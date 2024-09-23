#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

int main() {
    char str[] = "Uestc";
    int len = 5;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int col = csbi.srWindow.Right - csbi.srWindow.Left;
    int c = 0, t = 1;
    while (true) {
        system("cls");
        if (c < 0) {
            t = 1;
        }
        if (c + len == col) {
            t = -1;
        }
        for (int i = 1; i <= c; i++) {
            putchar(' ');
        }
        printf("%s", str);
        Sleep(50);
        c += t;
    }
    return 0;
}