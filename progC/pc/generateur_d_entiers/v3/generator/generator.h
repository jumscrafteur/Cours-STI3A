#ifndef GENERATOR_H
#define GENERATOR_H
enum message
{
    Debut,
    Suivant
};

typedef enum message message;

extern int generator_generate(message);

#endif