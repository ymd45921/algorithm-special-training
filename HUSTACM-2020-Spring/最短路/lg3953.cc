/**
 *
 * WA: 妈耶，前向星改错了
 * 
 * DP 写的时候冷静点不好吗？
 * 210122: 方法 1 Passed.
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
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 1e5 + 5, M = N * 2;

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

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    void addReverse(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, tail[u]);
        tail[u] = tot ++;
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }

    template <class fun>
    void rForEach(int u, const fun process)
    {
        for (auto c = tail[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }
}

namespace FWS0
{
    int head[N], in[N], top[N];
    int tot;
    edge ee[M];
    bitset<N> is;

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(in, 0, sizeof(int) * (n + 1));
        tot = 0, is.reset();
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++, ++ in[v];
        is[u] = is[v] = true;
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }

    void topSort(int n)
    {
        memset(top, 0, sizeof(int) * (n + 1));
        queue<int> zero; int cnt = 0;
        for (int i = 1; i <= n; ++ i)
            if (is[i] && !in[i]) zero.push(i);
        while (!zero.empty())
        {
            int u = zero.front(); zero.pop();
            top[u] = ++ cnt;
            forEach(u, [&](const edge &e)
            {if (!-- in[e.v]) zero.push(e.v);});
        }
    }
}

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;

const dist_t inf = 0x3f3f3f3f;

bitset<N> vis;
dist_t dis[N], sid[N];
int in[N];

void dijkstra(int st, int n)
{
    memset(dis, 0x3f, sizeof(dist_t) * (n + 1));
    heap_t heap; vis.reset();
    dis[st] = 0, heap.push({0, st});
    while (!heap.empty())
    {
        auto now = heap.top();
        heap.pop();
        const auto u = now.second;
        if (vis[u]) continue;
        else vis[u] = true;
        FWS::forEach(u, [&](const edge &e)
        {
            const auto v = e.v;
            if (dis[u] + e.w >= dis[v]) return;
            dis[v] = dis[u] + e.w;
            heap.push({dis[v], v});
        });
    }
}

void rDijkstra(int st, int n)
{
    memset(sid, 0x3f, sizeof(dist_t) * (n + 1));
    heap_t heap; vis.reset();
    sid[st] = 0, heap.push({0, st});
    while (!heap.empty())
    {
        auto now = heap.top();
        heap.pop();
        const auto u = now.second;
        if (vis[u]) continue;
        else vis[u] = true;
        FWS::rForEach(u, [&](const edge &e)
        {
            const auto v = e.v;
            if (sid[u] + e.w >= sid[v]) return;
            sid[v] = sid[u] + e.w;
            heap.push({sid[v], v});
        });
    }
}

dist_t f[N][60];

//longs method2(int n, int k, int p)
//{
//    rDijkstra(n, n);
//    memset(f, 0, sizeof f);
//    fill(f[n], f[n] + k + 1, 1);
//    bitset<N> ins;
//    const function dfs = [&](int u)
//    {
//        ins[u] = true;
//        FWS::rForEach(u, [&](const edge &e)
//        {
//            int now = sid[e.v] + e.w - sid[u];
//            for (int kk = now - sid[e.v]; kk <= k; ++ kk);
//        });
//        ins[u] = false;
//    };
//}

longs method1(int n, int k, int p)  // Passed.
{
    dijkstra(1, n), rDijkstra(n, n);
    vector<pair<pair<int, int>, int>> update;
    FWS0::topSort(n);
    for (int i = 1; i <= n; ++ i)
        if (FWS0::in[i] && dis[i] + sid[i] <= dis[n] + k)
            return -1;
    for (int i = 1; i <= n; ++ i)
        update.push_back({{dis[i], FWS0::top[i]}, i});
    sort(update.begin(), update.end());
    memset(f, 0, sizeof f);
    f[1][0] = 1;
    for (int x = 0; x <= k; ++ x)
        for (auto &[info, ii] : update)
            FWS::forEach(ii, [&](const edge &e)
            {
               auto tmp = dis[e.u] + x + e.w - dis[e.v];
               if (tmp <= k) f[e.v][tmp] += f[e.u][x], f[e.v][tmp] %= p;
            });
    longs sum = 0;
    for (int i = 0; i <= k; ++ i)
        sum = (sum + f[n][i]) % p;
    return sum;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    while (T --)
    {
        int n, m, k, p, a, b, c;
        scanner(n, m, k, p);
        FWS::init(n), FWS0::init(n);
        memset(in, 0, sizeof(int) * (n + 1));
        while (m --)
        {
            scanner(a, b, c);
            FWS::addEdge(a, b, c);
            FWS::addReverse(b, a, c);
            if (!c) FWS0::addEdge(a, b, c);
        }
        println(method1(n, k, p));
    }
    return 0;
}