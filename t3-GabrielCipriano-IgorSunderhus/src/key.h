
#include <stdlib.h>
#include <stdbool.h>
#ifndef KEY_H
#define KEY_H

#define C 10 // Número de caracteres na senha.
#define C_CUSTOM (C / 2)
#define B 5        // Número de bits por caractere.
#define R (1 << B) // Tamanho do alfabeto (sempre = 32).
#define N (B * C)  // Número de bits por senha.

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

// Um inteiro módulo R formado por C dígitos. O array está contido
// dentro de uma estrutura para facilitar a gerência de memória e
// a passagem de parâmetros nas funções.
typedef struct
{
    unsigned char digit[C];
} Key;

// Estrutura para guardar metade de uma key
typedef struct
{
    unsigned char digit[C_CUSTOM];
} Key_custom;

// Estrutura contendo um par chave-valor
typedef struct
{
    Key k;
    Key_custom v;
} Item;

typedef Key Value;

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]);
Key *init_key_ptr(Key *s);
Key_custom *init_key_custom_ptr(Key_custom *s);

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key *k);
void print_key_custom(Key_custom *k);

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key *k);
void print_key_char_soma(Key *a, Key *b);
void print_key_char_soma_custom(Key_custom *a, Key_custom *b);

// Retorna o i-ésimo bit de k.
int bit(Key *k, int i);
int bit_l(unsigned char k, int i);

// Retorna a + b (mod 2^N) .
Key add(Key *a, Key *b);
Key add_custom(Key_custom *a, Key_custom *b);
void add1(Key *a);
void add1_custom(Key_custom *a);
void add_onfirst(Key *a, const Key *b);

// Retorna a - b (mod 2^N)
void sub(const Key *a, Key *b);

// Verifica que duas senhas são iguais
bool equal(const Key *a, const Key *b);
bool equal_custom(const Key_custom *a, const Key_custom *b);

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]);
Key subset_sum_custom(Key *k, Key lista[R][C]);

// Matriz de valores relativos
void init_lista_key(Key(lista[R][C]), Key T[N]);

#endif
