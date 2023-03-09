#include <stdio.h>
#include <unistd.h>

#include "mini_lib.h"

int main(int argc, char const *argv[])
{
  // |=============|
  // | MINI MEMORY |
  // |=============|

  // void *cal1 = mini_calloc(16, 1);
  // void *cal2 = mini_calloc(16, 1);
  // void *cal3 = mini_calloc(16, 1);

  // printf("test mini_calloc 1 :%p\n", cal1);
  // printf("test mini_calloc 2 :%p\n", cal2);
  // printf("test mini_calloc 3 :%p\n", cal3);

  // mini_free(cal2);

  // void *cal4 = mini_calloc(8, 1);

  // printf("test mini_calloc 4 :%p\n", cal4);

  // mini_printf("salut");

  // |=============|
  // | MINI STRING |
  // |=============|

  // int myTestSize = 5;
  // char *myTest = mini_calloc(sizeof(char), myTestSize);

  // printf("%d\n", mini_scanf(myTest, myTestSize * sizeof(char)));
  // mini_printf(myTest);

  // int test_mini_strlen = mini_strlen("7delong");
  // printf("%d\n", test_mini_strlen);

  // char *test_mini_strcpy_s = "je suis la vraie";
  // char *test_mini_strcpy_d = mini_calloc(sizeof(char), mini_strlen(test_mini_strcpy_s));
  // char *test_mini_strcmp = "je suis la pas vraie";

  // mini_strcpy(test_mini_strcpy_s, test_mini_strcpy_d);

  // printf("%s | %s \n", test_mini_strcpy_s, test_mini_strcpy_s);

  // printf("%d \n", mini_strcmp(test_mini_strcpy_s, test_mini_strcpy_d));
  // printf("%d \n", mini_strcmp(test_mini_strcpy_s, test_mini_strcmp));

  // write(-1, " \n", 0);
  // mini_perror("Error");

  // |=========|
  // | MINI IO |
  // |=========|

  // void *test_file = mini_calloc(sizeof(char), 419);
  // MYFILE *file = mini_fopen("reponses.txt", 'r');
  // mini_fread(test_file, sizeof(char), 200, file);
  // mini_printf(test_file);

  // void *test_file2 = mini_calloc(sizeof(char), 419);
  // mini_fread(test_file2, sizeof(char), 400, file);
  // mini_printf(test_file2);

  // MYFILE *file = mini_fopen("test.txt", 'w');
  // mini_fwrite("salut\n", sizeof(char), 8, file);

  // MYFILE *file = mini_fopen("test.txt", 'r');

  // printf("%c\n", mini_fgetc(file));
  // printf("%c\n", mini_fgetc(file));
  // printf("%c\n", mini_fgetc(file));

  // MYFILE *file = mini_fopen("test.txt", 'w');
  // mini_fputc(file, 'f');
  // mini_fputc(file, 'i');
  // mini_fputc(file, 'n');
  // mini_fputc(file, 'i');
  // mini_fputc(file, 't');
  // mini_fputc(file, 'o');

  mini_exit();
}
