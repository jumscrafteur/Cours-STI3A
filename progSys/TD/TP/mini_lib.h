#ifndef LIB_H
#define LIB_H

// mini_memory.c
void *mini_calloc(int size_element, int number_element);

void mini_free(void *ptr);

// mini_string.c
void mini_printf(char *text);
int mini_scanf(char *buffer, int size_buffer);
int mini_strlen(char *s);
int mini_strcpy(char *s, char *d);
int mini_strcmp(char *s1, char *s2);
char *itoa(int val);
void mini_perror(char *message);
void mini_exit();

// mini_io.c

struct MYFILE
{
  int fd;
  void *buffer_read;
  void *buffer_write;
  int ind_read;
  int ind_write;
};

typedef struct MYFILE MYFILE;

MYFILE *mini_fopen(char *file, char mode);

#define FILE_NB_LIMITE 80

extern MYFILE *opened_files[FILE_NB_LIMITE];
extern int opened_files_nb;

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file);
int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file);
int mini_fflush(MYFILE *file);
int mini_fclose(MYFILE *file);
int mini_fgetc(MYFILE *file);
int mini_fputc(MYFILE *file, char c);

#endif