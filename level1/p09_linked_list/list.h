typedef struct Node{
    int data;
    struct Node *next;
} Node;

void append(int x);
void reverse();
int find(int num, int ord);
