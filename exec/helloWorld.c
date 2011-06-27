#define EXIT_SUCCESS 0

#include "../lib/serial.h"

/**
 * Main
 */ 
//__attribute__((naked)) //To avoid gcc from putting garbage before and after main function, especially with stuffs using stack...
int main(int argc, char **argv)
{
  serial_init();
  serial_puts("\r\n\r\nHello world!\n\r\n\rBrought to you by Florent Guignabert & Axel Schumacher\r\n\r\n");
  char c = serial_getc();
  while (c != 27 /*echap*/)
  {
    serial_putc(c);
    c = serial_getc();
  }
  serial_puts("\n\r");
  return EXIT_SUCCESS;
}

