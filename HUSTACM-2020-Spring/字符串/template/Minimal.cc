#include "public.h"

int minimal(const string_t &s, int n)
{
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n)
        if (s[(i + k) % n] == s[(j + k) % n]) ++ k;
        else
        {
            s[(i + k) % n] > s[(j + k) % n] ?
            (i = i + k + 1) : (j = j + k + 1);
            if (i == j) ++ i; k = 0;
        }
    return min(i, j);
}
