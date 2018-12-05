#include <stdlib.h>
#include <stdbool.h>

#include "list.1.h"

/*Inicializa a lista, alocando memória e inicializa os ponteiros*/
List1 *list_init1()
{
    List1 *l = malloc(sizeof(*l));

    l->first = NULL;

    return l;
}
/*Inicializa o nó, alocando memória e inicializando os ponteiros*/
Node1 *node_init1(Value *v, Key *k)
{
    Node1 *n = malloc(sizeof(*n));
    n->k = *k;
    n->v = *v;
    n->next = NULL;
    return n;
}

/*Insere na lista*/
void list_insere1(List1 *list, Value *v, Key *k)
{
    Node1 *n = node_init1(v, k);
    if (list->first == NULL)
    {
        list->first = n;
    }
    else
    {
        n->next = list->first;
        list->first = n;
    }
}
/*Libera a memória*/
void list_free1(List1 *l)
{
    if (l != NULL)
    {
        Node1 *atual = l->first;
        Node1 *next = NULL;
        while (atual != NULL)
        {
            next = atual->next;
            free(atual);
            atual = next;
        }

        free(l);
    }
}

void list_iterate1(List1 *l, void (*visit)(Value *, Value *), Value *opt)
{
    if (l != NULL)
    {
        for (Node1 *n = l->first; n != NULL; n = n->next)
        {
            visit(&(n->v), opt);
        }
    }
}
