#include "leds.h"

#define PORTC (*((volatile long *)0x01d20014))   //C leds address (bits 1, 2, and 3)
#define PORTE (*((volatile long *)0x01d2002C))   //E led address  (bit 5)

void turnOnLedC(short bit)
{
  long ledMask = 1 << bit;
  PORTC = PORTC | ledMask;
}

void turnOffLedC(short bit)
{
  long ledMask = 1 << bit;
  PORTC = PORTC & (0xFFFFFFFF - ledMask);
}

void turnOnLedE()
{
  long ledMask = 1 << 5;
  PORTE = PORTE | ledMask;
}

void turnOffLedE()
{
  long ledMask = 1 << 5;
  PORTE = PORTE & (0xFFFFFFFF - ledMask);
}

void turnOnLed(short n)
{
  if (n <= 2)
    turnOnLedC(n+1);
  else if (n == 3)
    turnOnLedE();
}

void turnOffLed(short n)
{
  if (n <= 2)
    turnOffLedC(n+1);
  else if (n == 3)
    turnOffLedE();
}

