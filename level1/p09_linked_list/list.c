#include <malloc.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

Node *start;
void append(int x) {
    Node *nd = malloc(sizeof (Node));
    nd->next = NULL;
    nd->data = x;
    if (start == NULL) {
        start = nd;
        return;
    }
    Node *cur = start;
    while (cur->next != NULL) cur = cur->next;
    cur->next = nd;
}

void reverse() {
    if (start == NULL) return;
    Node *nd = start;
    Node *pre = NULL;
    Node *nxt = NULL;
    while (nd->next != NULL) {
        nxt = nd->next;
        nd->next = pre;
        pre = nd;
        nd = nxt;
    }
    nd->next = pre;
    start = nd;
}

int find(int num, int ord) {
    int cnt = 1;
    Node *cur = start;
    while (cur != NULL) {
        if (cur->data == num) {
            ord--;
            if (ord == 0) return cnt;
        }
        cur = cur->next;
        cnt++;
    }
    return  -1;
}