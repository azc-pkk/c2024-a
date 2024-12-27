//
// Created by BeiDAmenLinyu on 2024/12/28.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <random>
#include <vector>

struct Node {
    int val;
    Node *right, *down;
};

// 升序排列
class SkipList{
public:
    SkipList();
    Node* find(int val);
    void insert(int val);
    bool erase(int val);
private:
    Node *head;
};

#endif //SKIPLIST_SKIPLIST_H
