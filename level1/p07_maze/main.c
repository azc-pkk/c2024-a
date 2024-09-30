#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

const int LEN = 20;
char maze[20][20];
bool vis[20][20];
bool end_exsit = false;
int pos_x, pos_y;
int end_x, end_y;

// x 表示行，y 表示列！

void init();
void dfs(int x, int y);
void show_maze();
void Move(char cmd);
bool valid(int x, int y);
bool check(int x, int y);

int main() {
    srand(time(NULL));
    pos_y = (rand() + 1) % (LEN-2);
    pos_x = LEN - 1;
    init();
    while (pos_x != end_x || pos_y != end_y) {
        show_maze();
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
    }
    system("cls");
    printf("YOU WIN!!!\nCongratulations!\n");
    return 0;
}


// 1.两条路之间有间隔，即不能有四个相邻的空格！
// 2.入口与出口必须联通！
// 3.四边不能再生成空格！

bool check(int x, int y) {  // 以该点为顶点，是否有四个联通的空格
    if ((valid(x-1,y-1)&&maze[x-1][y-1]==' ') && (valid(x,y-1)&&maze[x][y-1]==' ') && (valid(x-1,y)&&maze[x-1][y]==' ')) return false;
    if ((valid(x,y-1)&&maze[x][y-1]==' ') && (valid(x+1,y)&&maze[x+1][y]==' ') && (valid(x+1,y-1)&&maze[x+1][y-1]==' ')) return false;
    if ((valid(x-1,y)&&maze[x-1][y]==' ') && (valid(x-1,y+1)&&maze[x-1][y+1]==' ') && (valid(x,y+1)&&maze[x][y+1]==' ')) return false;
    if ((valid(x+1,y+1)&&maze[x+1][y+1]==' ') && (valid(x,y+1)&&maze[x][y+1]==' ') && (valid(x+1,y)&&maze[x-1][y]==' ')) return false;
    return true;
}

void dfs(int x, int y) {
    vis[x][y] = true;
    int nx, ny;
    int flag = rand() % 4;
    int now  = flag;
    do {
        nx = x, ny = y;
        if (now == 0) nx++;
        else if (now == 1) nx--;
        else if (now == 2) ny++;
        else ny--;
        if (valid(nx, ny) && !vis[nx][ny] && (!end_exsit || (nx != 0 && nx != LEN - 1 && ny != 0 && ny != LEN - 1)) && check(nx, ny)) {
            if (!end_exsit && (ny == 0 || ny == LEN - 1 || nx == LEN - 1)) {
                now = (now + 1) % 4;
                continue;
            }
            maze[nx][ny] = ' ';
            if (nx == 0) {
                end_exsit = true;
                end_x = nx, end_y = ny;
                now = (now + 1) % 4;
                continue;
            }
            dfs(nx, ny);
        }
        now = (now + 1) % 4;
    } while (now != flag);
}

void init() {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            maze[i][j] = '#';
        }
    }
    maze[pos_x][pos_y] = ' ';
    dfs(pos_x, pos_y);
    return;
}

void show_maze() {
    system("cls");
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            if (i == pos_x && j == pos_y) {
                putchar('P');
                continue;
            }
            putchar(maze[i][j]);
        }
        putchar('\n');
    }
}

void Move(char cmd) {
    int dx = 0, dy = 0;
    switch (cmd) {
        case 'u':
            dx = -1;
            break;
        case 'd':
            dx = 1;
            break;
        case 'l':
            dy = -1;
            break;
        case 'r':
            dy = 1;
            break;
        default:
            break;
    }
    if (valid(pos_x + dx, pos_y + dy) && maze[pos_x + dx][pos_y + dy] != '#') {
        pos_x += dx;
        pos_y += dy;
    }
}

bool valid(int x, int y) {
    return x >= 0 && x < LEN && y >= 0 && y < LEN;
}