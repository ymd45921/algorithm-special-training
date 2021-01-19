/**
 *
 * 不愧是省选，像 DP 又像最短路
 * 不是我说这看起来和最短路有一点点关系吗
 *
 * 考察的只是 SPFA 的思想——松弛（？）
 *
 * TLE: 妈耶我怎么被卡了==
 * TLE: 哦，原来不是卡常，是我傻逼啊（
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
    int u, v, next;
    edge() = default;
    edge(int u, int v, int next)
            : u(u), v(v), next(next) {}
};

const int N = 2e5 + 5, M = 1e6 + 5;

namespace FWS
{
    int head[N], tail[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(tail, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v)
    {
        ee[tot] = edge(u, v, head[u]);
        head[u] = tot ++;
    }

    void addReverse(int u, int v)
    {
        ee[tot] = edge(u, v, tail[u]);
        tail[u] = tot ++;
    }
}

using dist_t = longs;
const dist_t inf = 0x3f3f3f3f3f3f3f3f;

dist_t dis[N];
longs s[N], k[N];
bitset<N> inq;
vector<int> pre[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(), m;
    FWS::init(n);
    for (int u = 1; u <= n; ++ u)
    {
        scanner(s[u], k[u], m);
        while (m --)
        {
            int v = scanner.nextInt();
            FWS::addEdge(u, v);
            FWS::addReverse(v, u);
        }
    }
    queue<int> hot;
    for (int i = 1; i <= n; ++ i)
        dis[i] = k[i], hot.push(i), inq[i] = true;
    while (!hot.empty())
    {
        auto u = hot.front();
        hot.pop();
        inq[u] = false;
        using namespace FWS;
        dist_t after = s[u];
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            after += dis[ee[c].v];
        if (after >= dis[u]) continue;
        dis[u] = after;
        for (auto c = tail[u];
             c != -1;
             c = ee[c].next)
            if (!inq[ee[c].v])
                hot.push(ee[c].v),
                inq[ee[c].v].flip();
    }
    println(dis[1]);
    return 0;
}