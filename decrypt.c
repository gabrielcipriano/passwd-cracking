#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "key.h"
#include "list.h"
#include "tst.h"
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

void dec_symbol_table(Key encrypted, Key T[N]) // R*C*N + R*(2C + g(C - 1))
{
    Key pass = {{0}};
    Key enc = {{0}};

    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    dec_symbol_table_rec(encrypted, pass, C, lista, enc);
}

typedef struct
{
    int tam;
    TST **hash;
} Hash_table;

Hash_table *hash_init(int tam)
{
    Hash_table *h = malloc(sizeof(*h));
    h->tam = tam;
    h->hash = malloc(sizeof(*(h->hash)) * tam);
    for (int i = 0; i < h->tam; i++)
    {
        h->hash[i] = TST_create();
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

    TST_insert(h->hash[hash], v, k);
}

List *hash_search(Hash_table *h, Key *k)
{
    int hash = horner(k, h->tam);
    List *l = TST_search(h->hash[hash], k);
    return l;
}

void hash_destroy(Hash_table *h)
{
    if (h != NULL)
    {
        for (int i = 0; i < h->tam; i++)
        {
            TST_destroy(h->hash[i]);
        }
        free(h->hash);
        free(h);
    }
}

void dec_symbol_table3(Key *encrypted, Key T[N])
{
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};

    int tam = pow(R, C / 2) / 4;

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

    List *l = hash_search(h, encrypted);

    Key zero = {{0}};
    list_iterate(l, print_key_char_soma, &zero);

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

        list_iterate(l, print_key_char_soma, &k);

        add_onfirst(&k, &maximo);
    } while (!equal(&zero, &k));

    hash_destroy(h);
}

#define max 4

//      = R*(C + R*(C - 1 + R*(C - 2 + T(C - 3))))
void dec_symbol_table2_rec(int maximum, Key prefix, int pos, Key lista[R][C], Key sum_anterior, TST **tst)
{
    // Base case: pos é C
    if (pos == maximum)
    {
        *tst = TST_insert(*tst, &sum_anterior, &prefix);
        return;
    }
    // Adicionar caracteres 1 por 1 e mudar posicao
    for (int i = 0; i < R; ++i) // R*(2C + T(C - 1))
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_anterior, &(lista[i][pos - 1]));

        dec_symbol_table2_rec(maximum, prefix, pos - 1, lista, novo_key, tst);
    }
}

void dec_symbol_table2(const Key *encrypted, Key T[N])
{

    clock_t tic = clock();
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};
    TST *tst = TST_create();

    int maximum = C / 2;
    if (maximum > 5)
    {
        maximum = C - 5;
    }

    // dec_symbol_table2_rec(maximum, k, C, lista, k, &tst);

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

    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    List *l = TST_search(tst, encrypted);

    Key zero = {{0}};
    list_iterate(l, print_key_char_soma, &zero);

    //Key passwordEncrypted = {{0}};

    //  dec_symbol_table2_rec(encrypted, k, maximum, lista, passwordEncrypted, tst);
    Key maximo = k;

    do
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < maximum; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, &passwordEncrypted);

        l = TST_search(tst, &passwordEncrypted);
        list_iterate(l, print_key_char_soma, &k);
        add_onfirst(&k, &maximo);
    } while (!equal(&zero, &k));

    TST_destroy(tst);
}

int main(int argc, char *argv[])
{
    Key encrypted; // A senha criptografada.
    Key T[N];      // A tabela T.

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./decrypt [encrypted] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    encrypted = init_key((unsigned char *)argv[1]);
    // Exibe a senha encriptada.
    printf("   ");
    print_key(&encrypted);
    printf("\n");

    // Lê a tabela T.
    unsigned char buffer[C + 1]; // Buffer temporário.
    for (int i = 0; i < N; i++)
    {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
    // Tabela de simbolos
    clock_t tic = clock();
    dec_symbol_table2(&encrypted, T);
    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}