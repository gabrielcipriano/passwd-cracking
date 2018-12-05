#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/*Estrutura do Nó de lista encadeada.
 *Possui um Value e ponteiros para o próximo nó.
 */
struct list
{
    Value k;
    struct list *next;
};

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
List *node_init(const Value *k)
{
    List *n = malloc(sizeof(*n));
    n->k = *k;
    n->next = NULL;
    return n;
}

/*Insere na lista*/
List* list_insere(List *list, const Value *k)
{
    List *n = node_init(k);
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
            free(atual);
            atual = next;
        }

    }
}

#include <stdio.h>  
void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt)
{
    if (l != NULL)
    {
        int i = 0;
        for (List *n = l; n != NULL; n = n->next)
        {
            printf("%d   ", ++i);
            visit(&(n->k), opt);
        }
    }
}
