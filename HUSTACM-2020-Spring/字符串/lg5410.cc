/**
 *
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#endif

template <class printable>
void trace(const char *name, printable &&value)
{cerr << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    cerr.write(names, separate - names) << " = " << value << ',';
    trace(separate + 1, list...);
}

template <class T>
void print(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void print(string &s) {printf(s.c_str());}
void print(const char *s) {printf(s);}
void print(char *s) {printf(s);}
void print(char ch) {putchar(ch);}
template <class T, class ...Ts>
void print(T x, Ts ...xs) {print(x), print(xs...);}
void println() {puts("");}
template <class T>
void println(T x)
{print(x), putchar('\n');}

static class Scanner
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

    static inline bool isBlank(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
    template <class T, class... Ts>
    void operator()(T &&x, Ts &&... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

using char_t = char;
using string_t = const char *const;
const int N = 2e7 + 7;
char a[N], b[N];

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

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    scanner(a, b);
    int aa = strlen(a), bb = strlen(b);
    exKMP_LCP(a, b, aa, bb);
    z[0] = bb;
    ulongs ans1 = 0, ans2 = 0;
    for (ulongs i = 0; i < bb; ++ i)
        ans1 ^= (i + 1) * (z[i] + 1);
    for (ulongs i = 0; i < aa; ++ i)
        ans2 ^= (i + 1) * (lcp[i] + 1);
    println(ans1), println(ans2);
    return 0;
}