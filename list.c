#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/*Estrutura da Lista. Possui ponteiro para a primeira posição*/
// struct list
// {
//     Node *first;
// };

/*Inicializa a lista*/
List *list_init()
{
    return NULL;
}
/*Inicializa o nó, alocando memória e inicializando os ponteiros*/
List *node_init(Value *v, Key *k)
{
    List *n = malloc(sizeof(*n));
    n->v = v;
    n->k = k;

    n->next = NULL;
    return n;
}

/*Insere na lista*/
List *list_insere(List *list, Value *v, Key *k)
{
    List *n = node_init(v, k);
    if (list == NULL)
    {
        list = n;
    }
    else
    {
        n->next = list;
        list = n;
    }

    return list;
}
/*Libera a memória*/
void list_free(List *l)
{
    if (l != NULL)
    {
        List *atual = l;
        List *next = NULL;
        while (atual != NULL)
        {
            next = atual->next;
            free(atual->k);
            free(atual->v);
            free(atual);
            atual = next;
        }
    }
}

Value *list_search(List *l, bool (*fn)(const Key *, const Key *), Key *key)
{
    for (List *n = l; n != NULL; n = n->next)
    {
        if (fn((n->k), key))
            return (n->v);
    }
    return NULL;
}

#include <stdio.h>
void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt)
{

    int i = 1;
    for (List *n = l; n != NULL; n = n->next)
    {
        printf("%d   ", i);
        i++;
        visit((n->v), opt);
    }
}
