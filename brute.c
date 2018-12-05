
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "key.h"

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