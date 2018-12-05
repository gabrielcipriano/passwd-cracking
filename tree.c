#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

// Um nó de árvore AVL que lida com duplicatas
struct node
{
    Key key;
    // List *val;
    Value val;
    struct node *left;
    struct node *right;
    int height;
};

Tree *tree_init()
{
    return NULL;
}

// retorna o tamanho da arvore
int height(Tree *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

// Retorna o maior dos dois itens
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// aloca um novo nó com a chave passada por parametro
Tree *newNode(const Key *key, const Value *val)
{
    Tree *node = malloc(sizeof(*node));
    node->key = *key;
    // node->val = list_init();
    // node->val = list_insere(node->val, val);
    node->val = *val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // adicionada as folhas da arvore
    return (node);
}

// Função para rotacionar a arvore a direita na subarvore com raiz em y
Tree *rightRotate(Tree *y)
{
    Tree *x = y->left;
    Tree *T2 = x->right;

    // rotaciona
    x->right = y;
    y->left = T2;

    // atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Função para rotacionar a arvore a esquerda na subarvore com raiz em x
Tree *leftRotate(Tree *x)
{
    Tree *y = x->right;
    Tree *T2 = y->left;

    // rotaciona
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// retorna o fator de balanço da arvore
int getBalance(Tree *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// adiciona novo item
Tree *tree_insert(Tree *node, const Key *key, const Value *val)
{
    /* Adiciona um item normalmente na arvore */
    if (node == NULL)
    {
        return (newNode(key, val));
    }

    // se já existe um item com aquela chave, incrementa e retorna o mesmo
    // if (equal(key, &(node->key)))
    // {
    //     node->val = list_insere(node->val, val);
    //     return node;
    // }

    int cmp = compare(key, &(node->key));
    /* percore a arvore em pre ordem */
    if (cmp == -1)
        node->left = tree_insert(node->left, key, val);
    else
        node->right = tree_insert(node->right, key, val);

    // /* Atualiza a altura do nó ancestral */
    // node->height = max(height(node->left), height(node->right)) + 1;

    // /* Pega o fator de balanço da arvore pra ver se a inserção desbalanceou a arvore */
    // int balance = getBalance(node);

    // // se o no esta desbalanceado

    // // Desbalanceada a esquerda duas vezes, rotaciona uma vez para a direita
    // if (balance > 1)
    // {
    //     int cmpL = compare(key, &(node->left->key));
    //     if (cmpL == -1)
    //         return rightRotate(node);
    // }

    // // Desbalanceada a direita duas vezes, rotaciona uma vez para a esquerda
    // if (balance < -1)
    // {

    //     int cmpR = compare(key, &(node->right->key));
    //     if (cmpR == 1)
    //     {
    //         return leftRotate(node);
    //     }
    // }

    // // Desbalanceada a esquerda e depois a direita, rotaciona a subarvore da esquerda para a esquerda e subarvore atual a direita
    // if (balance > 1)
    // {
    //     int cmpL = compare(key, &(node->left->key));
    //     if (cmpL == 1)
    //     {
    //         node->left = leftRotate(node->left);
    //         return rightRotate(node);
    //     }
    // }

    // //  Desbalanceada a direita e depois a esquerda, rotaciona a subarvore da direita para a direita e subarvore atual para esquerda
    // if (balance < -1)
    // {

    //     int cmpR = compare(key, &(node->right->key));
    //     if (cmpR == -1)
    //     {
    //         node->right = rightRotate(node->right);
    //         return leftRotate(node);
    //     }
    // }

    return node;
}

/* retorna o nó com menor valor da arvore */
Tree *search_rec(Tree *t, Key *k)
{
    if (t == NULL)
    {
        return NULL;
    }
    int cmp = compare(k, &(t->key));

    if (cmp == -1)
    {
        return search_rec(t->left, k);
    }
    else if (cmp == 1)
    {
        return search_rec(t->right, k);
    }
    else
    {
        return t;
    }
}

Value *tree_search(Tree *t, Key *k)
{
    t = search_rec(t, k);
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        return &(t->val);
    }
}

// apaga a arvore toda
void delete_tree(Tree *node)
{
    if (node == NULL)
        return;
    delete_tree(node->left);
    delete_tree(node->right);
    //list_free(node->val);
    free(node);
}
