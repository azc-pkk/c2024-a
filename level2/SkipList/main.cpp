//
// Created by BeiDAmenLinyu on 2024/12/28.
//
#include "skiplist.h"
#include <cstdio>

int main() {
    int opcode, val;
    SkipList sl;
    // 0 -- exit
    // 1 -- find
    // 2 -- insert
    // 3 -- erase
    while (true) {
        scanf("%d", &opcode);
        if (opcode == 0) {
            break;
        }
        else if (opcode == 1) {
            scanf("%d", &val);
            if (sl.find(val) == nullptr) {
                printf("failed\n");
            }
            else {
                printf("%d\n", sl.find(val)->val);
            }
        }
        else if (opcode == 2) {
            scanf("%d", &val);
            sl.insert(val);
        }
        else if (opcode == 3) {
            scanf("%d", &val);
            sl.erase(val);
        }
    }
    return 0;
}