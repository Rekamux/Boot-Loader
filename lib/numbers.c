#include "numbers.h"
#include "serial.h"

//Digit to char
char dtoc(unsigned short n)
{
  if (n >= 36)
    return '0';
  if (n < 10)
    return n + 48;
  return n - 10 + 65;
}

//Number to Hexadecimal
void itohex(unsigned long n)
{
  if (n == 0) //Critical check
  {
    serial_putc('0');
    return;
  }

  //Digits count
  long digitsCount = 0;
  unsigned long i = 1;
  while (i <= n && digitsCount < 8)
  {
    i = i << 4;
    digitsCount++;
  }

  //Word allocation
  char word[digitsCount+1];
  word[digitsCount] = '\0';

  //Algorithm
  unsigned long troncated_n = n;
  i = digitsCount-1;
  while (n > 0) //Genercial check
  {
    troncated_n = troncated_n >> 4;
    unsigned short digit = n - (troncated_n << 4);
    word[i] = dtoc(digit);
    n = troncated_n;
    i--;
  }

  //Return
  serial_puts(word);
  return;
}

//Number to 8 Hexadecimals
void itohex8(unsigned long n)
{
  long i;

  //Word allocation
  char word[11];
  word[10] = '\0';
  for (i=0; i<10; i++)
    word[i] = '0';
  word[1] = 'x';

  //Algorithm
  unsigned long troncated_n = n;
  unsigned long n_bis = n;
  i = 9;
  while (n_bis > 0)
  {
    troncated_n = troncated_n >> 4;
    unsigned short digit = n_bis - (troncated_n << 4);
    word[i] = dtoc(digit);
    n_bis = n_bis >> 4;
    i--;
  }

  //Return
  serial_puts(word);
  return;
}



//Number to Decimal
void itodec(long n)
{
  //Critical check
  if (n == 0) 
  {
    serial_puts("0");
    return;
  }

  //Sign check
  short isNegative = n < 0;
  if (isNegative)
    n = -n;

  //Digits count
  long digitsCount = 0;
  long i = 1;
  while (i <= n)
  {
    i *= 10;
    digitsCount++;
  }

  //Word allocation
  char word[digitsCount+1];
  word[digitsCount] = '\0';

  //Algorithm
  long troncated_n = n;
  long n_bis = n;
  i = digitsCount-1;
  while (n_bis > 0) //Genercial check
  {
    troncated_n /= 10;
    unsigned short digit = n_bis - troncated_n * 10;
    word[i] = dtoc(digit);
    n_bis /= 10;
    i--;
  }

  //Display
  if (isNegative)
    serial_putc('-');
  serial_puts(word);
  return;
}
