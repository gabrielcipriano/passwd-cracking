#ifndef TST_H
#define TST_H

#include "key.h"

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------

typedef struct node TST;
struct node {
    Value val;
    unsigned char c;
    TST *l, *m, *r;
};

TST* TST_create();
void TST_destroy(TST*);

TST *TST_insert(TST *t, Key *key, Value val, const Key* encrypted, const Key lista[R][C])
Value TST_search(TST*, Key*);

#endif
