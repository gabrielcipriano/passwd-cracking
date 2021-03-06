
#include <stdlib.h>
#ifndef KEY_H
#define KEY_H

#define C 6        // Número de caracteres na senha.
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

typedef Key Value;

static const Key NULL_Value = {{R + 1}};

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]);

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(const Key *k);

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(const Key *k);

// Retorna o i-ésimo bit de k.
int bit(const Key *k, int i);
int bit_l(unsigned char k, int i);

// Retorna a + b (mod 2^N) .
Key add(const Key *a,const Key *b);
void add1(Key *a);

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(const Key *k, Key T[N]);

// Lista todas as possíveis senhas com um algoritmo de força bruta
void dec_forca_bruta(const Key encrypted, Key T[N]);

// Lista todas as possíveis senhas com um algoritmo de tabela de simbolos
void dec_symbol_table(const Key encrypted, Key T[N]);

void teste_symbol_table(const Key *encrypted, Key T[N]);
void dec_symbol_table_new(const Key encrypted, Key T[N]);
void novo_(const Key encrypted, Key T[N]);
// COmpara duas chaves
int compareK(const Key *a, const Key *b);

#endif
