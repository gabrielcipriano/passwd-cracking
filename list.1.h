#include "key.h"
#ifndef LIST_1_HEADER_H_INCLUDED
#define LIST_1_HEADER_H_INCLUDED

/*Estrutura do Nó de lista encadeada.
 *Possui um Value e ponteiros para o próximo nó.
 */
struct list1
{
    Value v;
    Key k;
    struct list1 *next;
};

typedef struct list1 List1;

// Inicializa a lista, alocando memória e inicializa os ponteiros
List1 *list_init1();

// Insere na lista
List1 *list_insere1(List1 *, Value *, Key *);

// Libera a lista
void list_free1(List1 *l);

// itera pela lista

void list_iterate1(List1 *, void (*visit)(Value *, Value *), Value *);

#endif
