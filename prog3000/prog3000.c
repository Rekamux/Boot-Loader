#include "../lib/buzzer.h"
#include "../lib/timer.h"
#include "../lib/serial.h"
#include "../lib/numbers.h"
#include "../lib/serial.h"
#include "../lib/leds.h"

extern unsigned long partition_begin;

int main(int argc, char **argv)
{
  serial_init();
  serial_puts("\r\nPortal - Still alive\r\n");
  long *address = (long *)(&partition_begin);
  long allTime = 0;
  initPE6();
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
  unsigned int a = 0;
  asm volatile("bx %0"::"r"(a));
  return 0;
}
