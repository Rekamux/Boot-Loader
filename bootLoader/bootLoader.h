/***********************************
 * BOOTLOADER
 *
 * Those are functions used by the
 * boot loader
 **********************************/
#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/**
 * Jump at address 0x3000 unless a character
 * is received within 5 seconds
 */
void wait5sec();

/**
 * Get incoming command and call appropriated function
 */
void getCommand();

/**
 * Stores received values starting at given address
 * If no value has been received within 1 second, ends writing.
 */
void store(unsigned long address);

/**
 * Same as above but interprets incoming characters (0-9a-fA-F)
 * and ends when other character received
 */
void storeUser(unsigned long address);

/**
 * Jumps at given address
 */
void execute(unsigned long address);

/**
 * Displays 32bits value stored at given address
 */
void display(unsigned long address);

/**
 * Returns integer value of a char (0-9a-fA-F)
 */
short getDigit(char);

/**
 * Gets a character or abort if none received within 1 second
 * @return char if character received, 256 otherwise
 */
short getCharOrAbort1s();

/**
 * Checks if given address is in ARM's RAM sector
 */
short addressIsInFreeRam(unsigned long);

/**
 * Same as C++
 */
void endl();

/**
 * Checks if given address is aligned
 */
short isAddressValid(unsigned long);

#endif
