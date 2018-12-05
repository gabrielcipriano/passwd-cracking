#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <unistd.h>

#include "key.h"
#include "list.h"
#include "tst.h"
#include "list.1.h"
#include "tree.h"
#include "hash.h"

void dec_symbol_table2(Key *encrypted, Key T[N])
{
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};
    int maximum = C / 2;
    unsigned long tam;
    if (maximum > 5)
    {
        tam = pow(R, 5) / 4;
        maximum = C - 5;
    }
    else
    {
        tam = pow(R, C / 2) / 4;
    }

    Hash_table *h = hash_init(tam);
    printf("t\n");

    while (k.digit[maximum - 1] == 0)
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        hash_insert(h, &passwordEncrypted, &k);
        add1(&k);
    }

    Value *l = hash_search(h, encrypted);

    Key zero = {{0}};
    if (l != NULL)
        print_key_char_soma(l, &zero);
    // list_iterate(l, print_key_char_soma, &zero);

    Key maximo = k;
    do
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, &passwordEncrypted);

        l = hash_search(h, &passwordEncrypted);
        if (l != NULL)
        {
            print_key_char_soma(l, &k);
        }

        add_onfirst(&k, &maximo);
    } while (!equal(&zero, &k));
    sleep(3);
    hash_destroy(h);
}

// hash(senha) = hash(a) + hash(b) + hash(c);
// tst = hash(a);
// tst2 = hash(b);
// hash(a) = hash(senha) - hash(b) - hash(c);
// hash(b) = hash(senha) - hash(a) - hash(c);
// hash(b) = hash(senha) - hash(c);

//hash(a) = hash(senha) - hash(senha) + hash(c) - hash(c)

void dec_symbol_table(const Key *encrypted, Key T[N])
{

    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key k = {{0}};
    TST *tst = TST_create();

    int maximum = C / 2;

    if (maximum > 4)
    {
        maximum = C - 4;
    }

    // dec_symbol_table2_rec(maximum, k, C, lista, k, &tst);
    while (k.digit[maximum - 1] == 0)
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        tst = TST_insert(tst, &passwordEncrypted, &k);
        add1(&k);
    }

    List *l = TST_search(tst, encrypted);

    Key zero = {{0}};
    if (l != NULL)
        list_iterate(l, print_key_char_soma, &zero);

    Key atual = k;

    do
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, &passwordEncrypted);

        l = TST_search(tst, &passwordEncrypted);
        if (l != NULL)
        {
            list_iterate(l, print_key_char_soma, &k);
            print_key(&passwordEncrypted);
            printf("\n");
        }
        add_onfirst(&k, &atual);
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