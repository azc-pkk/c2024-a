#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define LEN 100

void show_menu() {
    printf("Welcome to use BDM repo system!\n");
    printf("1 --> show the repo\n");
    printf("2 --> add a item\n");
    printf("3 --> remove a item\n");
    printf("4 --> exit the system\n");
    printf("Please enter a command:\n");
}

void show_repo() {
    FILE *fp = fopen("repo.txt", "r");
    char buf[LEN];
    int cnt;
    while (fscanf(fp, "%s", buf) == 1) {
        printf("%s\n", buf);
        cnt++;
    }
    printf("%d item(s) in total.\n", cnt);
    fclose(fp);
}

void add() {
    char buf[LEN];
    printf("Please enter the name of the item:\n");
    scanf("%s", buf);
    FILE *fp = fopen("repo.txt", "a");
    fprintf(fp, "%s\n", buf);
    fclose(fp);
}

void del() {
    int tag = 0;
    char buf1[LEN], buf2[LEN];
    printf("Please enter the item you want to remove:\n");
    scanf("%s", buf1);

    FILE *fpr = fopen("repo.txt", "r");
    FILE *fpw = fopen("tmp.txt", "w");
    while (fscanf(fpr, "%s", buf2) == 1) {
        fprintf(fpw, "%s\n", buf2);
    }
    fclose(fpr);
    fclose(fpw);

    fpr = fopen("tmp.txt", "r");
    fpw = fopen("repo.txt", "w");
    while (fscanf(fpr, "%s", buf2) == 1) {
        if (tag == 0 && strcmp(buf1, buf2) == 0) {
            tag = 1;
            continue;
        }
        fprintf(fpw, "%s\n", buf2);
    }
    if (tag == 0) {
        printf("No such item!\n");
    }
    fclose(fpr);
    fclose(fpw);
    system("del tmp.txt");
}