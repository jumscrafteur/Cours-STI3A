#include <fcntl.h>
#include <unistd.h>
#include "mini_lib.h"

#define IOBUFFER_SIZE 2048

MYFILE *opened_files[80];
int opened_file_nb;

MYFILE *mini_fopen(char *file, char mode)
{
  MYFILE *output_file = mini_calloc(1, sizeof(MYFILE));

  int mode_flag;

  // On définit la valeur du flag d'ouverture du fichier en fonction de "mode"
  switch (mode)
  {
  case 'r':
    mode_flag = O_RDONLY;
    break;
  case 'w':
    mode_flag = O_WRONLY;
    break;
  case 'b':
    mode_flag = O_RDWR;
    break;
  case 'a':
    mode_flag = O_APPEND;
    break;

  default:
    mode_flag = -1;
    break;
  }

  int fd = open(file, mode_flag);
  if (fd == -1)
  {
    mini_perror("Error");
  }

  // On initialise l'élément file
  output_file->fd = fd;
  output_file->ind_read = -1;
  output_file->ind_write = -1;

  // On ajoute le fichier a la liste des fichiers ouverts
  opened_files[opened_files_nb++] = output_file;
  return output_file;
};

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file)
{
  // Variable pour compter le nombre de chars écrit dans le buffer
  int written_char = 0;

  // Variable pour verifier si on fait un dernier passage de boucle
  int last = 0;

  int nb_char_lu = read(file->fd, file->buffer_read, IOBUFFER_SIZE);

  // On initialise si le buffer de lecture n'as jamais été utilisé
  if (file->ind_read == -1)
  {
    file->buffer_read = mini_calloc(sizeof(char), IOBUFFER_SIZE);

    nb_char_lu = read(file->fd, file->buffer_read, IOBUFFER_SIZE);

    // Si on arrive pas a remplir le buffer c'est que l'on a attend la fin du fichier
    if (nb_char_lu < IOBUFFER_SIZE)
      last = 1;

    if (nb_char_lu == -1)
    {
      mini_perror("Error");
      return -1;
    }
    file->ind_read = 0;
  }

  for (size_t i = 0; i < number_element; i++)
  {
    // On déplace le caractère du fichier vers le buffer
    ((char *)buffer)[i] = ((char *)file->buffer_read)[file->ind_read];
    written_char++;

    file->ind_read++;

    if (file->ind_read == nb_char_lu && last == 1)
      break;

    // Si On arrive a la fin du buffer alors on récupère un nouveaux chunk de donnée et on remet ind_read a 0
    if (file->ind_read == nb_char_lu && last == 0)
    {
      lseek(file->fd, 0, SEEK_CUR);
      nb_char_lu = read(file->fd, file->buffer_read, IOBUFFER_SIZE);

      // Si on arrive pas a remplir le buffer c'est que l'on a attend la fin du fichier
      if (nb_char_lu < IOBUFFER_SIZE)
        last = 1;

      if (nb_char_lu == -1)
      {
        mini_perror("Error");
        return -1;
      }
      file->ind_read = 0;
    }
  }

  return written_char;
};

int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file)
{
  // Si le buffer l'écriture n'est pas initialisé on l'initialise
  if (file->ind_write == -1)
  {
    file->buffer_write = mini_calloc(sizeof(char), IOBUFFER_SIZE);
    file->ind_write = 0;
  }

  int written_char = 0;

  for (size_t i = 0; i < number_element; i++)
  {
    // On copie les données du buffer passé en argument vers le buffer d'écriture du fichier
    ((char *)file->buffer_write)[file->ind_write] = ((char *)buffer)[i];
    file->ind_write++;
    written_char++;

    // On s'arrête lorsque l'on arrive a la fin du buffer
    if (((char *)buffer)[i] == '\0')
      break;

    // Si on arrive a la fin du buffer , on l'écrit dans le fichier puis on le remet a 0
    if (file->ind_write == IOBUFFER_SIZE)
    {
      if (write(file->fd, file->buffer_write, IOBUFFER_SIZE) == -1)
      {
        mini_perror("Error");
        return -1;
      }
      lseek(file->fd, 0, SEEK_END);

      file->ind_write = 0;
    }
  }

  return written_char;
};

int mini_fflush(MYFILE *file)
{
  // Si le buffer d'écriture est initialisé, le vide dans le fichier
  if (file->ind_write != -1)
    if (write(file->fd, file->buffer_write, mini_strlen(file->buffer_write)) == -1)
    {
      mini_perror("Error");
      return -1;
    }
}

int mini_fclose(MYFILE *file)
{
  // On flush le fichier
  mini_fflush(file);

  int offset = 0;

  for (size_t i = 0; i < opened_file_nb; i++)
  {
    // On supprime l'élément de la liste des fichiers ouverts
    if (opened_files[i] == file)
    {
      offset++;
    }

    // On décale les éléments pour ne pas laisser de vide
    opened_files[i] = opened_files[i + offset];
  }

  opened_file_nb -= offset;

  // On ferme le fichier
  if (close(file->fd) == -1)
  {
    mini_perror("Error");
    return -1;
  };

  return 0;
}

int mini_fgetc(MYFILE *file)
{
  char *charbuff = mini_calloc(sizeof(char), 1);
  mini_fread(charbuff, sizeof(char), 1, file);

  return (int)charbuff[0];
}

int mini_fputc(MYFILE *file, char c)
{
  mini_fwrite(&c, sizeof(char), 1, file);
};
