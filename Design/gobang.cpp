#include "gobang.h"
std::pair<int, int> next_step;
std::pair<int, int> fool() {
    next_step = std::make_pair(0, 0);
    alpha_beta(true, DEPTH, -INF, INF);
    return next_step;
}

int64_t alpha_beta(bool is_ai, int depth, int64_t alpha, int64_t beta) {
    if (depth == 0 || game_win(list1) || game_win(list2)) {
//        printf("%lld\n", evaluate());
        return evaluate();
    }
    for (int i = 0; i <= ROW; i++) {
        for (int j = 0; j <= COLUMN; j++) {
            if (list3.count(std::make_pair(i, j)) == 0 && has_neighbour(i, j, 1)) {
                list3.insert(std::make_pair(i, j));

                if (is_ai) { // AI 下，最大
                    list1.insert(std::make_pair(i, j));
                    evl_board[i][j] = 1;
                    int64_t val = alpha_beta(false, depth - 1, alpha, beta);
                    list1.erase(std::make_pair(i, j));
                    evl_board[i][j] = 0;

                    if (val > alpha && depth == DEPTH) {
                        next_step = std::make_pair(i, j);
                    }

                    alpha = std::max(alpha, val);
                }
                else {
                    list2.insert(std::make_pair(i, j));
                    evl_board[i][j] = 2;
                    beta = std::min(beta, alpha_beta(true, depth - 1, alpha, beta));
                    list2.erase(std::make_pair(i, j));
                    evl_board[i][j] = 0;
                }

                list3.erase(std::make_pair(i, j));

                if (alpha >= beta) {
                    return is_ai ? alpha : beta;
                }
            }
        }
    }

    return is_ai ? alpha : beta;
}

bool game_win(std::set< std::pair<int, int> > &li) {
    for (std::pair<int, int> piece : li) {
        int x = piece.first, y = piece.second;
        if (y + 4 <= COLUMN) { // 横
            if (li.count(std::make_pair(x, y + 1)) != 0
            &&  li.count(std::make_pair(x, y + 2)) != 0
            &&  li.count(std::make_pair(x, y + 3)) != 0
            &&  li.count(std::make_pair(x, y + 4)) != 0
            ) return true;
        }
        if (x + 4 <= ROW) { // 竖
            if (li.count(std::make_pair(x + 1, y)) != 0
            &&  li.count(std::make_pair(x + 2, y)) != 0
            &&  li.count(std::make_pair(x + 3, y)) != 0
            &&  li.count(std::make_pair(x + 4, y)) != 0
            ) return true;
        }
        if (x + 4 <= ROW && y - 4 >= 0) { // 左下
            if (li.count(std::make_pair(x + 1, y - 1)) != 0
            &&  li.count(std::make_pair(x + 2, y - 2)) != 0
            &&  li.count(std::make_pair(x + 3, y - 3)) != 0
            &&  li.count(std::make_pair(x + 4, y - 4)) != 0
            ) return true;
        }
        if (x + 4 <= ROW && y + 4 <= COLUMN) { // 右下
            if (li.count(std::make_pair(x + 1, y + 1)) != 0
            &&  li.count(std::make_pair(x + 2, y + 2)) != 0
            &&  li.count(std::make_pair(x + 3, y + 3)) != 0
            &&  li.count(std::make_pair(x + 4, y + 4)) != 0
            ) return true;
        }
    }
    return false;
}

