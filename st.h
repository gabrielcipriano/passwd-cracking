#ifndef ST_H
#define ST_H

#include <stdbool.h>
#include "key.h"
typedef struct node Node;

// Create an empty symbol table.
Node *ST_init();

// Put key-value pair into the table: a[key] = val; .
Node *ST_put(Node *root, unsigned char key, Value val);


Value subset_sum_tree(Key k, Key T[N], Node *root);


// Clean up the table memory.
void ST_finish();

#endif
