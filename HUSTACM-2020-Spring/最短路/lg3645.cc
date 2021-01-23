/**
 *
 * 这，，，
 *
 * 需要注意这些事情：
 * - 每条狗的生活空间是固定且不变的
 * - 只有到达了狗的起点，狗才会有意义
 * - 实际上的状态是 (n + m)√n 的
 * 这样就可以写对了
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

const int N = 3e4 + 5;

int p[N], b[N];
vector<int> e[N];
bitset<N> vis[N], arr;

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    for (int i = 0; i < m; ++ i)
        b[i] = scanner.nextInt(),
        p[i] = scanner.nextInt(),
        e[b[i]].push_back(p[i]);
    int S = b[0], T = b[1];
    if (S == T) return println(0), 0;
    queue<tuple<int, int, int>> q;
    const function<void(int, int, int)> stepIn =
    [&](int pos, int step, int dis)
    {
        if (pos < 0 || pos >= n) return;
        if (!arr[pos])
        {
            arr.set(pos);
            for (auto to : e[pos])
                if (!vis[pos][to])
                    vis[pos].set(to),
                    q.emplace(pos, to, dis);
        }
        if (!vis[pos][step])
            vis[pos].set(step),
            q.emplace(pos, step, dis);
    };
    arr.set(S);
    for (int to : e[S])
        vis[S].set(to),
        q.emplace(S, to, 0);
    int ans = 0x3f3f3f3f;
    while (!q.empty())
    {
        auto [pos, step, dis] = q.front();
        q.pop();
        int left = pos - step, right = pos + step;
        if (left == T || right == T)
        {minimize(ans, dis + 1); break;}
        stepIn(left, step, dis + 1);
        stepIn(right, step, dis + 1);
    }
    if (0x3f3f3f3f == ans) ans = -1;
    println(ans);
    return 0;
}