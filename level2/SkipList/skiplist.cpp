//
// Created by BeiDAmenLinyu on 2024/12/28.
//

#include "skiplist.h"

const int MAX_LEVEL = 16;
const int INF = 1e9 + 10;


SkipList::SkipList() {
    this->head = new Node;
    Node *cur = this->head;
    cur->right = nullptr;
    cur->val = -INF;
    for (int i = 1; i < MAX_LEVEL; i++) {
        cur->down = new Node;
        cur = cur->down;
        cur->right = nullptr;
        cur->val = -INF;
    }
    cur->down = nullptr;
}

Node* SkipList::find(int val) {
    Node *cur = this->head;
    while (cur != nullptr) {
        if (cur->val == val) {
            return cur;
        }
        else if (cur->right != nullptr && cur->right->val <= val) {
            cur = cur->right;
        }
        else{
            cur = cur->down;
        }
    }
    return nullptr;
}

void SkipList::insert(int val) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(1, MAX_LEVEL);
    int level = dist(gen);

    std::vector<Node*> road;

    Node *cur = this->head;

    while (cur != nullptr) {
        if (cur->right != nullptr && cur->right->val <= val) {
            cur = cur->right;
        }
        else{
            road.push_back(cur);
            cur = cur->down;
        }
    }

    Node *node = new Node;
    for (int i = MAX_LEVEL - level; i < MAX_LEVEL - 1; i++) {
        node->right = road[i]->right;
        road[i]->right = node;
        node->down = new Node;
        node->val = val;
        node = node->down;
    }
    node->right = road[MAX_LEVEL-1]->right;
    road[MAX_LEVEL-1]->right = node;
    node->down = nullptr;
    node->val = val;
}

bool SkipList::erase(int val) {
    Node *pos = this->find(val);
    if (pos == nullptr)
        return false;

    std::vector<Node*> road;
    Node *cur = this->head;
    while (cur != nullptr) {
        if (cur->right != nullptr && cur->right->val < val) {
            cur = cur->right;
        }
        else{
            road.push_back(cur);
            cur = cur->down;
        }
    }

    for (auto node : road) {
        if (node->right == pos) {
            Node *tmp = pos->right;
            pos = pos->down;
            delete node->right;
            node->right = tmp;
        }
    }

    return true;
}
