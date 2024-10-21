#include <stdio.h>
#include <Windows.h>
#include "repo.h"

int main() {
    int op;
    while (1) {
        show_menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                show_repo();
                break;
            case 2:
                add();
                break;
            case 3:
                del();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid Input!\n");
                system("pause");
                break;
        }
    }
    return 0;
}