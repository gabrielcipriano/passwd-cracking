#ifndef TRIE_H
#define TRIE_H

#include "key.h"

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

typedef struct node Trie;

struct node
{
    Value val;
    Trie *next[R];
};

Trie *Trie_create();
void Trie_destroy(Trie *);

Trie *Trie_insert(Trie *t, Key *key, const Key lista[R][C], const Key *encrypted);
Value Trie_search(Trie *, Key *);

#endif
