#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbt.h"

#define RUNS 10
#define N    255

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int sum = 0;
    printf("ITER\tMAX HEIGHT\n");
    for (int run = 0; run < RUNS; run++) {
        printf("%d\t", run);
        RBT *t = RBT_create();
        for (int i = 0; i < N; i++) {
            int r = rand();
            t = RBT_insert(t, r, 0);
        }
        int h = RBT_height(t);
        sum += h;
        printf("%d\n", h);
        RBT_destroy(t);
    }

    printf("-----------------\n");
    printf("MEAN: %.2f\n", (double) sum / RUNS);
}
