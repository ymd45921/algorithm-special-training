/**
 *
 * 差分约束模板题：
 *
 * 假设 d[i] 表示 [0, i] 中 Z 包含的数字数量
 * 那么 [a, b] 中要包含 c 个数：d[b] - d[a-1] >= c
 * 这就变成了一个差分约束系统了。
 * 特别需要注意，隐含条件是 d[i] - d[i-1] <= 1
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
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
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

const int N = 50005, M = N * 2;
const int inf = 0x3f3f3f3f;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

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
        ee[tot] = edge(u, v, w, head[u]);
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

template <class _n_Array>
bool SPFA$bfsVersion(int n, int st, _n_Array &dis)
{
    for (int i = 1; i <= n; ++ i) dis[i] = -inf;
    for (int i = 0; i <= st; ++ i) dis[i] = 0;
    bitset<N> inQue;
    queue<int> hot;
    vector<int> path(n + 1);
    dis[st] = 0, inQue[st] = true,
    path[st] = 1, hot.push(st);
    bool nega = false;
    while (!hot.empty())
    {
        int u = hot.front();
        hot.pop(), inQue[u] = false;            //// 出队后取消标记
        FWS::forEach(u, [&](const edge &e)
        {
            if (nega) return;
            auto [uu, v, w, x] = e;
            if (dis[u] + w <= dis[v]) return;   //// TIP: 三角不等式松弛
            else dis[v] = dis[u] + w;
            path[v] = path[u] + 1;              //// 维护路径上最大可能的节点个数
            if (path[v] > n) return void(nega = true);  //// 发现负环
            if (inQue[v]) return;
            inQue[v].flip(), hot.push(v);       //// 和 dij 不同，不需要现在的路径长度
        });
        if (nega) break;
    }
    return !nega;           //// 没有发现负环
}

template <class _n_Array>
void spfa(int n, int st, _n_Array dis)
{
    for (int i = st; i <= n; ++ i) dis[i] = -inf;
    for (int i = 0; i <= st; ++ i) dis[i] = 0;
    using node_t = pair<int, int>;
    bitset<N> inq; queue<node_t> hot;
    dis[st] = 0, hot.push({0, st});
    inq[st] = true;
    while (!hot.empty())
    {
        auto now = hot.front();
        hot.pop();
        const auto u = now.second;
        inq[u] = false;     // 注意：SPFA 出队后需要取消标记
        FWS::forEach(u, [&](const edge &e)
        {
            const auto v = e.v;
            if (dis[u] + e.w <= dis[v]) return;
            dis[v] = dis[u] + e.w;
            if (inq[v]) return;
            inq[v] = true, hot.push({e.w, v});    // 注意：这里和 dij 不一样
        });
    }
}

#define d(x) (x + 1)
int dis[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(), a, b, c;
    FWS::init();
    int ma = 0, mi = inf;
    for (int i = 1; i <= n; ++ i)
    {
        scanner(a, b, c);
        FWS::addEdge(d(a - 1), d(b), c);    // d[b] - d[a - 1] >= c
        maximize(ma, b), minimize(mi, a);
    }
    for (int i = mi; i <= ma; ++ i)
        FWS::addEdge(d(i - 1), d(i), 0),    // d[i] - d[i - 1] >= 0
                FWS::addEdge(d(i), d(i - 1), -1);   // d[i - 1] - d[i] >= -1
    auto nonNeg = SPFA$bfsVersion(d(ma), d(mi - 1), dis);
    watch(nonNeg);
    // spfa(d(ma), d(mi - 1), dis);
    println(dis[d(ma)]);
    return 0;
}
