#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "key.h"
#include "tst.h"
#include "list.h"
#include "list.1.h"
// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key *init_key(unsigned char s[])
{
    // Converte cada char em um int no intervalo 0-31.
    Key *k = malloc(sizeof(*k));
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < R; j++)
        {
            if (s[i] == ALPHABET[j])
            {
                k->digit[i] = j;
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

int addT(int a, int b)
{
    int sum = a + b;
    return sum % R;
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
Key subset_sum(Key k, Key *T[N]) // N*C
{
    Key sum = {{0}};
    for (int i = 0; i < N; i++)
    {
        int b = bit(&k, i); //Constante

        if (b)
        {
            add_onfirst(&sum, (T[i])); //C
            // printf("%2d   ", i);      // Para teste.
            // print_key(&(T[i]));       // Para teste.
        }
    }
    return sum;
}

int compareK(Key *a, Key *b)
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

bool equalN(Key a, Key b, int n)
{

    int ini = C - 1;
    int fim = ini - n;
    for (int i = ini; i >= fim; i--)
    {
        if (a.digit[i] != b.digit[i])
        {
            return false;
        }
    }

    return true;
}

void init_lista_key(Key(lista[R][C]), Key *T[N]) // R*C*N
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
                    add_onfirst(&sum, (T[b + (p * B)]));
                }
            }
            (lista[l][p]) = sum;
        }
    }
}

void dec_forca_bruta(Key encrypted, Key *T[N]) // ((R^C) * (B*C² + 2C)
{
    Key k;

    // Quantidade de combinações
    //double tam = pow(R, C);
    Key zero = {{0}};

    do
    {
        Key passwordEncrypted = subset_sum(k, T);

        if (equal(&encrypted, &passwordEncrypted)) //C obrigatorio, não tem como reduzir isso
        {
            print_key_char(&k);
        }
        add1(&k); //C
    } while (!equal(&k, &zero));
}

int bit_l(unsigned char k, int i)
{
    return (k >> (B - 1 - i % B)) & 1;
}

// T(C) = R*(2C + T(C - 1))
//      = R*(C + R*(C - 1 + T(C - 2)))
//      = R*(C + R*(C - 1 + R*(C - 2 + T(C - 3))))
void dec_symbol_table_rec(Key encrypted, Key prefix, int pos, Key lista[R][C], Key sum_anterior)
{
    // Base case: pos é C
    if (pos == 0)
    {
        if (equal(&sum_anterior, &encrypted))
        {
            print_key_char(&prefix);
        }
        return;
    }
    // Adicionar caracteres 1 por 1 e mudar posicao
    for (int i = 0; i < R; ++i) // R*(2C + T(C - 1))
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_anterior, &(lista[i][pos - 1]));

        dec_symbol_table_rec(encrypted, prefix, pos - 1, lista, novo_key);
    }
}

void dec_symbol_table(Key encrypted, Key *T[N]) // R*C*N + R*(2C + g(C - 1))
{
    Key pass = {{0}};
    Key enc = {{0}};

    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    dec_symbol_table_rec(encrypted, pass, C, lista, enc);
}

// int hashing(Key *key, Value *val)
// {
// }

typedef struct
{
    int tam;
    List1 **hash;
} Hash_table;

Hash_table *hash_init(int tam)
{
    Hash_table *h = malloc(sizeof(*h));
    h->tam = tam;
    h->hash = malloc(sizeof(*(h->hash)) * tam);
    for (int i = 0; i < h->tam; i++)
    {
        h->hash[i] = list_init1();
    }
    return h;
}

int horner(Key *s, int m)
{
    int h = 0;
    for (int i = 0; i < C; i++)
    {
        h = (251 * h + (s->digit[i])) % m;
    }
    return h;
}

void hash_insert(Hash_table *h, Key *k, Value *v)
{
    int hash = horner(k, h->tam);

    list_insere1(h->hash[hash], v, k);
}

List1 *hash_search(Hash_table *h, Key *k)
{
    int hash = horner(k, h->tam);
    List1 *l = h->hash[hash];
    return l;
}

void hash_destroy(Hash_table *h)
{
    if (h != NULL)
    {
        for (int i = 0; i < h->tam; i++)
        {
            list_free1(h->hash[i]);
        }
        free(h->hash);
        free(h);
    }
}

void dec_symbol_table3(Key *encrypted, Key *T[N])
{
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};

    int tam = pow(R, C / 2);

    Hash_table *h = hash_init(tam);

    while (k.digit[C / 2 - 1] == 0)
    {
        Key passwordEncrypted = {{0}};
        for (int p = C - 1; p >= C / 2; p--)
        {
            add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }
        hash_insert(h, &k, &passwordEncrypted);
        add1(&k);
    }

    List1 *l = hash_search(h, encrypted);

    for (Node1 *n = l->first; n != NULL; n = n->next)
    {
        if (equal(&(n->k), encrypted))
            print_key_char(&(n->v));
    }

    Key zero = {{0}};
    Key maximo = k;
    do
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C; p++)
        {
            add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, &passwordEncrypted);

        l = hash_search(h, &passwordEncrypted);

        for (Node1 *n = l->first; n != NULL; n = n->next)
        {
            Key addtq = add(&(n->k), &passwordEncrypted);
            if (equal(&addtq, encrypted))
            {
                Key t = add(&k, &(n->v));

                print_key_char(&t);
            }
        }

        add_onfirst(&k, &maximo);
    } while (!equal(&zero, &k));

    hash_destroy(h);
}

#define max 4

//      = R*(C + R*(C - 1 + R*(C - 2 + T(C - 3))))
void dec_symbol_table2_rec(const Key *encrypted, Key prefix, int pos, Key lista[R][C], Key sum_anterior, TST *tst)
{
    // Base case: pos é C
    if (pos == 0)
    {
        sub(encrypted, &sum_anterior);

        List *l = TST_search(tst, &sum_anterior);
        list_iterate(l, print_key_char_soma, &prefix);
        return;
    }
    // Adicionar caracteres 1 por 1 e mudar posicao
    for (int i = 0; i < R; ++i) // R*(2C + T(C - 1))
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_anterior, &(lista[i][pos - 1]));

        dec_symbol_table2_rec(encrypted, prefix, pos - 1, lista, novo_key, tst);
    }
}

void dec_symbol_table2(const Key *encrypted, Key *T[N])
{
    clock_t tic = clock();
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};
    TST *tst = TST_create();

    int maximum = C / 2;
    if (maximum > max)
    {
        maximum = C - max;
    }
    while (k.digit[maximum - 1] == 0)
    {
        Key passwordEncrypted = {{0}};
        for (int p = C - 1; p >= maximum; p--)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }
        tst = TST_insert(tst, &passwordEncrypted, &k);
        add1(&k);
    }

    List *l = TST_search(tst, encrypted);

    Key zero = {{0}};
    list_iterate(l, print_key_char_soma, &zero);

    Key passwordEncrypted = {{0}};

    dec_symbol_table2_rec(encrypted, k, maximum, lista, passwordEncrypted, tst);

    // do
    // {
    //     Key passwordEncrypted = {{0}};
    //     for (int p = 0; p < maximum; p++)
    //     {
    //         if (k.digit[p] != 0)
    //             add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
    //     }

    //     sub(encrypted, &passwordEncrypted);

    //     l = TST_search(tst, &passwordEncrypted);
    //     list_iterate(l, print_key_char_soma, &k);
    //     add_onfirst(&k, &maximo);
    // } while (!equal(&zero, &k));

    TST_destroy(tst);

    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
}
