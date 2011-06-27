/************
 * LEDS
 *
 * Utilities for the leds
 ************/

#ifndef LEDS_H
#define LEDS_H

/**
 * Turns on led C #bit
 */
void turnOnLedC(short bit); // Bit in {1, 2, 3}

/**
 * Turns off led C #bit
 */
void turnOffLedC(short bit); // Bit in {1, 2, 3}

/**
 * Turns on led E
 */
void turnOnLedE();

/**
 * Turns off led E
 */
void turnOffLedE();

/**
 * Turns on led #bit (3 = E)
 */
void turnOnLed(short n); // N in {0, 1, 2, 3}

/**
 * Turns off led #bit (3 = E)
 */
void turnOffLed(short n); // N in {0, 1, 2, 3}

#endif
