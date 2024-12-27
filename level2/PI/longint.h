//
// Created by BeiDAmenLinyu on 2024/12/16.
//

#ifndef PI_LONGINT_H
#define PI_LONGINT_H
#include <string>
#include <stack>
#include <algorithm>
#include <iostream>

class LongInt {
public:
    LongInt();
    explicit LongInt(const std::string &s);

    friend class Rational;
    friend std::ostream& operator << (std::ostream &out, const LongInt &a);
    friend bool operator == (const LongInt &a, const LongInt &b);
    friend bool operator < (const LongInt &a, const LongInt &b);
    friend LongInt operator + (const LongInt &a, const LongInt &b);
    friend LongInt operator - (const LongInt &a, const LongInt &b);
    friend LongInt operator * (const LongInt &a, int b);
    friend LongInt operator * (const LongInt &a, const LongInt &b);
    friend LongInt operator / (const LongInt &a, const LongInt &b);

    bool is_negative{};
    std::string num;
};

#endif //PI_LONGINT_H
