#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1

// static void copy_file_GLIBC(const char *src, const char *dst)
// {
//   struct stat stsrc, stdst;
//   FILE *fsrc, *fdst;
//   int c;

//   lstat(src, &stsrc);
//   lstat(dst, &stdst);

//   if (stsrc.st_ino == stdst.st_ino && stsrc.st_dev == stdst.st_dev)
//   {
//     fprintf(stderr, "%s et %s sont le meme fichier\n", src, dst);
//     return;
//   }

//   fsrc = fopen(src, "r");
//   fdst = fopen(dst, "w");

//   while ((c = fgetc(fsrc)) != EOF)
//     fputc(c, fdst);

//   fclose(fsrc);
//   fclose(fdst);
// }

static void copy_file_GLIBC(const char *src, const char *dst)
{
  struct stat stsrc, stdst;
  FILE *fsrc, *fdst;
  char buffer[BUFSIZE];
  size_t bytes;

  lstat(src, &stsrc);
  lstat(dst, &stdst);

  if (stsrc.st_ino == stdst.st_ino && stsrc.st_dev == stdst.st_dev)
  {
    fprintf(stderr, "%s et %s sont le meme fichier\n", src, dst);
    return;
  }

  fsrc = fopen(src, "r");
  fdst = fopen(dst, "w");

  while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fsrc)))
    fwrite(buffer, 1, bytes, fdst);

  fclose(fsrc);
  fclose(fdst);
}

static void copy_file_AS(const char *src, const char *dst)
{
  int fdsrc, fddst;
  char buffer[BUFSIZE];
  int nchar;

  fdsrc = open(src, O_RDONLY);
  fddst = open(dst, O_WRONLY | O_CREAT | O_TRUNC,
               S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  while ((nchar = read(fdsrc, buffer, BUFSIZE)))
  {
    write(fddst, buffer, nchar);
  }
  close(fdsrc);
  close(fddst);
}

int main(int argc, char *argv[])
{
  copy_file_AS(argv[1], argv[2]);
  printf("ok\n");
}