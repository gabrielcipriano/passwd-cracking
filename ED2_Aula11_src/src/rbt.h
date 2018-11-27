#ifndef RBT_H
#define RBT_H

#include <stdbool.h>

// ----------------------------------------------------------------------------

typedef int Key;
typedef int  Value;

#define NULL_Key   -1
#define NULL_Value -1

#define compare(A, B) (A - B)

// ----------------------------------------------------------------------------

#define RED     true
#define BLACK   false

typedef struct node RBT;

struct node {
    Key key;
    Value val;
    bool color;
    RBT *l, *r;
};

RBT* RBT_create();
void RBT_destroy(RBT*);

int RBT_height(RBT*);

RBT* RBT_insert(RBT*, Key, Value);

#endif
