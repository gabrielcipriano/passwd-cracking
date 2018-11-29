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
void print_key(Key k)
{
    for (int i = 0; i < C; i++)
    {
        printf("%c", ALPHABET[(unsigned char)(k.digit[i])]);
    }
    printf("  ");
    for (int i = 0; i < C; i++)
    {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++)
    {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k)
{
    for (int i = 0; i < C; i++)
    {
        if (k.digit[i] < 0)
            printf("%d", k.digit[i]);
        else
        {
            printf("%c", ALPHABET[(unsigned char)(k.digit[i])]);
        }
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key k, int i)
{
    return (k.digit[i / B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b)
{
    Key c = {{0}};
    int carry = 0;
    for (int i = C - 1; i >= 0; i--)
    {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum % R;
        carry = sum >= R;
    }
    return c;
}
Key add1(Key a)
{
    int sum = a.digit[C - 1] + 1;

    a.digit[C - 1] = sum % R;
    int carry = sum >= R;
    int i = C - 2;
    while (i >= 0 && carry != 0)
    {
        sum = a.digit[i] + carry;
        a.digit[i] = sum % R;
        carry = sum >= R;
        i--;
    }

    return a;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N])
{
    Key sum = {{0}};

    int i;
    for (i = 0; i < N; i++)
    {
        int b = bit(k, i);

        if (b)
        {
            sum = add(sum, T[i]);

            /*   printf("%2d   ", i); // Para teste.
            print_key(T[i]);     // Para teste.
            printf("sum: ");
            print_key(sum); // Para teste.
            printf("\n");*/
        }
    }

    return sum;
}

int compareK(Key a, Key b)
{

    for (int i = 0; i < C; i++)
    {
        if (a.digit[i] < b.digit[i])
        {
            return -1;
        }
        if (a.digit[i] > b.digit[i])
        {
            return 1;
        }
    }

    return 0;
}

bool equal(Key a, Key b)
{

    for (int i = 0; i < C; i++)
    {
        if (a.digit[i] != b.digit[i])
        {
            return false;
        }
    }

    return true;
}

void dec_forca_bruta(Key encrypted, Key T[N])
{
    Key k;
    static Key a;

    // Senha para incrementar 1

    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = subset_sum(k, T);
        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
}

/*Key subset_sum_custom(Key k, Key T[N], Node *root)
{
    Key sum = {{0}};
    for (int i = 0; i < C; i++)
    {
        unsigned char letra = k.digit[i];
        Key val = ST_get(root, letra);
        if (!equal(val, NULL_Value))
        {
            for (int j = 0; j < B; j++)
                if ((item >> (B - 1 - j % B)) & 1)
                {
                    sumIn = add(sumIn, T[j]);
                    printf("%2d ", j); // Para teste.
                    print_key(T[j]);   // Para teste.
                }
        }
        sum = add(sum, val);
    }
    return sum;
}*/

void dec_symbol_table_new(Key encrypted, Key T[N])
{
    Key k = {{0}};
    Key a = {{0}};

    // Senha para incrementar 1

    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);
    Node *root = ST_init();
    root = ST_put(root, R + 1, NULL_Value);
    for (double i = 0; i < tam; i++)
    {
        Value passwordEncrypted = subset_sum_tree(k, T, root);
        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add(k, a);
    }
    ST_finish(root);
}

void dec_symbol_table(Key encrypted, Key T[N])
{

    /*  Key k={{0}};
    Key a;
    // Senha base



    // Key symbol_table[R];
    // Arvore de simbolos
    Node *root = ST_init();
    for (int j = 0; j < R; j++)
    {
        Key sum = {{0}};
        unsigned char letra = ALPHABET[j];
        for (int i = 0; i < B; i++)
        {
            if ((letra >> (B - 1 - i % B)) & 1)
            {
                sum = add(sum, T[i]);
            }
        }
        root = ST_put(root, letra, sum);
    }
    //root = ST_put(root, k, val);

    // Senha para somar
    for (int i = 0; i < C; i++)
    {
        a.digit[i] = 0;
    }
    a.digit[C - 1] = 1;

    // Quantidade de combinações
    double tam = pow(R, C);

    for (double i = 0; i < tam; i++)
    {

        Key val = subset_sum_custom(k, T, root);

        // Key keyAchou = ST_floor(root, k);
        //   Key valAchou = ST_get(root, keyAchou);

        if (equal(encrypted, val))
        {
            print_key_char(k);
        }

        k = add(k, a);
    }*/

    /*  Key k;
    Node *root = ST_init();
    root = dec_symbol_table_rec(T, k, R, 0, root);
    printf("tamanho arvore: %d\n", ST_size(root));
    k = ST_get(root, encrypted);
    print_key_char(k);
     while (compare(k, NULL_Value) != 0)
    {
        print_key_char(k);
        root = ST_delete(root, k);
        k = ST_get(root, encrypted);
    }*/

    //ST_finish(root);
}
#include <unistd.h>

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
    for (int i = 0; i <= p->topo && i <= C; i++)
    {
        printf("i: %d ", i);
        print_key(p->pilha[i]);
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

void teste_symbol_table_rec(Key encrypted, Key prefix, int pos, Key lista[R][C], Pilha p)
{
    // Base case: pos is 0,
    // print prefix
    if (pos == C)
    {

        // Key passwordEncrypted = subset_sum(prefix, map);

        if (equal(encrypted, olha_topo(&p)))
        {
            print_key_char(prefix);
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
        prefix.digit[pos] = i;
        // printf("empilhando letra %c na pos %d\n", ALPHABET[i], pos + 1);
        // printf("topo: ");
        // printf("%d\n", p.topo);

        // print_key(p.pilha[p.topo]);
        Pilha nova = empilha(p, add(sum_atual,lista[i][pos]));
        // if (ALPHABET[i] == 'p' && pos == 0)
        // {

        //     print_pilha(&p);
        // }
        // if (ALPHABET[i] == 'a' && pos == 1)
        // {
        //     print_pilha(&p);
        // }
        // if (ALPHABET[i] == 's' && pos == 2)
        // {
        //     print_pilha(&p);
        // }
        // if (ALPHABET[i] == 's' && pos == 3)
        // {
        //     print_pilha(&p);
        // }

        // printf("topo: ");
        // printf("%d\n", p.topo);
        // print_key(p.pilha[p.topo]);
        //sleep(1);

        /* printf("\npos: %d\n", pos);
            print_key(prefix);
            printf("before\n");
            print_key(sum_atual);
            printf("\n");*/

        // sum_atual = add(sum_anterior, lista[i][pos]);

        /* printf("after\n");
            print_key(sum_atual);
            printf("\n");
            sleep(1);*/

        // printf("%2d ", i); // Para teste.
        // print_key(T[i]);   // Para teste.

        // k is increased, because
        // we have added a new character
        teste_symbol_table_rec(encrypted, prefix, pos + 1, lista, nova);
        // printf("desempilhando %d\n", pos);
        // printf("%d\n", p.topo);
    }
}

void teste_symbol_table(Key encrypted, Key T[N])
{

    Key pass = {{0}};
    Key lista[R][C];
    for (int l = 0; l < R; l++)
    {
        for (int p = 0; p <= C; p++)
        {

            Key sum = {{0}};
            if (l != 0)
                for (int b = 0; b < B; b++)
                {
                    int bitt = bit_l(l, b);
                    if (bitt)
                    {
                        sum = add(sum, T[b + (p * B)]);
                    }
                }

            lista[l][p] = sum;
        }
    }
    Pilha p = Pilha_init();
    teste_symbol_table_rec(encrypted, pass, 0, lista, p);
}

void novo_(Key encrypted, Key T[N])
{
    Key lista[R][C];
    for (int l = 0; l < R; l++)
    {
        for (int p = 0; p <= C; p++)
        {

            Key sum = {{0}};
            for (int b = 0; b < B; b++)
            {
                int bitt = bit_l(l, b);
                if (bitt)
                {
                    sum = add(sum, T[b + (p * B)]);
                }
            }

            lista[l][p] = sum;
        }
    }

    /*   Pilha *p = Pilha_init();

    for (int i = 0; i < R; i++)
    {
        empilha(p, lista[i][0], i);
        for (int j = 0; j < R; j++)
        {

            empilha(p, add(olha_topo(p).k, lista[j][1]), j);
            for (int k = 0; k < R; k++)
            {
                empilha(p, add(olha_topo(p).k, lista[k][2]), k);
                for (int l = 0; l < R; l++)
                {
                    empilha(p, add(olha_topo(p).k, lista[l][3]),l);
                    for (int m = 0; m < R; m++)
                    {
                        ItemPilha item = olha_topo(p);

                        if (equal(encrypted, add(item.k, lista[m][4])))
                        {
                            printf("%c", ALPHABET[i]);
                            printf("%c", ALPHABET[j]);
                            printf("%c", ALPHABET[k]);
                            printf("%c", ALPHABET[l]);
                            printf("%c", ALPHABET[m]);
                            printf("\n");
                        }
                    }
                    desempilha(p);
                }
                desempilha(p);
            }

            desempilha(p);
        }

        desempilha(p);
    }

    free(p);*/

    Key k = {{0}};

    double tam = pow(R, C);

    // Pilha *p = Pilha_init();
    //  p->topo = C - 1;

    for (double i = 0; i < tam; i++)
    {

        Key passwordEncrypted = {{0}};
        int j;
        for (j = 0; j < C; j++)
        {

            //  ItemPilha top = olha_topo(p);

            // if (top.c != k.digit[j] && p->topo == j)
            // {
            //     desempilha(p);
            //     top = olha_topo(p);
            //     empilha(p, add(top.k, lista[k.digit[j]][j]), k.digit[j]);
            // }

            //Key *temp = (lista[k.digit[j]][j]);
            if (k.digit[j] != 0)
                passwordEncrypted = add(passwordEncrypted, lista[k.digit[j]][j]);
        }
        // while (j < C)
        // {
        //     ItemPilha top = olha_topo(p);
        //     empilha(p, add(top.k, lista[k.digit[j]][j]), k.digit[j]);
        //     j++;
        // }
        // ItemPilha top = olha_topo(p);
        // passwordEncrypted = top.k;

        if (equal(encrypted, passwordEncrypted))
        {
            print_key_char(k);
        }
        k = add1(k);
    }
    //  free(p);
}