#include "hash.h"
#include "tree.h"

struct hash_table
{
  unsigned long tam;
  List **hash;
};

Hash_table *hash_init(unsigned long tam)
{
  Hash_table *h = malloc(sizeof(*h));
  h->tam = tam;
  h->hash = malloc(sizeof(*(h->hash)) * tam);
  for (int i = 0; i < h->tam; i++)
  {
    h->hash[i] = list_init();
  }
  return h;
}

unsigned long horner(Key *s, unsigned long m)
{
  unsigned long h = 0;
  for (int i = 0; i < C; i++)
  {
    h = (251 * h + (s->digit[i])) % m;
  }
  return h;
}
#include <stdio.h>
void hash_insert(Hash_table *h, Key *k, Key_custom *v)
{
  unsigned long hash = horner(k, h->tam);

  h->hash[hash] = list_insere(h->hash[hash], v, k);
  // if (hash == 90483)
  // {
  //   Key teste = init_key((unsigned char *)"wlswlca5");
  //   if (equal(k, &teste))
  //   {
  //     printf("hash: %lu\n", hash);
  //     Key zero = {{0}};
  //     List *l = tree_search(h->hash[hash], k);
  //     list_iterate(l, print_key_char_soma, &zero);
  //   }
  // }
}

Item *hash_search(Hash_table *h, bool (*fn)(const Key *, const Key *), Key *k)
{
  unsigned long hash = horner(k, h->tam);

  Item *i = list_search(h->hash[hash], fn, k);

  // {
  //   if (hash == 90483)
  //   {
  //     Key teste = init_key((unsigned char *)"wlswlca5");
  //     if (equal(k, &teste))
  //     {
  //       printf("hash: %lu\n", hash);
  //       Key zero = {{0}};
  //       list_iterate(l, print_key_char_soma, &zero);
  //     }
  //   }
  // }
  return i;
}

void hash_destroy(Hash_table *h)
{
  if (h != NULL)
  {
    for (unsigned long i = 0; i < h->tam; i++)
    {
      list_free(h->hash[i]);
    }
    free(h->hash);
    free(h);
  }
}