#include <stdio.h>
#include <stdlib.h>
#include "tst.h"

TST *TST_create()
{
    return NULL;
}

void TST_destroy(TST *t)
{
    if (t == NULL)
    {
        return;
    }
     list_free(t->val);
    TST_destroy(t->l);
    TST_destroy(t->m);
    TST_destroy(t->r);
    free(t);
}

TST *create_node()
{
    TST *t = malloc(sizeof *t);
    t->val = list_init();
    t->l = NULL;
    t->m = NULL;
    t->r = NULL;
    return t;
}

TST *rec_insert(TST *t, const Key *key, const Value *val, int d)
{
    unsigned char c = key->digit[d];
    if (t == NULL)
    {
        t = create_node();
        t->c = c;
    }
    if (c < t->c)
    {
        t->l = rec_insert(t->l, key, val, d);
    }
    else if (c > t->c)
    {
        t->r = rec_insert(t->r, key, val, d);
    }
    else if (d < C - 1)
    {
        t->m = rec_insert(t->m, key, val, d + 1);
    }
    else
    {
        // t->val = *val;
        list_insere(t->val, val);
    }
    return t;
}

TST *TST_insert(TST *t, const Key *key, const Value *val)
{
    return rec_insert(t, key, val, 0);
}

TST *rec_search(TST *t, const Key *key, int d)
{
    if (t == NULL)
    {
        return NULL;
    }
    unsigned char c = key->digit[d];
    if (c < t->c)
    {
        return rec_search(t->l, key, d);
    }
    else if (c > t->c)
    {
        return rec_search(t->r, key, d);
    }
    else if (d < C - 1)
    {
        return rec_search(t->m, key, d + 1);
    }
    else
    {
        return t;
    }
}

List *TST_search(TST *t, const Key *key)
{
    t = rec_search(t, key, 0);
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        return t->val;
    }
}
