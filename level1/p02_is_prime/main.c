#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    int t = sqrt(n);
    for (int i = 2; i <= t; i++) {
        if (n % i == 0) {
            printf("No!\n");
            return 0;
        }
    }
    printf("Yes!\n");
    return 0;
}