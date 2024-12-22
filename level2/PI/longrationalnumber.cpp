//
// Created by BeiDAmenLinyu on 2024/12/16.
//

#include "longrationalnumber.h"

LongRationalNumber::LongRationalNumber()= default;

LongRationalNumber::LongRationalNumber(const std::string &s) {
    if (s[0] == '-') {
        this->is_negative = true;
        this->num = s.substr(1);
    }
    else {
        this->is_negative = false;
        this->num = s;
    }
}

// 绝对值加
LongRationalNumber operator+(const LongRationalNumber &a, const LongRationalNumber &b) {
    int carry = 0;
    std::stack<int> num_a, num_b;
    LongRationalNumber res;
    res.num = "";
    for (auto ch : a.num) {
        num_a.push(ch - '0');
    }
    for (auto ch : b.num) {
        num_b.push(ch - '0');
    }
    while (carry != 0 || !num_a.empty() || !num_b.empty()) {
        int tmp = carry;
        if (!num_a.empty()) {
            tmp += num_a.top();
            num_a.pop();
        }
        if (!num_b.empty()) {
            tmp += num_b.top();
            num_b.pop();
        }
        carry = tmp / 10;
        tmp %= 10;
        res.num += char(tmp + '0');
    }
    std::reverse(res.num.begin(), res.num.end());
    return res;
}

std::ostream &operator<<(std::ostream &out, const LongRationalNumber &a) {
    if (a.is_negative)
        out << '-';
    out << a.num;
    return out;
}

bool operator<(const LongRationalNumber &a, const LongRationalNumber &b) {
    if (a.is_negative ^ b.is_negative) {
        return a.is_negative;
    }
    if (a.num.length() != b.num.length()) {
        return (!a.is_negative && a.num.length() < b.num.length())
               || (a.is_negative && a.num.length() > b.num.length());
    }
    for (int i = 0; i < a.num.length(); i++) {
        if (a.num[i] != b.num[i]) {
            return (a.is_negative && a.num[i] > b.num[i])
                   || (!a.is_negative && a.num[i] < b.num[i]);
        }
    }
    return false;
}

LongRationalNumber operator-(const LongRationalNumber &a, const LongRationalNumber &b) {
    LongRationalNumber res;
    res.num = "";
    if (a.is_negative ^ b.is_negative) {
        res = a + b;
        if (a < b)
            res.is_negative = true;
    }
    else {
        std::stack<int> num_a, num_b;
        for (auto ch : a.num)
            num_a.push(ch - '0');
        for (auto ch : b.num)
            num_b.push(ch - '0');
        std::stack<int> *g = &num_a, *l = &num_b;
        if (a < b) {
            res.is_negative = true;
            g = &num_b;
            l = &num_a;
        }
        int borrow = 0;
        // 绝对值大的减绝对值小的
        while (!num_a.empty() || !num_b.empty()) {
            int tmp = borrow;
            tmp += g->top();
            g->pop();
            if (!l->empty()) {
                tmp -= l->top();
                l->pop();
            }
            if (tmp < 0) {
                borrow = -1;
                tmp += 10;
            }
            else {
                borrow = 0;
            }
            res.num += char(tmp + '0');
        }
        std::reverse(res.num.begin(), res.num.end());
        // 去除结果的前导零
        while (res.num.length() > 1 && res.num[0] == '0')
            res.num = res.num.substr(1);
    }
    return res;
}

LongRationalNumber operator*(const LongRationalNumber &a, int b) {
    LongRationalNumber res;
    res.num = "";
    std::stack<int> num_a;
    for (auto ch : a.num) {
        num_a.push(ch - '0');
    }
    int carry = 0;
    while (carry != 0 || !num_a.empty()) {
        int tmp = carry % 10;
        carry /= 10;
        if (!num_a.empty()) {
            tmp += num_a.top() * b;
            num_a.pop();
        }
        if (tmp >= 10) {
            carry += tmp / 10;
            tmp %= 10;
        }
        res.num += char(tmp + '0');
    }
    res.is_negative = a.is_negative;
    std::reverse(res.num.begin(), res.num.end());
    while (res.num.length() > 1 && res.num[0] == '0')
        res.num = res.num.substr(1);
    return res;
}

LongRationalNumber operator*(const LongRationalNumber &a, const LongRationalNumber &b) {
    LongRationalNumber res;
    std::stack<int> num_b;
    for (auto ch : b.num) {
        num_b.push(ch - '0');
    }

//    std::string zeros;
//    while (!num_b.empty()) {
//        LongRationalNumber t = a * num_b.top();
//        t.num += zeros;
//        zeros += "0";
//        res = res + t;
//        num_b.pop();
//    }
//    res.is_negative = a.is_negative ^ b.is_negative;
//    return  res;

    std::string zeros;
    for (int i = 0; i * 8 < b.num.length(); i++) {
        int tmp = 0;
        int j = 0, k = 1;
        for(; j < 8 && !num_b.empty(); j++, k *= 10) {
            tmp += num_b.top() * k;
            num_b.pop();
        }
        LongRationalNumber t = a * tmp;
        t.num += zeros;
        res = res + t;
        while (j--) {
            zeros += "0";
        }
    }
    res.is_negative = a.is_negative ^ b.is_negative;
    return res;
}

// 四舍五入
LongRationalNumber operator/(const LongRationalNumber &a, const LongRationalNumber &b) {
    LongRationalNumber res;
    res.is_negative = a.is_negative ^ b.is_negative;
    LongRationalNumber abs_a = a, abs_b = b;
    abs_a.is_negative = abs_b.is_negative = false;
    while (!(abs_a < abs_b)) {
        abs_a = abs_a - abs_b;
        res = res + LongRationalNumber("1");
    }
    if (!(abs_a * 2 < abs_b)) {
        res = res + LongRationalNumber("1");
    }
    return res;
}


