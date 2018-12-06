#include "key.h"
#ifndef LIST_HEADER_H_INCLUDED
#define LIST_HEADER_H_INCLUDED

typedef struct{
    Key k;
    Key_custom v;
} Item;

/*Estrutura do Nó de lista encadeada.
 *Possui um Item e ponteiros para o próximo nó.
 */
typedef struct list List;



// Inicializa a lista, alocando memória e inicializa os ponteiros
List *list_init();

// Insere na lista
List *list_insere(List *list, Key_custom *v, Key *k);

// Libera a lista
void list_free(List *l);

// Pesquisa a chave na lista
Item *list_search(List *l, bool (*fn)(const Key *, const Key *), Key *key);

// itera pela lista
void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt);

#endif
