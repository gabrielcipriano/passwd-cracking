#include "key.h"
#include "list.h"
#ifndef TREE_H
#define TREE_H

// Estrutura para arvore AVL
typedef struct node Tree;

//Inicia uma arvore
Tree *tree_init();
// Insere um item na arvore
Tree *tree_insert(Tree *t, const Key *k, const Value *val);

Value *tree_search(Tree *t, Key *k);

// apaga a arvore
void delete_tree(Tree *node);

#endif /* AVLTREE_H */