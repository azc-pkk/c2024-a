#include "evaluation.h"

int evl_board[ROW][COLUMN];
std::set< std::pair<int, int> > list1, list2, list3;
//std::list< std::pair<int, int> > calculated;
std::list< std::pair<int64_t, std::list< std::pair<int, int> > > > calculated;
// 一个链表，每个元素是棋子序列和分数组成的 pair
std::list< std::pair< int64_t, int64_t > > SHAPE = {
// 连五
        {1000000, 911111},
// 活四
        {100000, 9011110},
// 冲四
        {50000, 9211110},
        {50000, 9211101},
        {50000, 911011},
// 活三
        {5000, 901110},
        {5000, 901101},
// 眠三
        {500, 92011102},
        {500, 910101},
        {500, 911001},
        {500, 9211100},
        {500, 9211010},
        {500, 9210110},
// 活二
        {50, 9010010},
        {50, 901010},
        {50, 9001100},
// 眠二
        {10, 910001},
        {10, 9210010},
        {10, 9210100},
        {10, 9211000}
};

int64_t evaluate() {
    int64_t my_score = 0, en_score = 0;
    calculated.clear();
    for (const auto& piece : list1) {
        my_score += cal(piece.first, piece.second, 1, 0, list1, list2);
        my_score += cal(piece.first, piece.second, 0, 1, list1, list2);
        my_score += cal(piece.first, piece.second, 1, 1, list1, list2);
        my_score += cal(piece.first, piece.second, 1, -1, list1, list2);
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (evl_board[i][j] != 1 && has_neighbour(i, j, 2))
                my_score += cal_cross(i, j);
        }
    }
    calculated.clear();
    for (const auto& piece : list2) {
        en_score += cal(piece.first, piece.second, 1, 0, list2, list1);
        en_score += cal(piece.first, piece.second, 0, 1, list2, list1);
        en_score += cal(piece.first, piece.second, 1, 1, list2, list1);
        en_score += cal(piece.first, piece.second, 1, -1, list2, list1);
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (evl_board[i][j] != 2 && has_neighbour(i, j, 2))
                en_score += cal_cross(i, j);
        }
    }
//    printf("%lld %lld\n", my_score, en_score);
    return my_score - en_score;
}

int64_t cal(int x, int y, int dx, int dy, std::set< std::pair<int, int> > &my_list, std::set< std::pair<int, int> > &en_list) {
//    for (auto piece : calculated)
//        if (x == piece.first && y == piece.second)
//            return 0;

    for (const auto& line : calculated)
        for (auto piece : line.second)
            if (x == piece.first && y == piece.second)
                return 0;

    bool is_ai = false;
    if (my_list == list1) is_ai = true;

    int64_t max_score = 0;
    std::list< std::pair<int, int> > max_shape;
    for (int len = 5; len <= 7; len++) {
        for (int offset = -len + 1; offset <= 0; offset++){
            int64_t  tmp_shape = 9;
            for (int i = 0; i < len; i++) {
                tmp_shape = tmp_shape * 10 + check(x + (i + offset) * dx, y + (i + offset) * dy, is_ai ? 1 : 2);
            }
            for (const auto& shape: SHAPE) {
                if (shape.first > max_score && shape.second == tmp_shape) {
//                    output(shape.second);
//                    output(tmp_shape);
                    max_score = shape.first;
                    max_shape.clear();
                    for (int i = 0; i < len; i++) {
                        max_shape.emplace_back(x + (i + offset) * dx, y + (i + offset) * dy);
                    }
                }
            }
        }
    }
    if (max_score != 0)
        calculated.emplace_back(max_score, max_shape);
    return max_score;
}

int64_t cal_cross(int x, int y) {
    int64_t res = 0;
    for (const auto& line : calculated)
        for (auto piece : line.second)
            if (x == piece.first && y == piece.second) {
                res += line.first;
                break;
            }
    return res;
}

int check(int x, int y, int tag) {
    if (evl_board[x][y] == tag) return 1;
    if (evl_board[x][y] != 0) return 2;
    return 0;
}

bool has_neighbour(int x, int y, int n) {
    for (int i = -n; i <= n; i++) {
        for (int j = -n; j <= n; j++) {
            if (x + i < 0 || x + i >= ROW || y + j < 0 || y + j >= COLUMN) continue;
            if (evl_board[x + i][y + j] != 0) return true;
        }
    }
    return false;
}