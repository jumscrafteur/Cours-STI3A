#include <unistd.h>

#include "mini_lib.h"

struct malloc_element
{
  void *ptr;
  void *next_malloc;
  int size;
  int status;
};

typedef struct malloc_element malloc_element;

malloc_element *malloc_list = NULL;

void *mini_calloc(int size_element, int number_element)
{

  int totalSize = size_element * number_element;

  malloc_element *element;
  element = sbrk(sizeof(malloc_element));

  // On initialise le premier element de la liste chainé
  if (malloc_list == NULL)
  {

    if ((element->ptr = sbrk(totalSize)) == (void *)-1)
      mini_perror("Error");

    // On remplis par default le buffer de \0
    for (size_t i = 0; i < totalSize; i++)
    {
      void *elPtr = element->ptr + i * size_element;
      elPtr = '\0';
    }

    element->size = totalSize;
    element->next_malloc = NULL;
    element->status = 1;

    malloc_list = element;
  }
  else
  // Dans le cas où la liste chainé est initialisé
  {

    malloc_element *last;

    element = malloc_list;

    // On cherche le premier emplacement libre (fin de chaine ou emplacement libre de taille suffisante)
    while (element != NULL && !(element->status == 0 && element->size >= totalSize))
    {
      last = element;
      element = element->next_malloc;
    }

    // Si le premier emplacement libre est un nouveaux element en fin de chaine , on crée cet element
    if (element == NULL)
    {
      element = sbrk(sizeof(malloc_element));

      if ((element->ptr = sbrk(totalSize)) == (void *)-1)
        mini_perror("Error");

      for (size_t i = 0; i < totalSize; i++)
      {
        void *elPtr = element->ptr + i * size_element;
        elPtr = '\0';
      }

      // On initialize l'élément
      element->status = 1;
      element->next_malloc = NULL;
      element->size = totalSize;

      last->next_malloc = element;
    }
    else
    // Sinon on change l'état de l'élément a 'occupé'
    {
      element->status = 1;
    }
  }

  return element->ptr;
}

void mini_free(void *ptr)
{

  malloc_element *element = malloc_list;
  // On cherche l'élément dans la liste chainé
  while (element->ptr != ptr)
  {
    element = element->next_malloc;
  }

  // Une fois l'élément trouve on le met a l'état 'Libre'
  element->status = 0;
}