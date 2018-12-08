#include "key.h"
#include "list.h"
#include <stdlib.h>

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

// estrutura hash
typedef struct hash_table Hash_table;

// inicia uma hash de tamanho tam
Hash_table *hash_init(unsigned long tam);

// calcula hash
unsigned long horner(Key *s, unsigned long m);

// insere na hash
void hash_insert(Hash_table *h, Key *k, Key_custom *v);

// procura na hash
Item *hash_search(Hash_table *h, bool (*fn)(const Key *, const Key *), Key *k);

// destroi a hash
void hash_destroy(Hash_table *h);

#endif
