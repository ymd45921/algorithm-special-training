/**
 *
 * 全建图是不可能的
 *
 * 然后我们可以发现，如果异或和有超过 1 位，那么可以拆开分别进行
 * 因此对于每一个点，最多也就 32 个出路，就可以建图了
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

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 2e5 + 5, M = N * 10;

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

bitset<N> vis;
dist_t dis[N];
const dist_t inf = 0x3f3f3f3f;

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

uint mask[20], ww[20];

template <class T>
int highest_bit(T x)
{return x ? sizeof(T) * 8 - 1 - __builtin_clz(x) : -1;}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, c, u, v, w, a, b;
    scanner(n, m, c);
    for (uint i = 0; i < 20u; ++ i)
        mask[i] = 1u << i, ww[i] = mask[i] * c;
    auto nn = highest_bit(n) + 1;
    FWS::init(mask[nn]);
    while (m --)
    {
        scanner(u, v, w);
        FWS::addEdge(u, v, w);
    }
    for (uint i = 0; i < mask[nn]; ++ i)
        for (int j = 0; j < nn; ++ j)
            FWS::addEdge(i, i ^ mask[j], ww[j]);
    scanner(a, b);
    dijkstra(a, mask[nn]);
    println(dis[b]);
    return 0;
}