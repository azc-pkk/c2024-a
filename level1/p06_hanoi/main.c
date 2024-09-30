#include <stdio.h>

void Hanoi(int n, char scr, char tar, char tmp) {
    if (n == 1) {
        printf("%c -> %c\n", scr, tar);
        return;
    }
    Hanoi(n - 1, scr, tmp, tar);  // 上 n - 1 个
    printf("%c -> %c\n", scr, tar);    // 最下面
    Hanoi(n - 1, tmp, tar, scr);
}

int main() {
    Hanoi(64, 'A', 'C', 'B');
    return 0;
}