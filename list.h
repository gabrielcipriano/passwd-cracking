#include "key.h"
#ifndef LIST_HEADER_H_INCLUDED
#define LIST_HEADER_H_INCLUDED
/*Estrutura do Nó de lista encadeada.
 *Possui um Value e ponteiros para o próximo nó.
 */
struct list
{
    Value k;
    struct list *next;
};

typedef struct list List;

// Inicializa a lista, alocando memória e inicializa os ponteiros
List *list_init();

// Insere na lista
List *list_insere(List *list, const Value *k);

// Libera a lista
void list_free(List *l);

// itera pela lista

void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt);

#endif
