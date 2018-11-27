#include <stdio.h>
#include "ST.h"

#define N 13

void visit(Key key, Value val) {
    printf("%c %i\n", key, val);
}

char c[N];

int main(void) {
    ST_init(N);

    for (int i = 0; i < N; i++) {
        scanf("%c ", &c[i]);
        ST_put(c[i], i);
    }

    int orig_size = ST_size();
    printf("SIZE: %d\n", orig_size);
    printf("MIN:  %c\n", ST_min());
    printf("MAX:  %c\n", ST_max());

    printf("\n");
    printf("KEY RANK FLOOR CEIL\n");
    printf("-------------------\n");
    for (char i = 'A'; i <= 'Z'; i++) {
        printf("%2c %4d %4c %4c\n",
               i, ST_rank(i), ST_floor(i), ST_ceiling(i));
    }
    printf("\n");

    printf("Initial table:\n");
    ST_traverse(visit);
    printf("\n");

    for (int i = 0; i < (orig_size / 2); i++) {
        ST_delmin();
    }
    printf("After deleting the smallest half:\n");
    ST_traverse(visit);
    printf("\n");

    for (int i = 0; i < (orig_size / 2) - 1; i++) {
        ST_delmax();
    }
    printf("After deleting all but one from the other half using delmax:\n");
    ST_traverse(visit);
    printf("\n");

    // Cleanup
    ST_delmax();

    for (int i = 0; i < N; i++) {
        scanf("%c ", &c[i]);
        ST_put(c[i], i);
    }
    printf("After puting everything back again:\n");
    ST_traverse(visit);
    printf("\n");

    ST_delete('C');
    ST_delete('R');
    ST_delete('E');
    printf("After 3 Hibbard deletions:\n");
    ST_traverse(visit);
    printf("\n");
    printf("SIZE: %d\n", ST_size());

    ST_finish();
}
