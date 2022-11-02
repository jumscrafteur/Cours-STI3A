#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LTEMPS 32

int main(int argc, char *argv)
{
  struct stat statut;
  int i;

  if (argc < 2)
  {
    if (fstat(STDIN_FILENO, &statut) == -1)
    {
      fprintf(stderr, "%s : impossible d’obtenir le statut de % s\n", argv[0], "<STDIN>");
      exit(EXIT_FAILURE);
    }
    print_stat("<STDIN>", &statut);
  }
  else
  {
    for (i = 1; i < argc; i++)
    {
      if (stat(argv[i], &statut) == -1)
      {
        fprintf(stderr, "%s : impossible d’obtenir le statut de % s\n", argv[0], argv[i]);
        continue;
      }
      print_stat(argv[i], &statut);
    }
  }
  exit(EXIT_SUCCESS);
}

void print_stat(const char *ref, struct stat *statut)
{
  struct passwd *pw;
  struct group *gr;
  char type;

  char pws[9], grs[9], temps[LTEMPS];
  type = '?';

  if (S_ISDIR(statut->st_mode))
    type = '-';
  else if (S_ISDIR(statut->st_mode))
    type = 'd';
  else if (S_ISDIR(statut->st_mode))
    type = 'd';
  else if (S_ISCHR(statut->st_mode))
    type = 'c';
  else if (S_ISBLK(statut->st_mode))
    type = 'b';
  else if (S_ISFIFO(statut->st_mode))
    type = 'p';

  strftime(temps, LTEMPS, "%a %e %h %Y %H:%M:%S", localtime(&(statut->st_mtime)));

  pw = getpwuid(statut->st_uid);

  if (pw != NULL)
    strcpy(pws, pw->pw_name);
  else
    sprintf(pws, "%8d", (int)statut->st_uid);

  // page 120
}