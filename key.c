#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "key.h"

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[])
{
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (s[i] == ALPHABET[j])
            {
                k.digit[i] = j;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key *k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[(unsigned char)(k->digit[i])]);
    }
    printf("  ");
    for (int i = 0; i < C; i++)
    {
        printf("%2d ", k->digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++)
    {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key *k)
{
    for (int i = 0; i < C; i++)
    {

        printf("%c", ALPHABET[(unsigned char)(k->digit[i])]);
    }
    printf("\n");
}

void print_key_char_soma(Key *a, Key *b)
{
    Key k = add(a, b);
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[(unsigned char)(k.digit[i])]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key *k, int i)
{
    return (k->digit[i / B] >> (B - 1 - i % B)) & 1;
}
int bit_l(unsigned char k, int i)
{
    return (k >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key *a, Key *b) //C
{
    Key c = {{0}};
    int carry = 0;
    for (int i = C - 1; i >= 0; i--)
    {
        int sum = a->digit[i] + b->digit[i] + carry;
        c.digit[i] = sum % R;
        carry = sum >= R;
    }
    return c;
}

void add_onfirst(Key *a, const Key *b)
{
    int carry = 0;
    for (int i = C - 1; i >= 0; i--)
    {
        int sum = a->digit[i] + b->digit[i] + carry;
        a->digit[i] = sum % R;
        carry = sum >= R;
    }
}

void sub(const Key *a, Key *b)
{

    int carry = 0;

    // if lhs >= rhs the following will clearly work
    // if lhs < rhs we will have carry == -1 after the for loop
    // but this is ok since we are working mod 2^N
    for (int i = C - 1; i >= 0; --i)
    {
        int sub = a->digit[i] - b->digit[i] + carry;
        b->digit[i] = sub % R;
        if (sub < 0)
        {
            carry = -1;
            b->digit[i] += R;
        }
        else
            carry = 0;
    }
}

// Add 1 ao item
void add1(Key *a)
{
    int sum = a->digit[C - 1] + 1;

    a->digit[C - 1] = sum % R;
    int carry = sum >= R;
    int i = C - 2;
    while (i >= 0 && carry != 0)
    {
        sum = a->digit[i] + carry;
        a->digit[i] = sum % R;
        carry = sum >= R;
        i--;
    }
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]) // N*C
{
    Key sum = {{0}};
    for (int i = 0; i < N; i++)
    {
        int b = bit(&k, i); //Constante

        if (b)
        {
            add_onfirst(&sum, &(T[i])); //C
            // printf("%2d   ", i);      // Para teste.
            // print_key(&(T[i]));       // Para teste.
        }
    }
    return sum;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros das posições relativas
Key subset_sum_custom(Key *k, Key lista[R][C]) // C*C
{
    Key passwordEncrypted = {{0}};

    for (int p = 0; p < C; p++)
    {
        if (k->digit != 0)
            add_onfirst(&passwordEncrypted, &(lista[k->digit[p]][p]));
    }
    return passwordEncrypted;
}

bool equal(const Key *a, const Key *b)
{

    for (int i = C - 1; i >= 0; i--)
    {
        if (a->digit[i] != b->digit[i])
        {
            return false;
        }
    }

    return true;
}

int compare(const Key *a, const Key *b)
{
    for (int i = 0; i < C; i++)
    {
        if (a->digit[i] < b->digit[i])
        {
            return -1;
        }
        if (a->digit[i] > b->digit[i])
        {
            return 1;
        }
    }

    return 0;
}

void init_lista_key(Key(lista[R][C]), Key T[N]) // R*C*N
{
    for (int l = 0; l < R; l++)
    {
        for (int p = 0; p < C; p++)
        {
            Key sum = {{0}};
            for (int b = 0; b < B; b++)
            {
                int bitt = bit_l(l, b);
                if (bitt)
                {
                    add_onfirst(&sum, &(T[b + (p * B)]));
                }
            }
            (lista[l][p]) = sum;
        }
    }
}
