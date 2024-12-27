//
// Created by BeiDAmenLinyu on 2024/12/24.
//

#include "rational.h"

int EXP = 10010;

Rational::Rational() = default;

// 向下取整
Rational::Rational(int a, int b) {
    this->ip = LongInt(std::to_string(a/b));
    a %= b;

    a = std::abs(a);
    b = std::abs(b);
    std::string tmp;
    for (int i = 0; i < EXP; i++) {
        a *= 10;
        tmp += char(a / b + '0');
        a %= b;
    }
    this->fp = LongInt(tmp);
}

std::ostream &operator<<(std::ostream &out, const Rational &a) {
    out << a.ip << '.' << a.fp;
    return out;
}

Rational operator+(const Rational &a, const Rational &b) {
    Rational res;
    res.ip = a.ip + b.ip;
    res.fp = a.fp + b.fp;
    if (res.fp.num.length() > EXP) {
        res.ip = res.ip + LongInt(res.fp.num.substr(0, res.fp.num.length() - EXP));
        res.fp.num = res.fp.num.substr(res.fp.num.length() - EXP);
    }
    return res;
}

Rational operator-(const Rational &a, const Rational &b) {
    if (a.ip.is_negative ^ b.ip.is_negative) {
        return a + (-b);
    }
    Rational res;
    res.fp = a.fp - b.fp;
    res.ip = a.ip - b.ip;
    res.fp.is_negative = false;
    if (a.ip == b.ip) {
        res.ip.is_negative = a.fp < b.fp;
    }
    else if (b.fp < a.fp && a.ip < b.ip) {
        res.ip = res.ip + LongInt("1");
        modify(&res);
    }
    else if (a.fp < b.fp && b.ip < a.ip) {
        res.ip = res.ip - LongInt("1");
        modify(&res);
    }
    while (res.ip.num.length() > 1 && res.ip.num[0] == '0')
        res.ip.num = res.ip.num.substr(1);
    return res;
}

Rational Rational::operator-()const {
    Rational tmp = *this;
    tmp.ip.is_negative ^= 1;
    return tmp;
}

void modify(Rational *a) {
    std::string tmp = "1" + std::string(EXP, '0');
    a->fp = LongInt(tmp) - a->fp;
    a->fp.num = a->fp.num.substr(1);
}

Rational operator*(const Rational &a, int b) {
    Rational res;
    res.fp = a.fp * b;
    res.ip = a.ip * b;
    if (res.fp.num.length() > EXP) {
        res.ip = res.ip + LongInt(res.fp.num.substr(0, res.fp.num.length() - EXP));
        res.fp.num = res.fp.num.substr(res.fp.num.length() - EXP);
    }
    return res;
}

Rational operator/(const Rational &a, const Rational &b) {
    Rational tmp = a;
    std::string ans;

    for (int i = 0; i <= EXP; i++) {
        int c = 0;
        while (!(tmp < b)) {
            tmp = tmp - b;
            c++;
        }
        ans += char('0' + c);
        tmp = tmp * 10;
    }

    tmp.ip = LongInt(ans.substr(0, 1));
    tmp.fp = LongInt(ans.substr(1));
    return tmp;
}

bool operator<(const Rational &a, const Rational &b) {
    if (a.ip.is_negative ^ b.ip.is_negative) {
        return a.ip.is_negative;
    }
    bool abs_less = false;
    if (a.ip < b.ip) {
        abs_less = true;
    }
    else if (a.ip == b.ip && a.fp < b.fp) {
        abs_less = true;
    }
    return a.ip.is_negative ^ abs_less;
}
