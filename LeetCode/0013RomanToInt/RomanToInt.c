#include <stdio.h>
#include <math.h>

/* **********************
** 算法区域
********************** */
#define METHOD 1
// 实现
#if METHOD == 1
int romanToInt(char* s) {
    int result = 0;
    while (*s != '\0') {
        switch (*s) {
            case 'I':
                if (s[1] == 'V') {
                    result += 4;
                    s = &s[1];
                }
                else if (s[1] == 'X') {
                    result += 9;
                    s = &s[1];
                }
                else
                    result += 1;
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                if (s[1] == 'L') {
                    result += 40;
                    s = &s[1];
                }
                else if (s[1] == 'C') {
                    result += 90;
                    s = &s[1];
                }
                else
                    result += 10;
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                if (s[1] == 'D') {
                    result += 400;
                    s = &s[1];
                }
                else if (s[1] == 'M') {
                    result += 900;
                    s = &s[1];
                }
                else
                    result += 100;
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
        }
        if (*s == '\0') break;
        s = &s[1];
    }
    return result;
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