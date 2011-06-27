#!/usr/bin/env python
# -*- coding: utf-8 -*-


import sys

from midi import *
from midi.MidiOutStream import MidiOutStream
from midi.MidiInFile import MidiInFile
from midi.MidiToText import MidiToText

ON = True
OFF = False

def note_to_freq(note):
    """
    44 : A4 (le LA standard)
    """
    return 440*pow(2, (note-44.0)/12.0)



class MidiParser(MidiOutStream):

    def __init__(self, infile = 'fichiers_midi/internationale.mid', verbose=False):
        self.infile = infile
        self._data = {}
        self._busy_chan = []
        self.verbose = verbose
        self._tempo = 1000000000.0 # empiriquement : 1 noire à la seconde 
        midi_in = MidiInFile(self, self.infile)
        midi_in.read()
        # Une fois le parsing fini, on ajuste les temps et durées pour
        # tenir compte du tempo
        for chan_num, chan_data in self._data.iteritems() :
            for evt in chan_data :
                evt['time'] = int(evt['time'] * self._tempo * 1000)
                evt['duration'] = int(evt['duration'] * self._tempo*1000)

    def get_data(self):
        return self._data

    def get_channel(self, channel):
        try:
            return self._data[channel]
        except:
            pass
        return None

    def merge_channels(self):
        all_events = []
        for chan_num, chan_data in self._data.iteritems():
            for evt in chan_data:
                evt['channel'] = chan_num
                all_events.append(evt)
        all_events.sort(lambda e1, e2: cmp(e1['time'], e2['time']))
        return all_events

    def get_channel_list(self):
        return self._data.keys()

    def note_on(self, channel=0, note=0x40, velocity=0x40):
        self.store_evt(ON, channel, note, self.abs_time())

    def note_off(self, channel=0, note=0x40, velocity=0x40):
        self.store_evt(OFF, channel, note, self.abs_time())

    def tempo(self, value):
        self._tempo = value/1000000000.0

    def sysex_event(self, data):
        pass

    def store_evt(self, status, channel, note, time):
        """
        channel : le numéro de channel de la note
        status : ON / OFF
        note : value (44=C0)
        time : absolute time (in frame)
        
        """
        if self.verbose:
            print status and "ON " or "OFF", channel, note, int(note_to_freq(note)+0.5), time
            
        # On récupère le tableau contenant le channel concerné, ainsi que le dernier
        # événement inséré dedans
        try:
            chan = self._data[channel]
        except:
            # Le channel est nouveau : on le crée !
            self._data[channel] = []
            chan = self._data[channel]
            chan.append({'time' : time,
                         'freq' : 0,
                         'duration' : 0, 
                         })

        # Si le channel n'a pas déjà une note en cours, on ajoute l'evt et on marque le channel comme occupé
        if channel not in self._busy_chan and status == ON:
            # Optimisation : si par hasard on a déjà un événement OFF à cette date là,
            # alors on le vire et on garde juste le ON
            if len(chan) > 0:
                evt = chan[len(chan)-1]
                if evt['time'] == time :
                    chan.pop()
                    if len(chan) == 0:
                        chan.append({'time' : time,
                                     'freq' : 0,
                                     'duration' : 0, 
                                     })
                        

            # On met à jour la durée de l'événement précédent
            chan[len(chan)-1]['duration'] = time-chan[len(chan)-1]['time']

            # On insère le nouvel événement
            evt = {'time' : time,
                   'freq' : int(345000/(note_to_freq(note)+0.5)),   #ICI ce n'est plus la frequence mais la longueur d'onde en mm !!!!
                   'duration' : 0, 
                   }
            chan.append(evt)
            self._busy_chan.append(channel)
            
        # Si le channel a déjà une note en cours, alors on n'insère qu'un OFF
        if channel in self._busy_chan and status == OFF:
            # On met à jour la durée de l'événement précédent
            chan[len(chan)-1]['duration'] = time-chan[len(chan)-1]['time']

            # On insère le nouvel événement
            evt = {'time' : time,
                   'freq' : 0,
                   'duration' : 0, 
                   }
            chan.append(evt)
            self._busy_chan.remove(channel)


def play(channel_data):
    from Numeric import sin, arrayrange, Int16, concatenate
    from pygame import mixer, sndarray, time
    from math import pi

    samplerate = 22000.0 # hz
    bits = 16
    mixer.init(int(samplerate), bits, 0)

    def beep(freq, duration):
        samples = (sin(arrayrange(duration/1000.0 * samplerate) * (2 * pi * (freq / samplerate))) * float(1 << (bits - 2))).astype(Int16)
        snd = sndarray.make_sound(samples)
        snd.play()
        while mixer.get_busy():
            pass

    for evt in channel_data:
        beep(evt['freq'], evt['duration'])


if __name__ == '__main__':

    if len(sys.argv) == 0:
      file = 'ave_maria.mid'
    else:
      file = sys.argv[1]

    if len(sys.argv) <= 1:
      chan = 0
    else:
      chan = int(sys.argv[2])

    #file = '../midi/fichiers_midi/'+file

    # Pour parser un fichier : parser = MidiParser()
    # Par défaut, c'est fichiers_midi/test.mid qui est joué.
    # Mais on peut aussi passer au constructeur un autre nom de fichier
    # Et un flag verbose pour afficher des infos de débug.
    parser = MidiParser(file, verbose=False)

    # Recupère la liste des channels du fichiers MIDI
    channel_list = parser.get_channel_list()

    # Affiche le nombre de channel trouvés
    #print "Channels = ", channel_list
    
    # Pour chaque channel, on affiche les notes qui le composent : un dico contenant les champs suivants
    #   time : temps absolu en ms
    #   duration : une durée en ms
    #   freq : fréquence en Hz
    #for chan in channel_list:
    #    print "channel %d : "%(chan)
    for evt in parser.get_channel(chan) :
      print str(evt['time'])+" "+str(evt['duration'])+" "+str(evt['freq'])

    #print getopt.getopt(1)

    # Joue le channel 0
    #play(parser.get_channel(0))



