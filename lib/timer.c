#include "timer.h"

#define PRESCALER      (*((volatile long *)0x01D50000))
#define T0_PRESCALER_MASK                  0xFFFFFF00

#define DIVIDER        (*((volatile long *)0x01D50004))
#define T0_DIVIDER_MASK                    0xFFFFFFF0

#define T0_ONE_SECOND                      64516
#define T0_500_MS                          32258
#define T0_250_MS                          16129
#define T0_125_MS                          8065
#define T0_75_MS                           4839
#define T0_50_MS                           3226
#define T0_25_MS                           1613
#define T0_10_MS                           645

#define TCON           (*((volatile long *)0x01D50008))
#define T0_TCON_MASK                       0xFFFFFFF0

#define TCNTB0         (*((volatile long *)0x01D5000C))
#define TCNTO0         (*((volatile long *)0x01D50014))

void initTimer0(long d)
{
  PRESCALER = PRESCALER & T0_PRESCALER_MASK;
  PRESCALER = PRESCALER | 255;
  DIVIDER   = DIVIDER & T0_DIVIDER_MASK;
  DIVIDER   = DIVIDER | 1; // Clock at 1/4

  TCNTB0    = d;

  TCON      = TCON & T0_TCON_MASK;
  TCON      = TCON | 0b0010; // Manual mode
}

long getCurrentTimer0()
{
  return TCNTO0;
}

#define MS_MULTIPLIER 65535/1020 //10ms error for 1s

void initMsTimer0(long ms)
{
  initTimer0(ms*MS_MULTIPLIER);
}

void init1sTimer0()
{
  initTimer0(T0_ONE_SECOND);
}

void init500msTimer0()
{
  initTimer0(T0_500_MS);
}

void init250msTimer0()
{
  initTimer0(T0_250_MS);
}

void init125msTimer0()
{
  initTimer0(T0_125_MS);
}

void init75msTimer0()
{
  initTimer0(T0_75_MS);
}

void init50msTimer0()
{
  initTimer0(T0_50_MS);
}

void init25msTimer0()
{
  initTimer0(T0_25_MS);
}

void init10msTimer0()
{
  initTimer0(T0_10_MS);
}

void launchTimer0()
{
  TCON      = TCON & T0_TCON_MASK;
  TCON      = TCON | 0b0001; // End of Manual and start
}

void launchAndWaitTimer0()
{
  launchTimer0();
  while (TCNTO0 != 0)
    asm("nop");
}
