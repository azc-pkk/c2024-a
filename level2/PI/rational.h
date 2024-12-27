//
// Created by BeiDAmenLinyu on 2024/12/24.
//

#ifndef PI_RATIONAL_H
#define PI_RATIONAL_H
#include "longint.h"

class Rational {
public:
    Rational();
    Rational(int a, int b);

    Rational operator - () const;

    friend void modify(Rational *a);

    friend std::ostream& operator << (std::ostream &out, const Rational &a);
    friend bool operator < (const Rational &a, const Rational &b);
    friend Rational operator + (const Rational &a, const Rational &b);
    friend Rational operator - (const Rational &a, const Rational &b);
    friend Rational operator * (const Rational &a, int b);
    friend Rational operator / (const Rational &a, const Rational &b);
private:
    LongInt ip;
    LongInt fp;
};

#endif //PI_RATIONAL_H
