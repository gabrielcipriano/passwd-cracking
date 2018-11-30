#include <stdio.h>
#include "key.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "st.h"
// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[])
{
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    k.digit[0] = 0;
    for (int i = 1; i <= C; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (s[i - 1] == ALPHABET[j])
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
    for (int i = 0; i <= C; i++)
    {
        printf("%c", ALPHABET[(unsigned char)(k->digit[i])]);
    }
    printf("  ");
    for (int i = 0; i <= C; i++)
    {
        printf("%2d ", k->digit[i]);
    }
    printf("  ");
    int lim = N + B;
    for (int i = 0; i < lim; i++)
    {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(const Key *k)
{
    for (int i = 0; i <= C; i++)
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
Key add(const Key *a, const Key *b)
{
    Key c = {{0}};
    int carry = 0;
    for (int i = C; i > 0; i--)
    {
        int sum = a->digit[i] + b->digit[i] + carry;
        c.digit[i] = sum % R;
        carry = sum >= R;
    }
    c.digit[0] = carry;
    return c;
}
void add1(Key *a)
{
    int sum = a->digit[C] + 1;

    a->digit[C] = sum % R;
    int carry = sum >= R;
    int i = C - 1;
    while (i > 0 && carry != 0)
    {
        sum = a->digit[i] + carry;
        a->digit[i] = sum % R;
        carry = sum >= R;
        i--;
    }
    if (i == 0)
    {
        a->digit[i] = carry;
    }
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(const Key *k, Key T[N])
{
    Key sum = {{0}};

    int i;
    int lim = N + B;
    for (i = B; i < lim; i++)
    {
        int b = bit(k, i);

        if (b)
        {
            Key temp = add(&sum, &(T[i - B]));

            if ((compareK(&sum, &temp)) > 0)
            {
                printf("antes\n");
                printf("maior\n");
                printf("depois\n\n");
            }

            sum = temp;

            // printf("%2d   ", i); // Para teste.
            // print_key(&T[i]);    // Para teste.
            printf("sum: ");
            print_key(&sum); // Para teste.
            printf("\n");
        }
    }

    return sum;
}

int compareK(const Key *a, const Key *b)
{

    for (int i = 0; i <= C; i++)
    {
        if (a->digit[i] > b->digit[i])
        {
            return 1;
        }
        if (a->digit[i] < b->digit[i])
        {
            return -1;
        }
        //sumA += a->digit[i] * j;
        // sumB += b->digit[i] * j;
        // j--;
    }
    //return sumA - sumB;

    // for (int i = 0; i < N; i++)
    // {
    //     int ba = bit(a, i);
    //     int bb = bit(b, i);
    //     if (ba > bb)
    //     {
    //         return 1;
    //     }
    //     if (ba < bb)
    //     {
    //         return -1;
    //     }
    // }

    return 0;
}

bool equal(const Key *a, const Key *b)
{
    for (int i = 1; i <= C; i++)
    {
        if (a->digit[i] != b->digit[i])
        {
            return false;
        }
    }

    print_key(a);
    return true;
}

void dec_forca_bruta(const Key encrypted, Key T[N])
{
    Key k;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = subset_sum(&k, T);
        if (equal(&encrypted, &passwordEncrypted))
        {
            print_key_char(&k);
        }
        add1(&k);
    }
}

#include <unistd.h>

void initi_lista_ley(Key(lista[R][C]), Key T[N])
{
    for (int l = 0; l < R; l++)
    {
        for (int p = 1; p <= C; p++)
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
            (lista[l][p - 1]) = sum;
        }
    }
}
int bit_l(unsigned char k, int i)
{
    return (k >> (B - 1 - i % B)) & 1;
}
typedef struct
{
    Key k;
    unsigned char c;

} ItemPilha;

typedef struct
{
    Key pilha[C + 1];
    int topo;
} Pilha;

Pilha Pilha_init()
{
    Key k = {{0}};
    Pilha p;
    for (int i = 0; i <= C; i++)
    {
        p.pilha[i] = k;
    }
    p.topo = 0;
    return p;
}

void print_pilha(Pilha *p)
{
    for (int i = 0; i <= p->topo && i <= C + 1; i++)
    {
        printf("i: %d ", i);
        print_key(&(p->pilha[i]));
    }
    printf("\n\n");
}
Pilha empilha(Pilha p, Key k)
{

    p.topo++;
    p.pilha[p.topo] = k;

    return p;
}

void desempilha(Pilha *p)
{
    p->topo--;
}

Key olha_topo(Pilha *p)
{
    return p->pilha[p->topo];
}

Key subset_sum_custom_teste(Key *k, Key T[N], int pos)
{
    Key sum = {{0}};

    //int i;

    for (int p = pos; p < C; p++)
    {
        for (int b = 0; b < B; b++)
        {
            int bitt = bit_l(k->digit[p], b);
            if (bitt)
            {
                sum = add(&sum, &(T[b + (p * B)]));
            }
        }
    }

    return sum;
}

Key testealo = {{15, 0, 18, 18, 22}};

void teste_symbol_table_rec(const Key *encrypted, Key prefix, int pos, Key lista[R][C], Pilha p)
{
    // Base case: pos is 0,
    // print prefix
    if (pos == 0)
    {

        Key topo = olha_topo(&p);
        if (equal(&topo, encrypted))
        {
            print_key_char(&prefix);
        }
        return;
    }

    // One by one add all characters
    // from set and recursively
    // call for pos equals to pos-1
    Key sum_atual = olha_topo(&p);

    for (int i = 0; i < R; ++i)
    {
        // Next character of input added
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_atual, &(lista[i][pos - 1]));
        // if (equal(&prefix, &testealo))
        // {
        //     print_key(&novo_key);
        // }

        // int cmp = compareK(&novo_key, &encrypted);

        // if (cmp > 0)
        // {
        //     continue;
        // }
        // else if (cmp == 0)
        // {
        //     print_key_char(&prefix);
        //     continue;
        // }

        Pilha nova = empilha(p, novo_key);

        teste_symbol_table_rec(encrypted, prefix, pos - 1, lista, nova);
    }
}

void teste_symbol_table(const Key encrypted, Key T[N])
{

    Key pass = {{0}};
    Key lista[R][C];

    initi_lista_ley(lista, T);
    Pilha p = Pilha_init();
    teste_symbol_table_rec(&encrypted, pass, C, lista, p);
}

void novo_(const Key encrypted, Key T[N])
{
    Key lista[R][C];
    initi_lista_ley(lista, T);

    Key k = {{0}};

    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = {{0}};
        int j;
        for (j = C - 1; j >= 0; j--)
        {

            //Key *temp = (lista[k.digit[j]][j]);
            if (k.digit[j] != 0)
                passwordEncrypted = add(&passwordEncrypted, &(lista[k.digit[j]][j]));
        }

        if (equal(&encrypted, &passwordEncrypted))
        {
            print_key_char(&k);
        }
        add1(&k);
    }
}
