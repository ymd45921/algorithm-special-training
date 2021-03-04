/**
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long longs;
typedef unsigned uint;
typedef unsigned long long ulongs;
typedef long double longd;
typedef __int128 lll;

#define minimize(a, b...) ((a) = min(a, b))
#define maximize(a, b...) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

template <class T>
void write(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void write(const char *s) {fputs(s, stdout);}
void write(char *s) {fputs(s, stdout);}
void write(string &s) {write(s.c_str());}
template <class T>
void println(T x)
{write(x), putchar('\n');}

template<class T>
inline T read()
{
    T x = 0; int f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}
template<class T>
void scan(T &x) {x = read<T>();}
void scan(char *s) {scanf("%s", s);}
void scan(char &c) {scanf("%c", &c);}

int nextInt() {return read<int>();}
int nextLongs() {return read<longs>();}
int nextInt128() {return read<lll>();}


signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif


    return 0;
}