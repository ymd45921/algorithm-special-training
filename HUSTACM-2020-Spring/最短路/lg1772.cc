/**
 *
 * 怎么说呢，感觉这个题目有点恶心（？）：
 *
 * 首先从模型上看，这是一个动态规划的板子：
 * - 假设 dp[i] 表示的是前 i 天送货的最小花费
 * - 首先预处理所有情况下的最短路：按照可用范围 [i, j] 来记录
 * - 那么 dp[i] 可以由 [x, i] * (i - x) + dp[x - 1] + k 更新
 * 毕竟数据范围很小，你怎么搞都行（
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

struct edge
{
    int v, next;
    longs w;
    edge() = default;
    edge(int v, longs w, int next)
            : v(v), w(w), next(next) {}
};

const int N = 25, M = N * N;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(v, w, head[u]);
        head[u] = tot ++;
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }
}

using dist_t = longs;
const dist_t inf = 0x3f3f3f3f3f3f3f3f;
dist_t dis[N];
bitset<N> inq;
bitset<N> able[110];
longs cost[110][110], f[110];

void spfa(int st, int n, bitset<N> &tag)
{
    for (int i = 1; i <= n; ++ i) dis[i] = inf;
    queue<pair<int, int>> hot; inq.reset();
    dis[st] = 0, hot.push({0, st});
    inq[st] = true;
    using namespace FWS;
    while (!hot.empty())
    {
        auto now = hot.front();
        hot.pop();
        const auto u = now.second;
        inq[u] = false;
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
        {
            const edge &e = ee[c];
            const auto v = e.v;
            if (tag[v]) continue;
            if (dis[u] + e.w >= dis[v]) continue;
            dis[v] = dis[u] + e.w;
            if (inq[v]) continue;
            inq[v] = true, hot.push({e.w, v});
        }
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
    longs n, m, k, e, u, v, w;
    scanner(n, m, k, e);
    FWS::init(m);
    while (e --)
    {
        scanner(u, v, w);
        FWS::addEdge(u, v, w);
        FWS::addEdge(v, u, w);
    }
    int d = scanner.nextInt(), p, a, b;
    while (d --)
    {
        scanner(p, a, b);
        for (int i = a; i <= b; ++ i)
            able[i].set(p);
    }
    for (int i = 1; i <= n; ++ i)
        for (int j = i; j <= n; ++ j)
        {
            bitset<N> taboo;
            for (int x = i; x <= j; ++ x)
                taboo |= able[x];
            spfa(1, m, taboo);
            cost[i][j] = dis[m];
        }
    memset(f, 0x3f, sizeof f), f[0] = 0;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < i; ++ j)
            if (cost[j + 1][i] < inf)
                minimize(f[i], f[j] + cost[j + 1][i] * (i - j) + k);
    println(f[n] - k);
    return 0;
}