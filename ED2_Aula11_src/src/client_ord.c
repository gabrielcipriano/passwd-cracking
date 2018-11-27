#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

#define N    255

int main(int argc, char *argv[]) {
    printf("ASCENDING ORDER: ");
    RBT *t = RBT_create();
    for (int i = 0; i < N; i++) {
        t = RBT_insert(t, i, 0);
    }
    int h = RBT_height(t);
    printf("%d\n", h);
    RBT_destroy(t);

    printf("DESCENDING ORDER: ");
    t = RBT_create();
    for (int i = N-1; i >= 0; i--) {
        t = RBT_insert(t, i, 0);
    }
    h = RBT_height(t);
    printf("%d\n", h);
    RBT_destroy(t);
}
