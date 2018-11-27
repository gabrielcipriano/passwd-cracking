#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

// Unchanged from BST.
RBT* RBT_create() {
    return NULL;
}

// Unchanged from BST.
void RBT_destroy(RBT *h) {
    if (h != NULL) {
        RBT_destroy(h->l);
        RBT_destroy(h->r);
        free(h);
    }
}

// Unchanged from BST.
int RBT_height(RBT *h) {
    if (h == NULL) {
        return -1;
    }
    int lh = RBT_height(h->l);
    int rh = RBT_height(h->r);
    if (lh > rh) {
        return lh + 1;
    } else {
        return rh + 1;
    }
}

RBT* create_node(Key key, Value val, bool color) {
    RBT *h = malloc(sizeof *h);
    h->key = key;
    h->color = color;
    h->l = h->r = NULL;
    return h;
}

bool is_red(RBT *x) {
  if (x == NULL) return BLACK;
  return x->color; //RED == true
}

RBT* rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

RBT* rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

void flip_colors(RBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

RBT* RBT_insert(RBT *h, Key key, Value val) {
  // Insert at bottom and color it red.
  if (h == NULL) { return create_node(key, val, RED); }

  int cmp = compare(key, h->key);
  if      (cmp < 0) { h->l = RBT_insert(h->l, key, val); }
  else if (cmp > 0) { h->r = RBT_insert(h->r, key, val); }
  else /*cmp == 0*/ { h->val = val; }

  // Lean left.
  if (is_red(h->r) && !is_red(h->l))    { h = rotate_left(h); }
  // Balance 4-node.
  if (is_red(h->l) &&  is_red(h->l->l)) { h = rotate_right(h); }
  // Split 4-node.
  if (is_red(h->l) &&  is_red(h->r))    { flip_colors(h); }

  return h;
}

Value search(RBT *n, Key key) {
  while (n != NULL) {
    int cmp;
    cmp = compare(key, n->key);
    if      (cmp < 0) n = n->l;
    else if (cmp > 0) n = n->r;
    else         return n->val;
  }
  return NULL_Value;
}
