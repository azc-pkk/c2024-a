#include <stdio.h>
#include <string.h>
#include <malloc.h>

// 输入一个小写字母组成的字符串，进行加密/解密

char *str;

int table[4][26] = {
        {3, 0, 6, 8, 21, 25, 7, 9, 10, 16, 23, 11, 15, 14, 2, 1, 4, 5, 24, 22, 19, 20, 12, 13, 17, 18},
        {13, 17, 18, 25, 7, 9, 10, 16, 3, 6, 8, 14, 0, 21, 23, 11, 1, 2, 12, 15, 4, 5, 24, 22, 19, 20},
        {17, 10, 16, 24, 13, 7, 9, 14, 11, 4, 6, 1, 21, 22, 19, 20, 3, 12, 15, 25, 23, 8, 18, 0, 2, 5},
        {9, 10, 16, 18, 25, 12, 3, 6, 8, 7, 21, 23, 11, 1, 13, 17, 5, 24, 19, 20, 22, 15, 4, 2, 14, 0}
};

void read() {
    int len = 1, ptr = 0;
    str = (char *)malloc(len);
    char ch;
    while ((ch = getchar()) != '\n') {
        if (ch > 'z' || ch < 'a') {
            printf("Error: Please enter lowercase characters!\n");
            return;
        }
        str[ptr++] = ch;
        if (ptr == len) {
            len *= 2;
            str = (char *)realloc(str, len);
        }
    }
    str[ptr] = '\0';
}

char* encrypt(char *uk) {
    int len = strlen(str);
    uk = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        uk[i] = table[i % 4][str[i] - 'a'] + 'a';
    }
    uk[len] = '\0';
    return uk;
}

char* decrypt(char *uk, char *mw) {
    int len = strlen(str);
    mw = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        int idx = i % 4;
        for (int j = 0; j < 26; j++) {
            if (table[idx][j] == uk[i] - 'a') {
                mw[i] = j + 'a';
                break;
            }
        }

    }
    mw[len] = '\0';
    return mw;
}

int main() {
    char *uk;
    char *mw;
    read();
    uk = encrypt(uk);
    printf("%s\n", uk);
    mw = decrypt(uk, mw);
    printf("%s\n", mw);
    return 0;
}