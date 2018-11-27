#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef struct node Node;

struct node {
    Key key;      // Sorted by key.
    Value val;    // Associated data.
    Node *l, *r;  // Left and right subtrees.
};

Node *root; // Root of BST.

static Node* create_node(Key key, Value val) {
    Node *n = malloc(sizeof *n);
    n->key = key;
    n->val = val;
    n->l = n->r = NULL;
    return n;
}

void ST_init(int maxN) {
    root = NULL;
}

static void rec_finish(Node *n) {
    if (n == NULL) { return; }
    rec_finish(n->l);
    rec_finish(n->r);
    free(n);
}

void ST_finish() {
    rec_finish(root);
}

static Node* rec_put(Node *n, Key key, Value val) {
    if (n == NULL) { return create_node(key, val); }
    int cmp = compare(key, n->key);
    if      (cmp < 0) { n->l = rec_put(n->l, key, val); }
    else if (cmp > 0) { n->r = rec_put(n->r, key, val); }
    else /*cmp == 0*/ { n->val = val; }
    return n;
}

void ST_put(Key key, Value val) {
    root = rec_put(root, key, val);
}

static Value rec_get(Node *n, Key key) {
    if (n == NULL) { return NULL_Value; }
    int cmp = compare(key, n->key);
    if      (cmp < 0) { return rec_get(n->l, key); }
    else if (cmp > 0) { return rec_get(n->r, key); }
    else /*cmp == 0*/ { return n->val; }
}

Value ST_get(Key key) {
    return rec_get(root, key);
}

static void rec_traverse(Node *n, void (*visit)(Key,Value)) {
    if (n == NULL) { return; }
    rec_traverse(n->l, visit);
    visit(n->key, n->val);
    rec_traverse(n->r, visit);
}

void ST_traverse(void (*visit)(Key,Value)) {
    rec_traverse(root, visit);
}
