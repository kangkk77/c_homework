#include <stdio.h>
#include <stdlib.h>

/**
 * 计算两个整数的和
 * @param a 第一个整数
 * @param b 第二个整数
 * @return 两数之和
 */
int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 10, y = 20;
    printf("%d + %d = %d\n", x, y, add(x, y));
    return 0;
}
