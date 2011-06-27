/****************
 * BUZZER
 *
 * Library for buzzer's manipulation
 ****************/
#ifndef BUZZER_H
#define BUZZER_H

/**
 * Initializes link between buzzer and timer #3
 */
void initPE6();

/**
 * Plays given long as helf period
 */
void playHalfPeriod(long);

/**
 * Plays given wave lenght in mm
 */
void playWaveLenghtMm(long);

/**
 * Plays a C4
 */
void playDo();

/**
 * Plays a D4
 */
void playRe();

/**
 * Plays a E4
 */
void playMi();

/**
 * Plays a F4
 */
void playFa();

/**
 * Plays a G4
 */
void playSol();

/**
 * Plays a A4
 */
void playLa();

/**
 * Plays a B4
 */
void playSi();

/**
 * Stops timer #3
 */
void shutUp();

/**
 * Plays a gam
 */
void playMelody();

#endif
