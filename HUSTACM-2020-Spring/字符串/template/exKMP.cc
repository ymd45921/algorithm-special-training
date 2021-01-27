#include "public.h"

/**
 *
 * @param s 0-index string to make z-array
 * @param z to build Z-function, at least n
 * @param n the string's length
 */
void z_function(const string_t &s, int *z, int n)
{
    memset(z, 0, sizeof(int) * n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++ i)
    {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (z[i] + i < n
            && s[z[i] + i] == s[z[i]]) ++ z[i];
        if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
}

int z[N], lcp[N];

void exKMP_LCP(const string_t &s, const string_t &t,
               int s_length, int t_length)
{
    z_function(t, z, t_length);
    int pos = 0, far = 0;
    for (int i = 0; i < s_length; ++ i)
    {
        if (i <= far)
            lcp[i] = min(z[i - pos], far - i + 1);
        while (i + lcp[i] < s_length
            && t[lcp[i]] == s[i + lcp[i]])
            ++ lcp[i];
        if (i + lcp[i] - 1 > far)
            far = i + lcp[i] - 1, pos = i;
    }
}
