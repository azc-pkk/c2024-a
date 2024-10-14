#include <stdio.h>
#include "list.h"

extern Node *start;

int main() {
    int n, x;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        append(x);
    }
    Node *nd = start;
    while (nd != NULL) {
        printf("%d ", nd->data);
        nd = nd->next;
    }
    putchar('\n');
    reverse();
    nd = start;
    while (nd != NULL) {
        printf("%d ", nd->data);
        nd = nd->next;
    }
    putchar('\n');
    printf("%d\n", find(5, 1));
    printf("%d\n", find(5, 2));
    return 0;
}