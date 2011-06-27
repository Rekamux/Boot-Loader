/****************
 * SERIAL
 *
 * Serial utilities ans configuration
 ***************/
#ifndef SERIAL_H
#define SERIAL_H

/**
 * UART's configuration
 */
void serial_init();

/**
 * Sends a character
 */
void serial_putc(char);

/**
 * Sends a string which MUST ends with '\0' character
 */
void serial_puts(char *);

/**
 * Gets a character
 */
char serial_getc();

/**
 * Gets a character without bloking
 * Returns 256 if no character
 */
short serial_getc_nb();

#endif
