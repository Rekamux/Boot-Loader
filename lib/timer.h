/****************
 * TIMER
 *
 * Timer tools
 ****************/

#ifndef TIMER_H
#define TIMER_H

/**
 * Initializes timer 0 for given time (in TCNTB)
 */
void initTimer0(long);

/**
 * Initializes timer 0 for 1s
 */
void init1sTimer0();

/**
 * Initializes timer 0 for 500ms
 */
void init500msTimer0();

/**
 * Initializes timer 0 for 250ms
 */
void init250msTimer0();

/**
 * Initializes timer 0 for 125ms
 */
void init125msTimer0();

/**
 * Initializes timer 0 for 75ms
 */
void init75msTimer0();

/**
 * Initializes timer 0 for 50ms
 */
void init50msTimer0();

/**
 * Initializes timer 0 for 25ms
 */
void init25msTimer0();

/**
 * Initializes timer 0 for 10ms
 */
void init10msTimer0();

/**
 * Initializes timer 0 for given ms
 */
void initMsTimer0(long ms);

/**
 * Returns current count
 */
long getCurrentTimer0();

/**
 * Launches timer 0 without blocking
 */
void launchTimer0();

/**
 * Launches timer 0 and waits until it finishes
 */
void launchAndWaitTimer0();

#endif
