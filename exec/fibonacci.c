#include "../lib/numbers.h"
#include "../lib/serial.h"

long fibonacci(long previous1, long previous2)
{
  return previous2 + previous1;
}

//BSS test
//long d[100000];

int main(int argc, char **argv)
{
  serial_init();
  serial_puts("\r\n\r\nFibonacci, the incredible suite\n\r\n\rBrought to you by Florent Guignabert & Axel Schumacher\r\n\r\n");

  long a = 0;
  long b = 1;
  itodec(a);
  serial_puts("\r\n");
  itodec(b);
  serial_puts("\r\n");
  long c;
  long count = 2;
  while (count < 10)
  {
    c = fibonacci(a, b);
    a = b;
    b = c;
    itodec(c);
    serial_puts("\r\n");
    count++;
  }
  return 0;
}
