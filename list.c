#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/*Estrutura do Nó de lista encadeada.
 *Possui um Value e ponteiros para o próximo nó.
 */
struct node
{
    Value k;
    struct node *next;
};

typedef struct node Node;
/*Estrutura da Lista. Possui ponteiro para a primeira posição*/
struct list
{
    Node *first;
};

/*Inicializa a lista, alocando memória e inicializa os ponteiros*/
List *list_init()
{
    List *l = malloc(sizeof(*l));

    l->first = NULL;

    return l;
}
/*Inicializa o nó, alocando memória e inicializando os ponteiros*/
Node *node_init(const Value *k)
{
    Node *n = malloc(sizeof(*n));
    n->k = *k;
    n->next = NULL;
    return n;
}

/*Insere na lista*/
void list_insere(List *list, const Value *k)
{
    Node *n = node_init(k);
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
void list_free(List *l)
{
    if (l != NULL)
    {
        Node *atual = l->first;
        Node *next = NULL;
        while (atual != NULL)
        {
            next = atual->next;
            free(atual);
            atual = next;
        }

        free(l);
    }
}

void list_iterate(List *l, void (*visit)(Value *, Value *), Value *opt)
{
    if (l != NULL)
    {
        for (Node *n = l->first; n != NULL; n = n->next)
        {
            visit(&(n->k), opt);
        }
    }
}
