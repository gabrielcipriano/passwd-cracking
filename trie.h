#ifndef TRIE_H
#define TRIE_H

#include "key.h"

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

typedef struct node Trie;

#define R 256

struct node
{
    Value val;
    Trie *next[R];
};

Trie *Trie_create();
void Trie_destroy(Trie *);

Trie *Trie_insert(Trie *, Key *, Value);
Value Trie_search(Trie *, Key *);

#endif
