#include "key.h"
#include "list.h"
#include <stdlib.h>

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
typedef struct hash_table Hash_table;

Hash_table *hash_init(unsigned long tam);

unsigned long horner(Key *s, unsigned long m);

void hash_insert(Hash_table *h, Key *k, Key_custom *v);

Item *hash_search(Hash_table *h, bool (*fn)(const Key *, const Key *), Key *k);

void hash_destroy(Hash_table *h);

#endif
