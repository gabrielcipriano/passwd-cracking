#ifndef TST_H
#define TST_H

#include "key.h"
#include "list.h"

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

typedef struct node TST;
struct node
{
    List *val;
    unsigned char c;
    TST *l, *m, *r;
};

TST *TST_create();
void TST_destroy(TST *);

TST *TST_insert(TST *t, const Key *, const Value *);
List *TST_search(TST *, const Key *);

#endif
