#include "rational.h"

// 高精度的功能比较残缺，有些地方根据计算圆周率的目的进行了简化
// 计算到小数点后 10010 位

int main() {
    clock_t start = clock();
    Rational ans(0, 1), base(1, 1);
    for (int i = 0; i <= 8700; i++) {
        ans = ans * 16 + (
                Rational(4, 8 * i + 1) -
                Rational(2, 8 * i + 4) -
                Rational(1, 8 * i + 5) -
                Rational(1, 8 * i + 6)
                );
        base = base * 16;
    }
    std::cout << ans * 16 / base << std::endl;
    std::cout << "Time cost: " << (double)(clock() - start) / 1000.0 << "s" << std::endl;
    return 0;
}
