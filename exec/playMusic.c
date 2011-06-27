#include "../lib/buzzer.h"
#include "../lib/timer.h"
#include "../lib/serial.h"
#include "../lib/numbers.h"
#include "../lib/serial.h"
#include "../lib/leds.h"

int main(int argc, char **argv)
{
  long allTime = 0;
  initPE6();
  long *address = (long *)0x0C500000;
  long time = *address;
  address ++;
  long duration = *address;
  address ++;
  long waveLenght = *address; 
  short c = 256;
  short previousLed = time%4;
  short currentLed = previousLed;
  while ((time != 0xFFFFFFFF || duration != 0xFFFFFFFF || waveLenght != 0xFFFFFFFF) && c > 255)
  {
    currentLed = time%4 == previousLed ? (time+1) % 4 : time % 4;
    turnOnLed(currentLed);
    if (time > allTime)
    {
      long diff = time - allTime;
      while (diff > 1000)
      {
        init1sTimer0();
        launchAndWaitTimer0();
        diff -= 1000;
      }
      initMsTimer0(diff);
      launchAndWaitTimer0();
    }
    allTime = time+duration;
    c = serial_getc_nb();
    initMsTimer0(duration);
    playWaveLenghtMm(waveLenght);
    launchAndWaitTimer0();
    shutUp();
    address ++;
    turnOffLed(currentLed);
    previousLed = currentLed;
    time = *address;
    address ++;
    duration = *address;
    address ++;
    waveLenght = *address; 
  }
  return 0;
}
