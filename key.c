#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "key.h"
#include "trie.h"
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
void print_key(const Key *k)
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
void print_key_char(const Key *k)
{
    for (int i = 0; i < C; i++)
    {

        printf("%c", ALPHABET[(unsigned char)(k->digit[i])]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(const Key *k, int i)
{
    return (k->digit[i / B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(const Key *a, const Key *b) //C
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
Key subset_sum(const Key *k, const Key T[N]) // N*C
{
    Key sum = {{0}};

    for (int i = 0; i < N; i++)
    {
        int b = bit(k, i); //Constante

        if (b)
        {
            sum = add(&sum, &(T[i])); //C

            // printf("%2d   ", i); // Para teste.
            // print_key(T[i]);     // Para teste.
        }
    }

    return sum;
}

int compareK(const Key *a, const Key *b)
{

    for (int i = N - 1; i >= 0; i--)
    {
        int ba = bit(a, i);
        int bb = bit(b, i);
        if (ba < bb)
        {
            return -1;
        }
        if (ba > bb)
        {
            return 1;
        }
    }

    return 0;
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

bool equalN(const Key *a, const Key *b, int n)
{

    int ini = C - 1;
    int fim = ini - n;
    for (int i = ini; i >= fim; i--)
    {
        if (a->digit[i] != b->digit[i])
        {
            return false;
        }
    }

    return true;
}

void init_lista_key(Key(lista[R][C]), const Key T[N]) // R*C*N
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
                    sum = add(&sum, &(T[b + (p * B)]));
                }
            }
            (lista[l][p]) = sum;
        }
    }
}

void dec_forca_bruta(const Key *encrypted, const Key T[N]) // ((R^C) * (5*C² + 2C)
{
    Key k;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++) //(R^C)*(N*C + 2C)
    {

        Key passwordEncrypted = subset_sum(&k, T);

        if (equal(encrypted, &passwordEncrypted)) //C obrigatorio, não tem como reduzir isso
        {
            print_key_char(&k);
        }
        add1(&k); //C
    }
}

int bit_l(unsigned char k, int i)
{
    return (k >> (B - 1 - i % B)) & 1;
}

// T(C) = R*(2C + T(C - 1))
//      = R*(C + R*(C - 1 + T(C - 2)))
//      = R*(C + R*(C - 1 + R*(C - 2 + T(C - 3))))
void dec_symbol_table_rec(const Key *encrypted, Key prefix, int pos, Key lista[R][C], Key *sum_anterior)
{
    // Base case: pos é C
    if (pos == 0)
    {
        if (equal(sum_anterior, encrypted))
        {
            print_key_char(&prefix);
        }
        return;
    }
    // Adicionar caracteres 1 por 1 e mudar posicao
    for (int i = 0; i < R; ++i) // R*(2C + T(C - 1))
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(sum_anterior, &(lista[i][pos - 1]));

        dec_symbol_table_rec(encrypted, prefix, pos - 1, lista, &novo_key);
    }
}

void dec_symbol_table(const Key *encrypted, const Key T[N]) // R*C*N + R*(2C + g(C - 1))
{
    Key pass = {{0}};
    Key enc = {{0}};

    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    dec_symbol_table_rec(encrypted, pass, C, lista, &enc);
}
