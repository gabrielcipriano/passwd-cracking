/**********************************************************************
 *  Criptografa uma senha usando o algoritmo de soma de subconjunto.
 *
 *  Compilação:   $ gcc -Wall key.c encrypt.c -o encrypt
 *  Execução:     $ ./encrypt password < in/rand8.txt
 *                   vbskbezp
 *
 *  Nota: lembre-se de sempre ajustar a macro C em key.h antes de
 *  compilar e executar com uma senha de tamanho específico.
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "key.h"

typedef struct
{
    Key pilha[C];
    int topo;
} pilha_teste;

pilha_teste pilha_init()
{
    Key k = {{0}};
    pilha_teste p;
    for (int i = 0; i < C; i++)
    {
        p.pilha[i] = k;
    }
    p.topo = 0;
    return p;
}
int main(int argc, char *argv[])
{
    Key password;  // A senha fornecida pelo usuário.
    Key encrypted; // A senha criptografada.
    Key T[N];      // A tabela T.

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    password = init_key((unsigned char *)argv[1]);
    // Exibe a senha informada.
    printf("   ");
    print_key(password);
    printf("\n");

    // Lê a tabela T.
    unsigned char buffer[C + 1]; // Buffer temporário.
    for (int i = 0; i < N; i++)
    {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }

    // Calcula a soma de subconjunto.
    encrypted = subset_sum(password, T);

    // Exibe o resultado.
    printf("\n   ");
    print_key(encrypted);
    printf("\n");


    return 0;
}
