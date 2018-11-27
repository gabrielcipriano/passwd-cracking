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

void ST_put(Key key, Value val) {
    if (root == NULL) { root = create_node(key, val); return; }

    Node *parent = NULL, *n = root;
    while (n != NULL) {
        parent = n;
        int cmp = compare(key, n->key);
        if      (cmp < 0) { n = n->l; }
        else if (cmp > 0) { n = n->r; }
        else /*cmp == 0*/ { n->val = val; return; }
    }

    Node *new = create_node(key, val);
    int cmp = compare(key, parent->key);
    if   (cmp < 0) { parent->l = new; }
    else           { parent->r = new; }
}

Value ST_get(Key key) {
    Node *n = root;
    while (n != NULL) {
        int cmp = compare(key, n->key);
        if      (cmp < 0) { n = n->l; }
        else if (cmp > 0) { n = n->r; }
        else /*cmp == 0*/ { return n->val; }
    }
    return NULL_Value;
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
