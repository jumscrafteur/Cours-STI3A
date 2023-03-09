#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int lineCount = atoi(argv[1]);

  printf("%d", lineCount);
  // FILE *fp;

  // fp = fopen("myTestFile.txt", "r");

  // if (fp == NULL)
  // {
  //   fprintf(stderr, "Cannot open file for reading\n");
  //   exit(-1);
  // }

  // int currentChar;
  // int breakCount = 0;

  // while ((currentChar = fgetc(fp)) != EOF)
  //   if (currentChar == '\n')
  //     breakCount++;

  // printf("%d\n", breakCount);

  // fseek(fp, 0, SEEK_SET);

  // char line[100];
  // for (size_t i = 0; i < breakCount + 2; i++)
  // {
  //   if (i >= break)
  //     fgets(line, sizeof(line), fp);
  //   printf("%s", line);
  // }

  // printf("\n");

  // // line = malloc(sizeof(char) * 100);
  // // fread(line, sizeof(char), 100, fp);
  // // fgets(line, sizeof(line), fp);
  // // printf("%s", line);
  // // fgets(line, sizeof(line), fp);
  return 0;
}
