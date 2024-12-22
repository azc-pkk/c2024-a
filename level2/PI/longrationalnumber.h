//
// Created by BeiDAmenLinyu on 2024/12/16.
//

#ifndef PI_LONGRATIONALNUMBER_H
#define PI_LONGRATIONALNUMBER_H
#include <string>
#include <stack>
#include <algorithm>
#include <iostream>

class LongRationalNumber {
public:
    int EXP = 1005;
    LongRationalNumber();
    explicit LongRationalNumber(const std::string &s);

    friend std::ostream& operator << (std::ostream &out, const LongRationalNumber &a);
    friend bool operator < (const LongRationalNumber &a, const LongRationalNumber &b);
    friend LongRationalNumber operator + (const LongRationalNumber &a, const LongRationalNumber &b);
    friend LongRationalNumber operator - (const LongRationalNumber &a, const LongRationalNumber &b);
    friend LongRationalNumber operator * (const LongRationalNumber &a, int b);
    friend LongRationalNumber operator * (const LongRationalNumber &a, const LongRationalNumber &b);
    friend LongRationalNumber operator / (const LongRationalNumber &a, const LongRationalNumber &b);
private:
    std::string num;
    bool is_negative{};
};

#endif //PI_LONGRATIONALNUMBER_H
