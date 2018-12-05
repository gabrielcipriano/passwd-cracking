#include <stdlib.h>
#include <stdbool.h>

#include "list.1.h"

/*Inicializa a lista, alocando memória e inicializa os ponteiros*/
List1 *list_init1()
{

    return NULL;
}
/*Inicializa o nó, alocando memória e inicializando os ponteiros*/
List1 *node_init1(Value *v, Key *k)
{
    List1 *n = malloc(sizeof(*n));
    n->k = *k;
    n->v = *v;
    n->next = NULL;
    return n;
}

/*Insere na lista*/
List1 *list_insere1(List1 *list, Value *v, Key *k)
{
    List1 *n = node_init1(v, k);
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
void list_free1(List1 *l)
{
    if (l != NULL)
    {
        List1 *atual = l;
        List1 *next = NULL;
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

    for (List1 *n = l; n != NULL; n = n->next)
    {
        visit(&(n->v), opt);
    }
}
