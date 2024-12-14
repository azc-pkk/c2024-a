#pragma once
#ifndef GOBANG_EVALUATION_H
#define GOBANG_EVALUATION_H
#include <set>
#include <list>
#include <cstdio>
#include <utility>
#include <cstdint>
#include <algorithm>
const int COLUMN = 15, ROW = 15;
extern int evl_board[ROW][COLUMN];
extern std::set< std::pair<int, int> > list1, list2, list3;
extern std::list< std::pair<int64_t, std::list< std::pair<int, int> > > > calculated;
extern std::list< std::pair< int64_t, std::list<int> > > SHAPE;

int64_t evaluate();

int64_t cal(int x, int y, int dx, int dy, std::set< std::pair<int, int> > &my_list, std::set< std::pair<int, int> > &en_list);

int64_t cal_cross(int x, int y);

int check(int x, int y, int tag);

bool has_neighbour(int x, int y, int n);

#endif //GOBANG_EVALUATION_H
