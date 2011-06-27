#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Use: musToBinary <file.mus> <output>\n");
    return 0;
  }

  char *fileName = argv[1];
  FILE *file = fopen(fileName, "r");
  char *fileBinName = argv[2];
  FILE *fileBin = fopen(fileBinName, "w+");
  int i;
  long time, duration, waveLength;

  if (file == NULL || fileBin == NULL)
  {
    printf("Cannot open file !\n");
    return 1;
  }

  while(fscanf(file, "%ld %ld %ld", &time, &duration, &waveLength) != EOF)
  {
    for (i=0; i<4; i++)
      fputc((time>>(i*8))&0xFF, fileBin);
    for (i=0; i<4; i++)
      fputc((duration>>(i*8))&0xFF, fileBin);
    for (i=0; i<4; i++)
      fputc((waveLength>>(i*8))&0xFF, fileBin);
  }

  for (i=0; i<12; i++)
    fputc(0xFF, fileBin);

  fclose(file);
  fclose(fileBin);

  return 0;
}
