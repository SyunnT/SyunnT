#include <stdbool.h>
#include <stdio.h>
#include <math.h>

/* **********************
** 算法区域
********************** */
#define METHOD 2
// 字符串实现
#if METHOD == 1
bool isPalindrome(int x)
{
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    char num[11] = {0};
    int i = 0;
    while (x) {
        num[i++] = x % 10;
        x /= 10;
    }
    int j = 0, k = i - 1;
    while (j < k) {
        if (num[j++] != num[k--]) return false;
    }
    return true;
}

// 非字符串实现：数字反转
#elif METHOD == 2
bool isPalindrome(int x)
{
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    int backReverse = 0;
    // 奇数位不适用
    // while (x > backReverse) {
    //     backReverse = backReverse * 10 + x % 10;
    //     x /= 10;
    // }
    while ((x / 10) > backReverse) {
        backReverse = backReverse * 10 + x % 10;
        x /= 10;
    }
    if (x != backReverse) {
        x /= 10;
    }
    return x == backReverse;
}

#endif

/* **********************
** 测试程序
********************** */
int main()
{
    printf("%lf\n", pow(2, 32));

    return 0;
}
