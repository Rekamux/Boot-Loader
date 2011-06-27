#include "../lib/leds.h"
#include "../lib/timer.h"
#include "../lib/serial.h"

#define WAIT           0x0000FFFF   //WAITING TIME

int main(int argc, char **argv)
{
  long i = 0;                    //Waiting counter
  long led = 0;                  //Bits to lit

  for (i=0; i<=3; i++)
    turnOffLed(i);

  init1sTimer0();

  while (serial_getc_nb() > 255)
  {
    turnOffLed(led);

    led++;

    if (led == 4)
      led = 0;

    turnOnLed(led);

    launchAndWaitTimer0();
  }

  return 0;
}
