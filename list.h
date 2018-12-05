#include "key.h"
#ifndef LIST_HEADER_H_INCLUDED
#define LIST_HEADER_H_INCLUDED

typedef struct list List;

// Inicializa a lista, alocando memória e inicializa os ponteiros
List *list_init();

// Insere na lista
void list_insere(List *list,const Value *k);

// Libera a lista
void list_free(List *l);

// itera pela lista

void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt);

#endif
