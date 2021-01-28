#include "public.h"

int d1[N], d2[N];

/**
 * d1[i] 的含义是 i 为中心的回文串数量
 * d2[i] 的含义是 i 和 i-1 中间为中心的回文串数量
 * 因为回文串是嵌套的，所以其数量就是最大长度
 *
 * @param s the string, elements impl equals
 * @param n the string length（0-index
 */
void manacher(const string_t &s, int n)
{
    for (int i = 0, l = 0, r = -1; i < n; ++ i)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (i - k >= 0 && i + k < n
               && s[i - k] == s[i + k]) ++ k;
        d1[i] = k --;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; ++ i)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n
               && s[i - k - 1] == s[i + k]) ++ k;
        d2[i] = k --;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
}