#include "serial.h"

#define UBRDIV0  (*((volatile long *)0x01D00028)) //Speed
#define UTRSTAT0 (*((volatile long *)0x01D00010)) //Transmission rights
#define RCVMASK                    1 //Transmission receive mask
#define SDMASK                     2 //Transmission send mask
#define UTXH0    (*((volatile long *)0x01D00020)) //Write
#define URXH0    (*((volatile long *)0x01D00024)) //Read
#define UCON0    (*((volatile long *)0x01D00004)) //Registers
#define ILCON0   (*((volatile long *)0x01D00000)) //UART

/**
 * Initialization
 */
void serial_init()
{
  //UART configuration
  ILCON0 = 0x3;
  //Registers configuration
  UCON0 = 0x5;
  //Speed configuration
  UBRDIV0 = 0x23;
}

/**
 * PUTC
 */
void serial_putc(char c)
{
  //Waiting for transmit buffer empty
  while (!(UTRSTAT0 & SDMASK));
  //Sending character
  UTXH0 = c;
}

/**
 * PUTS
 */
void serial_puts(char *s)
{
  short counter = 0;
  while (s[counter] != '\0')
  {
    serial_putc(s[counter]);
    counter ++;
  } 
}

/**
 * GETC
 */
char serial_getc()
{
  //Waiting for receive buffer not empty
  while (!(UTRSTAT0 & RCVMASK));
  //Returning character
  return URXH0;
}

/**
 * GETC NON BLOQUANT
 */
short serial_getc_nb()
{
  //Trying to receive buffer not empty
  if (!(UTRSTAT0 & RCVMASK))
     return 256;
  //Returning character
  return (short)((char)URXH0);
}
