#include "../lib/serial.h"
#include "../lib/numbers.h"
#include "../lib/buzzer.h"
#include "../lib/timer.h"
#include "../lib/leds.h"
#include "bootLoader.h"

#define START_RAM 0x0C000000
#define END_RAM   0x0C7FFFFF

int main(int argc, char ** argv)
{
  serial_init();

  endl();
  endl();
  serial_puts("Boot-Loader v0.1");
  endl();
  endl();
  serial_puts("Brought to you by Florent Guignabert & Axel Schumacher");
  endl();
  endl();
  serial_puts("Press any key to abort booting...");
  wait5sec();
  init1sTimer0();
  endl();
  endl();
  serial_puts("Enter a command :");
  endl();
  endl();
  serial_puts("L <addr>: stores memory coming from serial at <addr>. Wait one second to terminate entry.");
  endl();
  serial_puts("U <addr>: user friendly memory storing coming from serial at <addr>. Press <ESC> to terminate entry.");
  endl();
  serial_puts("G <addr>: executes a program starting at given <addr>.");
  endl();
  serial_puts("R <addr>: displays memory at <addr>.");
  endl();
  endl();

  while (1)
    getCommand();

  return 0;
}

void wait5sec()
{
  init1sTimer0();
  short i = 0;
  short c = 256;
  char ret = 13;
  endl();
  serial_puts("Remaining time: ");
  itodec(5-i);
  serial_puts("s...");
  while (i < 5 && c > 255)
  {
    launchTimer0();
    while (getCurrentTimer0() != 0 && c > 255)
      c = serial_getc_nb();
    serial_putc(ret);
    serial_puts("Remaining time: ");
    itodec(4-i);
    serial_puts("s...");
    i++;
  }
  if (c > 255)
  {
    endl();
    serial_puts("Launching program at 0x3000");
    endl();
    unsigned int a = 0x3000;
    asm volatile("bx %0"::"r"(a));
  }
}

void getCommand()
{
  serial_puts("> ");
  char c = 0;
  char hexa;
  unsigned long addr = 0;
  short i;
  short bermuda;
  while (
      c != 'L' &&
      c != 'l' &&
      c != 'G' &&
      c != 'g' &&
      c != 'R' &&
      c != 'r' &&
      c != 'U' &&
      c != 'u'
      )
    c = serial_getc();

  serial_putc(c);
  serial_putc(' ');
  addr = 0;
  for (i=7; i>=0;)
  {
    hexa = serial_getc();
    bermuda = getDigit(hexa);
    if (bermuda != -1)
    {
      addr += (bermuda << (i*4));
      itohex(bermuda);
      i--;
    }
  }
  endl();
  if (c == 'L' || c == 'l')
    store(addr);
  else if (c == 'G' || c == 'g')
    execute(addr);
  else if (c == 'R' || c == 'r')
    display(addr);
  else if (c == 'U' || c == 'u')
    storeUser(addr);
  return;
}

void store(unsigned long address)
{
  char * destination = (char *) address;
  if (!isAddressValid(address))
  {
    serial_puts("Non valid address");
    endl();
    return;
  }
  if (!addressIsInFreeRam(address))
  {
    serial_puts("You cannot write in this area !\n\r");
    return;
  }
  short c = getCharOrAbort1s();
  while (c < 256)
  {
    *destination = (char)c;
    destination++;
    if (!addressIsInFreeRam((unsigned long)destination))
    {
      serial_puts("Incoming file is too big !");
      endl();
      return;
    }
    c = getCharOrAbort1s();
  }
  endl();
  serial_puts("No character received within 1 second, current writting aborted.");
  endl();
}

void storeUser(unsigned long address)
{
  if (!isAddressValid(address))
  {
    serial_puts("Non valid address");
    endl();
    return;
  }
  if (!addressIsInFreeRam(address))
  {
    serial_puts("You cannot write in this area !\n\r");
    return;
  }
  serial_puts("Enter values or press <ESC> to finish.\r\n");
  char c = serial_getc();
  unsigned long data = 0;
  short i = 7;
  while (c != 27 && getDigit(c) != -1)
  {
    char value = getDigit(c);
    serial_putc(c); 
    data += value << (i*4);
    if (i != 0)
      i--;
    else
    {
      i = 7;
      (*((unsigned long *)address)) = data;
      endl();
      serial_puts("Writing ");
      itohex8(data);
      serial_puts(" at address ");
      itohex8(address);
      endl();
      address += 4;
      data = 0;
      serial_puts("Now address is ");
      itohex8(address);
      endl();
      if (!addressIsInFreeRam(address))
      {
        serial_puts("At address ");
        itohex8(address);
        serial_puts(": ");
        endl();
        serial_puts("You cannot write in this area !");
        endl();
        return;
      }
    }
    c = serial_getc();
  }
  endl();
  if (getDigit(c) == -1)
  {
    serial_puts("Non digit character received, current writting aborted.");
    endl();
    return;
  }
  serial_puts("<ESC> received, current writting aborted.");
  endl();
}

void execute(unsigned long address)
{
  if (!isAddressValid(address))
  {
    serial_puts("Non valid address");
    endl();
    return;
  }
  void (*a)();
  a = (void *)address;
  a();
  init1sTimer0();
}

void display(unsigned long address)
{
  if (!isAddressValid(address))
  {
    serial_puts("Non valid address");
    endl();
    return;
  }
  unsigned long value = (*((volatile unsigned long *)address));
  serial_puts("Memory at ");
  itohex8(address);
  serial_puts(": ");
  itohex8(value);
  endl();
}

short getDigit(char c)
{
  if (c>=48 && c<=57)
    return c-48;
  if (c>=65 && c<=70)
    return c-55;
  if (c>=97 && c<=102)
    return c-87;
  return -1;
}

short getCharOrAbort1s()
{
  launchTimer0();
  short c = 256;
  while ((c > 255) && (getCurrentTimer0() != 0))
    c = serial_getc_nb();
  return c;
}

short addressIsInFreeRam(unsigned long address)
{
  return 
    (
     address >= START_RAM && 
     address <= END_RAM
    );
}

void endl()
{
  serial_puts("\r\n");
}

short isAddressValid(unsigned long address)
{
  return ((address % 4) == 0);
}

