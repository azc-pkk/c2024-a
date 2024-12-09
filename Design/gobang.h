#pragma once
#ifndef GOBANG_GOBANG_H
#define GOBANG_GOBANG_H
#include <cstdint>
#include "evaluation.h"
const int64_t INF = 10000000000000;
const int DEPTH = 4;
extern std::pair<int, int> next_step;

std::pair<int, int> fool();

int64_t alpha_beta(bool is_ai, int depth, int64_t alpha, int64_t beta);

bool game_win(std::set< std::pair<int, int> > &li);

#endif //GOBANG_GOBANG_H
