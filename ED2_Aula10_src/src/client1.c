#include <stdio.h>
#include "ST.h"

#define N 13

void visit(Key key, Value val) {
    printf("%c %i\n", key, val);
}
int main(void) {
    ST_init(N);
    for (int i = 0; i < N; i++) {
        char key;
        scanf("%c ", &key);
        ST_put(key, i);
    }
    ST_traverse(visit);
    ST_finish();
}
