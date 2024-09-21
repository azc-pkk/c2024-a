#include <stdio.h>
#include <time.h>

int p[1001], v[1001];
int tot;

void Euler() {
    for (int i = 2; i <= 1000; i++) {
        if (!v[i]) {
            v[i] = i;
            p[++tot] = i;
        }
        for (int j = 1; j <= tot; j++) {
            if (p[j] * i > 1000) break;
            v[p[j] * i] = p[j];
        }
    }
    return;
}

int main() {
    clock_t st, ed;
    st = clock();
    Euler();
    for (int i = 1; i <= tot; i++) {
        printf("%d\n", p[i]);
    }
    ed = clock();
    printf("It takes %ld ms to run.\n", ed - st);
    return 0;
}