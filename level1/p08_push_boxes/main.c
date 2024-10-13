#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>

#define LEN 20
const int LEVEL = 3;
int map[LEN][LEN];
int map_x, map_y;
int player_x, player_y;
int count;

void init();
void showMap();
void Move(int cmd);
bool win();
void game();

int main() {
    freopen("map.txt", "r", stdin);
    FILE *fp = fopen("score.txt", "w");
    for (int i = 1; i <= LEVEL; i++) {
        init();
        count = 0;
        game();
        printf("Level %d Finished!\n", i);
        fprintf_s(fp, "Level %d steps: %d\n", i, count);
        Sleep(1000);
    }
    printf("Congratulations!\nYou have finished all levels, here is your flag:\ncnss{I_AM_B0X_PUSH_MAS73R_AND_I_L0V3_Sh1n0!}");
    return 0;
}

void game() {
    system("cls");
    showMap();
    while (!win()) {
        while (!_kbhit());
        if (_kbhit()) {
            int cmd = _getch();
            switch (cmd) {
                case 72:
                    Move('u');
                    break;
                case 80:
                    Move('d');
                    break;
                case 75:
                    Move('l');
                    break;
                case 77:
                    Move('r');
                    break;
                default:
                    break;
            }
        }
        system("cls");
        showMap();
    }
}

bool win() {
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            if (map[i][j] == 3 || map[i][j] == 4) return false;
        }
    }
    return true;
}

void Move(int cmd) {
    int dx = 0, dy = 0;
    if (cmd == 'u') dx = -1;
    else if (cmd == 'd') dx = 1;
    else if (cmd == 'l') dy = -1;
    else dy = 1;
    if (map[player_x + dx][player_y + dy] == 1) return;
    if (map[player_x + dx][player_y + dy] == 6 || map[player_x + dx][player_y + dy] == 2) {
        if (map[player_x + dx + dx][player_y + dy + dy] == 2 || map[player_x + dx + dx][player_y + dy + dy] == 1 || map[player_x + dx + dx][player_y + dy + dy] == 6) return;
        if (map[player_x + dx + dx][player_y + dy + dy] == 3) map[player_x + dx + dx][player_y + dy + dy] = 6;
        else map[player_x + dx + dx][player_y + dy + dy] = 2;
        if (map[player_x][player_y] == 4) map[player_x][player_y] = 3;
        else map[player_x][player_y] = 0;
        if (map[player_x + dx][player_y + dy] == 6) {
            map[player_x + dx][player_y + dy] = 4;
        }
        else map[player_x + dx][player_y + dy] = 5;
        player_x += dx, player_y +=dy;
    }
    else if (map[player_x + dx][player_y + dy] == 3 || map[player_x + dx][player_y + dy] == 0) {
        if (map[player_x][player_y] == 4) map[player_x][player_y] = 3;
        else map[player_x][player_y] = 0;
        player_x += dx, player_y +=dy;
        if (map[player_x][player_y] == 3) map[player_x][player_y] = 4;
        else map[player_x][player_y] = 5;
    }
    count++;
}

void showMap() {
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            int ch = 0;
            switch (map[i][j]) {
                case 0:
                    ch = ' ';
                    break;
                case 1:
                    ch = '#';
                    break;
                case 2:
                    ch = '$';
                    break;
                case 3:
                    ch = '@';
                    break;
                case 4:
                    ch = '^';
                    break;
                case 5:
                    ch = '&';
                    break;
                case 6:
                    ch = '$';
                    break;
                default:
                    break;
            }
            putchar(ch);
        }
        putchar('\n');
    }
}

// 0 represents blank space where you can move to
// 1 represents '#' which means a barrier
// 2 represents '$' which means a box
// 3 represents '@' which means the place where you should push to
// 4 represents '^' which means the player is standing on the '@'
// 5 represents '&', the player
// 6 represents the box is in the right place

void init() {
    memset(map, 0, sizeof map);
    scanf("%d%d", &map_x, &map_y);
    scanf("%d%d", &player_x, &player_y);
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            scanf("%d", &map[i][j]);
        }
    }
}