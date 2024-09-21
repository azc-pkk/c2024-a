#include <stdio.h>
#include <stdbool.h>

bool is_prime[101];
int p[101], v[101];
int tot;

void Euler() {
    for (int i = 2; i <= 100; i++) {
        if (!v[i]) {
            v[i] = i;
            is_prime[i] = true;
            p[++tot] = i;
        }
        for (int j = 1; j <= tot; j++) {
            if (p[j] * i > 100) break;
            v[p[j] * i] = p[j];
        }
    }
    return;
}

int main() {
    Euler();
    for (int i = 2; i <= 100; i++) {
        if (is_prime[i]) {
            printf("%d is prime.\n", i);
            continue;
        }
        for (int j = 2; j < i; j++) {
            if (is_prime[j] && is_prime[i-j]) {
                printf("%d = %d + %d\n", i, j, i-j);
                break;
            }
        }
    }
    return 0;
}