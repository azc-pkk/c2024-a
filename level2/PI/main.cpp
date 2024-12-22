#include "longrationalnumber.h"

int main() {
    std::string sa, sb;
    std::cin >> sa >> sb;
    LongRationalNumber a(sa);
    LongRationalNumber b(sb);
    std::cout << a / b << std::endl;

    return 0;
}
