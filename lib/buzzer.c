#include "buzzer.h"
#include "timer.h"

#define PRESCALER      (*((volatile long *)0x01D50000))
#define T3_PRESCALER_MASK                  0xFFFF00FF

#define DIVIDER        (*((volatile long *)0x01D50004))
#define T3_DIVIDER_MASK                    0xFFFF0FFF

#define T3_HALF_DO                         250
#define T3_HALF_RE                         223
#define T3_HALF_MI                         199
#define T3_HALF_FA                         188
#define T3_HALF_SOL                        167
#define T3_HALF_LA                         149
#define T3_HALF_SI                         133

#define TCON           (*((volatile long *)0x01D50008))
#define T3_TCON_MASK                       0xFFF0FFFF

#define TCNTB3         (*((volatile long *)0x01D50030))
#define TCMPB3         (*((volatile long *)0x01D50034))
#define TCNTO3         (*((volatile long *)0x01D50038))

#define PORT_E_CFG     (*((volatile long *)0x01D20028))
#define PE6_MASK                           0xFFFFCFFF

void initPE6()
{
  PORT_E_CFG = PORT_E_CFG & PE6_MASK;
  PORT_E_CFG = PORT_E_CFG | (1<<13); //TOUT3 mode

  PRESCALER = PRESCALER & T3_PRESCALER_MASK;
  PRESCALER = PRESCALER | (255<<8);
  DIVIDER   = DIVIDER & T3_DIVIDER_MASK;
  DIVIDER   = DIVIDER | 0; // Clock at 1/2
}

void shutUp()
{
  TCON = TCON & T3_TCON_MASK;
}

void playHalfPeriod(long p)
{
  TCNTB3 = p*2;
  TCMPB3 = p;

  TCON = TCON & T3_TCON_MASK;
  TCON = TCON | (1<<17); //Manual mode

  TCON = TCON & T3_TCON_MASK;
  TCON = TCON | (1<<19); //Auto-reload
  TCON = TCON | (1<<18); //Inverter for TOUT3
  TCON = TCON | (1<<16); //Start
}

void playWaveLenghtMm(long wl)
{
  if (wl == 0)
    shutUp();
  else
    playHalfPeriod(wl*65535/345000);
}

void playDo()
{
  playHalfPeriod(T3_HALF_DO);
}

void playRe()
{
  playHalfPeriod(T3_HALF_RE);
}

void playMi()
{
  playHalfPeriod(T3_HALF_MI);
}

void playFa()
{
  playHalfPeriod(T3_HALF_FA);
}

void playSol()
{
  playHalfPeriod(T3_HALF_SOL);
}

void playLa()
{
  playHalfPeriod(T3_HALF_LA);
}

void playSi()
{
  playHalfPeriod(T3_HALF_SI);
}

void playMelody()
{
  initPE6();
  init125msTimer0();
  playDo();
  launchAndWaitTimer0();
  playRe();
  launchAndWaitTimer0();
  playMi();
  launchAndWaitTimer0();
  playFa();
  launchAndWaitTimer0();
  playSol();
  launchAndWaitTimer0();
  playLa();
  launchAndWaitTimer0();
  playSi();
  launchAndWaitTimer0();
  playLa();
  launchAndWaitTimer0();
  playSol();
  launchAndWaitTimer0();
  playFa();
  launchAndWaitTimer0();
  playMi();
  launchAndWaitTimer0();
  playRe();
  launchAndWaitTimer0();
  playDo();
  launchAndWaitTimer0();
  long i=401;
  init10msTimer0();
  while (i >= 0)
  {
    playHalfPeriod(i);
    i -= 4;
    launchAndWaitTimer0();
  }
  shutUp();
  init125msTimer0();
  launchAndWaitTimer0();
  playSol();
  launchAndWaitTimer0();
  shutUp();
  launchAndWaitTimer0();
  playHalfPeriod(20);
  launchAndWaitTimer0();
  shutUp();
}

