#include <unistd.h>

int main(int argc, char **argv)
{
  unsigned long c = argc == 1?250000:atoi(argv[1])*1000;
  usleep(c);
}
