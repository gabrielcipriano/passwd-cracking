#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

Trie *Trie_create()
{
    return NULL;
}

void Trie_destroy(Trie *t)
{
    if (t == NULL)
    {
        return;
    }
    for (int i = 0; i < R; i++)
    {
        Trie_destroy(t->next[i]);
    }
    free(t);
}

Trie *create_node()
{
    Trie *t = malloc(sizeof *t);
    t->val = NULL_Value;
    for (int i = 0; i < R; i++)
    {
        t->next[i] = NULL;
    }
    return t;
}

Trie *rec_insert(Trie *t, Key *key, int d, const Key lista[R][C], const Key *encrypted)
{
    if (t == NULL)
    {
        t = create_node();
    }
    if (d == C)
    {
        if (equal(&(t->val), encrypted))
        {
            print_key_char(key);
        }
        return t;
    }
    unsigned char c = key->digit[d];

    t->next[c] = rec_insert(t->next[c], key, d + 1, lista, encrypted);

    if (equal(&(t->next[c]->val), &NULL_Value))
    {
        printf("teste\n");
        t->next[c]->val = add(&(t->val), &(lista[c][d]));
    }
    return t;
}

Trie *Trie_insert(Trie *t, Key *key, const Key lista[R][C], const Key *encrypted)
{
    return rec_insert(t, key, 0, lista, encrypted);
}

Trie *rec_search(Trie *t, Key *key, int d)
{
    if (t == NULL)
    {
        return NULL;
    }
    if (d == C)
    {
        return t;
    }
    unsigned char c = key->digit[d];
    return rec_search(t->next[c], key, d + 1);
}
Value Trie_search(Trie *t, Key *key)
{
    t = rec_search(t, key, 0);
    if (t == NULL)
    {
        return NULL_Value;
    }
    else
    {
        return t->val;
    }
}
