#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define M 3571

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int t1[M];
int t2[M];
int t3[M];
int t4[M];
char* fn = "/usr/share/dict/cracklib-small";
FILE* fd;
char word[50];

// ----------------------------------------------------------------------------

uint32_t silly(char *s, int len) {
  uint32_t h = 0;
  for (int i = 0; i < len; i++) {
    h += s[i];
  }
  return h % M;
}

// ----------------------------------------------------------------------------

uint32_t horner(char *s, int len) {
  uint32_t h = 0;
  for (int i = 0; i < len; i++) {
    h = (251*h + s[i]) % M;
  }
  return h;
}

// ----------------------------------------------------------------------------

uint32_t adler(char *s, int len) {
  uint32_t s1 = 1;
  uint32_t s2 = 0;
  for (int i = 0; i < len; i++) {
    s1 = (s1 + s[i]) % 65521;
    s2 = (s1 + s2) % 65521;
  }
  return ((s2 << 16) | s1) % M;
}

// ----------------------------------------------------------------------------

uint32_t joaat(char *s, int len) {
  uint32_t h = 0;
  for (int i = 0; i < len; i++) {
    h += s[i];
    h += (h << 10);
    h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);
  return h % M;
}

// ----------------------------------------------------------------------------

void read_word() {
  if (fscanf(fd, "%s", word) == EOF) {
    word[0] = 0;
  }
  //printf("%s\n", word);
}

void print(int *t) {
  int min = INT_MAX;
  int max = 0;
  int counts[500];
  int sum, w;
  int i;

  for (i = 0; i < 500; i++) {
    counts[i] = 0;
  }

  for (i = 0; i < M; i++) {
    int count = t[i];
    min = MIN(min, count);
    max = MAX(max, count);
    counts[count]++;
  }

  sum = 0;
  w = 0;
  for (i = 0; i < 500; i++) {
    if (counts[i] != 0) {
      sum += i * counts[i];
      w += i;
    }
  }

  printf("Min = %d, Max = %d, Collision rate = %f\n", min, max, (float) w / sum);
}

// ----------------------------------------------------------------------------

int main(void) {
  for (int i = 0; i < M; i++) {
    t1[i] = 0;
    t2[i] = 0;
    t3[i] = 0;
    t4[i] = 0;
  }

  fd = fopen(fn, "r");
  read_word();
  while (word[0] != 0) {
    int len = strlen(word);
    t1[silly(word, len)]++;
    t2[horner(word,len)]++;
    t3[adler(word, len)]++;
    t4[joaat(word, len)]++;
    read_word();
  }

  fclose(fd);
  print(t1);
  print(t2);
  print(t3);
  print(t4);

  return 0;
}
