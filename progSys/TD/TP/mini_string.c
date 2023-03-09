#include "mini_lib.h"
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 1024

int opened_files_nb;

char *buffer;
static int ind = -1;

void mini_printf(char *msg)
{
  // Si le buffer n'est pas initialisé , on l'initialise
  if (ind == -1)
  {
    buffer = mini_calloc(sizeof(char), BUF_SIZE);
    if (buffer == NULL)
    {
      mini_perror("Error");
    }
    ind = 0;
  }

  // On parcoure la chaine jusqu'a la fin
  for (size_t i = 0; msg[i] != '\0'; i++)
  {
    // On ajoute les caractères a afficher dans le buffer
    buffer[ind] = msg[i];
    ind++;

    // Si on arrive a une fin de ligne ou que qu'on arrive a la fin du buffer on affiche le buffer et reviens au debut
    if (msg[i] == '\n' || ind == BUF_SIZE)
    {
      if (write(1, buffer, ind) == -1)
      {
        mini_perror("Error");
      }
      ind = 0;
    }
  }
}

int mini_scanf(char *buffer2, int size_buffer)
{
  // On lit stdin
  int nb_char_read = read(0, buffer2, 5);
  if (nb_char_read == -1)
  {
    mini_perror("Error");
  }
  else
  {
    // Lorsque le buffer est déjà remplis de donné avec l'input du stdin , in n'y a pas la place pour le \n
    // on limite donc la taille du stdin a buffer_size - 1
    if (nb_char_read == size_buffer / sizeof(char))
      buffer2[nb_char_read - 1] = '\n';
    return nb_char_read;
  }
}

int mini_strlen(char *s)
{
  int len = 0;

  // On compte le nombre de char avant \0
  while (s[len] != '\0')
    len++;

  return len;
};

int mini_strcpy(char *s, char *d)
{
  int i = 0;

  // On copie tout les chars de source vers destination jusqu'a tomber sur le caractère de fin de chaine
  while (s[i] != '\0')
  {
    d[i] = s[i];
    i++;
  }

  d[i] = '\0';

  return i;
}

int mini_strcmp(char *s1, char *s2)
{
  // On vérifie si tout les caractère des chaines sont égaux
  for (size_t i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    // En cas de différence on retourne -1
    if (s1[i] != s2[i])
      return -1;

  return 0;
}

char *itoa(int val)
{
  static char buf[32] = {0};

  // on gère le cas où val = 0 => val = False
  if (val == 0)
    return "0";

  int i = 30;

  // On récupère chaque chiffre en partant de la droite pour le transformer en char
  for (; val && i; --i, val /= 10)
    buf[i] = "0123456789"[val % 10];

  return &buf[i + 1];
}

void mini_perror(char *message)
{
  // On transforme le code d'erreur entier en string
  char *err_code = itoa(errno);

  int err_code_len = mini_strlen(err_code);

  int msg_len = mini_strlen(message);

  char *err_msg = mini_calloc(sizeof(char), msg_len + 2 + err_code_len + 1);

  // On forme la string "*message d'erreur*: *code d'erreur*\n"
  mini_strcpy(message, err_msg);
  mini_strcpy(": ", err_msg + msg_len);
  mini_strcpy(err_code, err_msg + msg_len + 2);
  mini_strcpy("\n", err_msg + msg_len + 2 + err_code_len);

  // On affiche la string
  mini_printf(err_msg);
}

void mini_exit()
{
  // On flush tout les buffers des fichiers ouvert
  for (size_t i = 0; i < opened_files_nb; i++)
  {
    mini_fflush(opened_files[i]);
  }

  // On vide le buffer de printf
  if (ind != -1)
    if (write(1, buffer, ind) == -1)
    {
      mini_perror("Error");
    }

  // On termine le programme
  _exit(0);
}
