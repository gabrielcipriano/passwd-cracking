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
// Lista todas as possíveis senhas com um algoritmo de força bruta
void dec_forca_bruta(const Key *encrypted, Key T[N]) // ((R^C) * (B*C² + 2C)
{
    Key k = {{0}};

    // Quantidade de combinações
    Key zero = {{0}};
    Key lista[R][C];
    init_lista_key(lista, T);
    do
    {
        Key passwordEncrypted = subset_sum_custom(&k, lista);

        if (equal(encrypted, &passwordEncrypted)) //C obrigatorio
        {
            print_key_char(&k);
        }
        add1(&k);                //C
    } while (!equal(&k, &zero)); //C
}

void dec_symbol_table2(Key *encrypted, Key T[N])
{
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    // int maximum = C / 2;
    unsigned long tam = pow(R, C_CUSTOM) / 4;
    // if (maximum > 5)
    // {
    //     tam = pow(R, 5) / 4;
    //     maximum = C - 5;
    // }
    // else
    // {
    //     tam = pow(R, maximum) / 4;
    // }

    Key_custom zero = {{0}};
    Key_custom k = {{0}};
    Hash_table *h = hash_init(tam);
    do
    {
        Key passwordEncrypted = {{0}}; //subset_sum_custom(&k, lista);
        for (int p = 0; p < C_CUSTOM; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p + (1 * C_CUSTOM)]));
        }
        Key_custom *k_ptr = &k;
        Key *password_ptr = &passwordEncrypted; //init_key_ptr(&passwordEncrypted);
        // print_key_custom(k_ptr);
        // print_key(password_ptr);
        // sleep(1);
        hash_insert(h, password_ptr, k_ptr);
        add1_custom(&k);
    } while (!equal_custom(&k, &zero));

    printf("hash feita\n");

    Item *l = hash_search(h, equal, encrypted);

    if (l != NULL)
        print_key_char_soma_custom(&zero, &(l->v));
    // list_iterate(l, print_key_char_soma, &zero);

    // Hash_table *h2 = hash_init(tam);

    // while (k.digit[C - 6 - 1] == 0)
    // {
    //     Key passwordEncrypted = subset_sum_custom(&k, lista);
    //     // for (int p = 0; p < C; p++)
    //     // {
    //     //     if (k.digit[p] != 0)
    //     //         add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
    //     // }
    //     Key *k_ptr = &k;                        //init_key_ptr(&k);
    //     Key *password_ptr = &passwordEncrypted; //init_key_ptr(&passwordEncrypted);

    //     hash_insert(h2, password_ptr, k_ptr);
    //     sub(encrypted, &passwordEncrypted);

    //     l = hash_search(h, equal, &passwordEncrypted);
    //     if (l != NULL)
    //     {
    //         print_key_char_soma(l, &k);
    //     }

    //     add_onfirst(&k, &maximo);
    // }

    k = zero;
    do
    {
        Key passwordEncrypted = {{0}};
        for (int p = 0; p < C_CUSTOM; p++)
        {
            if (k.digit[p] != 0)
                add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, &passwordEncrypted);

        l = hash_search(h, equal, &passwordEncrypted);
        if (l != NULL)
        {
            print_key_char_soma_custom(&k, &(l->v));
        }

        add1_custom(&k);
    } while (!equal_custom(&zero, &k));
    sleep(3);
    hash_destroy(h);
}

// hash(senha) = hash(a) + hash(b) + hash(c);
// h = hash(a);
// h2 = hash(b) + hash(a);
// hash(a) = hash(senha) - hash(b) - hash(c);
// hash(b) = hash(senha) - hash(a) - hash(c);
// hash(d) = hash(senha) - hash(c);

// hash(d) = hash(a) + hash(b)

// hash(a) = hash(d) - hash(b);

//hash(a) = hash(senha) - hash(senha) + hash(c) - hash(c)

// void dec_symbol_table(const Key *encrypted, Key T[N])
// {

//     Key lista[R][C];

//     init_lista_key(lista, T); // R*C*N

//     Key k = {{0}};
//     TST *tst = TST_create();

//     int maximum = C / 2;

//     if (maximum > 4)
//     {
//         maximum = C - 4;
//     }

//     // dec_symbol_table2_rec(maximum, k, C, lista, k, &tst);
//     while (k.digit[maximum - 1] == 0)
//     {
//         Key passwordEncrypted = {{0}};
//         for (int p = 0; p < C; p++)
//         {
//             if (k.digit[p] != 0)
//                 add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
//         }

//         tst = TST_insert(tst, &passwordEncrypted, &k);
//         add1(&k);
//     }

//     List *l = TST_search(tst, encrypted);

//     Key zero = {{0}};
//     if (l != NULL)
//         list_iterate(l, print_key_char_soma, &zero);

//     Key atual = k;

//     do
//     {
//         Key passwordEncrypted = {{0}};
//         for (int p = 0; p < C; p++)
//         {
//             if (k.digit[p] != 0)
//                 add_onfirst(&passwordEncrypted, &(lista[k.digit[p]][p]));
//         }

//         sub(encrypted, &passwordEncrypted);

//         l = TST_search(tst, &passwordEncrypted);
//         if (l != NULL)
//         {
//             list_iterate(l, print_key_char_soma, &k);
//             print_key(&passwordEncrypted);
//             printf("\n");
//         }
//         add_onfirst(&k, &atual);
//     } while (!equal(&zero, &k));
//     TST_destroy(tst);
// }

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
    if (C == 5)
        dec_forca_bruta(&encrypted, T);
    else
        dec_symbol_table2(&encrypted, T);
    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}