#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <unistd.h>

#include "key.h"
#include "list.h"
#include "hash.h"


void dec_forca_bruta_rec(const Key *encrypted, Key prefix, Key lista[R][C], Key sum_anterior, int pos)
{
    if (pos == 0)
    {

        if (equal(&sum_anterior, encrypted))
        {
            print_key_char(&prefix);
        }
        return;
    }

    for (int i = 0; i < R; i++)
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_anterior, &(lista[i][pos - 1]));

        dec_forca_bruta_rec(encrypted, prefix, lista, novo_key, pos - 1);
    }
}

// Lista todas as possíveis senhas com um algoritmo de força bruta
void dec_forca_bruta(const Key *encrypted, Key T[N]) // R*C^2*B + (R*(C+T(C-1)))
{
    Key k = {{0}};

    // Quantidade de combinações
    Key zero = {{0}};
    Key lista[R][C];
    init_lista_key(lista, T);

    dec_forca_bruta_rec(encrypted, k, lista, zero, C);
}

void hash_populate_rec(Key_custom prefix, Key sum_anterior, Key lista[R][C], Hash_table *hash, int pos) //T(pos) = R*(C + T(pos-1)) + C
{
    if (pos == 0)
    {
        hash_insert(hash, &sum_anterior, &prefix); // C
        return;
    }

    for (int i = 0; i < R; i++)
    {
        prefix.digit[pos - 1] = i;

        Key novo_key = add(&sum_anterior, &(lista[i][(pos - 1) + (1 * C_CUSTOM)])); // C

        hash_populate_rec(prefix, novo_key, lista, hash, pos - 1); 
    }
}

void dec_symbol_table2(Key *encrypted, Key T[N]) //R*C*N + (R^C/2)/4 + T(C/2) + C + C + ((R^C/2)* C + C²/2 + C + C + C + C)
{
    Key lista[R][C];

    init_lista_key(lista, T); // R*C*N

    Key_custom zero = {{0}};
    Key_custom k = {{0}};
    Key *passwordEncrypted = malloc(sizeof(*passwordEncrypted));

    unsigned long tam = pow(R, C_CUSTOM) / 4;
    Hash_table *h = hash_init(tam); // (R^C/2)/4
    Key zeroo = {{0}};
    // Calcula R^C/2 combinações e coloca elas numa hash
    hash_populate_rec(k, zeroo, lista, h, C_CUSTOM); // T(C/2)

    printf("hash feita\n");

    Item *l = hash_search(h, equal, encrypted); // C

    if (l != NULL)
    {
        print_key_char_soma_custom(&zero, &(l->v)); // C
    }

    k = zero;

    // Como subset_sum(senha) = subset_sum(A) + subset_sum(B), calcula de B e procura em A a substração da senha com B
    do //(R^C/2) * 
    {
        for (int i = 0; i < C; i++) // C
        {
            passwordEncrypted->digit[i] = 0;
        }
        for (int p = 0; p < C_CUSTOM; p++) // C/2 * C
        {
            if (k.digit[p] != 0)
                add_onfirst(passwordEncrypted, &(lista[k.digit[p]][p]));
        }

        sub(encrypted, passwordEncrypted); // C

        l = hash_search(h, equal, passwordEncrypted); // C
        if (l != NULL)
        {
            print_key_char_soma_custom(&k, &(l->v)); // C
        }

        add1_custom(&k); // C/2
    } while (!equal_custom(&zero, &k)); // C/2
    free(passwordEncrypted);
    hash_destroy(h);
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

    printf("with key: %lu, without key: %lu\n", sizeof(List), sizeof(Teste));

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
    // menor do que 5 é rapido o suficiente usar a solução bruta e com numero impar não funciona por causa do C_custom = C/2
    if (C <= 5)
        dec_forca_bruta(&encrypted, T);
    else
        dec_symbol_table2(&encrypted, T);
    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}