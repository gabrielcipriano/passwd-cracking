
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "key.h"

void dec_forca_bruta_rec(const Key *encrypted, Key prefix, Key lista[R][C], Key sum_anterior, int pos) // T(pos) = R*(C + T(pos-1)) + C
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
void dec_forca_bruta(const Key *encrypted, Key T[N]) // R*N*C + T(C)
{
    Key k = {{0}};

    // Quantidade de combinações
    Key zero = {{0}};
    Key lista[R][C];
    init_lista_key(lista, T); //R*N*C

    dec_forca_bruta_rec(encrypted,k, lista, zero, C ); //T(C)
}

int main(int argc, char *argv[])
{
    Key encrypted; // A senha criptografada.
    Key T[N];      // A tabela T.

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./brute [encrypted] < [table.txt]\n");
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
    // Força bruta

    clock_t tic = clock();
    dec_forca_bruta(&encrypted, T);
    clock_t toc = clock();

    printf("Tempo: %.3f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}