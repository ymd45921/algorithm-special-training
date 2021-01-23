/**
 *
 * a * b - (a + b)  的进化版（
 *
 * 有两种情况没有最大值：
 * - 1 存在：此时可以修建任何长度，没有不能表达的数字
 * - gcd > 1：总是存在无法被表示的数字
 * 至于答案是什么？
 * - 同余最短路找到了剩余系每个余数可达到的最小值
 * - 等于找到了每个余数不可达到的最大值，用来更新就行
 * 所以就得到了答案
 *
 * 包含了 jjikkollp 提供的 O(n*a) 的同余最短路板子
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

const int N = 3e4 + 5, M = N * 2;

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

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;

bitset<N> vis;
dist_t dis[N], tmp[N];
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

int normal(const set<int> &list)
{
    int mod = *list.begin();
    FWS::init(mod);
    for (int i = 0; i < mod; ++ i)
        for (auto j : list) if (j != mod)
            FWS::addEdge(i, (i + j) % mod, j);
    dijkstra(0, mod);
    int ret = -1;
    for (int i = 1; i < mod; ++ i)
        maximize(ret, dis[i] - mod);
    return ret;
}

int jjikkollp(const set<int> &list)
{
    int mod = *list.rbegin();
    const static auto dijkstra_like =
    [&list](int st, int n) -> void  // Only for Congruence Shortest Path
    {
        memset(tmp, 0x3f, sizeof(dist_t) * (n + 1));
        deque<dist_t> tab; vis.reset();
        tmp[st] = 0, tab.push_front(st);
        while (!tab.empty())
        {
            int u = tab.front();
            tab.pop_front();
            if (vis[u]) continue;
            else vis[u] = true;
            for (auto j : list) if (j != n)
                if (u + j < n)
                    minimize(tmp[u + j], tmp[u]),
                    tab.push_front(u + j);
                else
                {
                    int v = (u + j) % n;
                    minimize(tmp[v], tmp[u] + 1);
                    tab.push_back(v);
                } else continue;
        }
        for (int i = 0; i < n; ++ i)
            dis[i] = tmp[i] * n + i;
    };
    dijkstra_like(0, mod);
    int ret = -1;
    for (int i = 1; i < mod; ++ i)
        maximize(ret, dis[i] - mod);
    return ret;
}

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
    vector<int> len(n);
    for (auto &ii : len)
        ii = scanner.nextInt();
    set<int> unique;
    for (auto ii : len)
        for (int jj = max(1, ii - m);
            jj <= ii; ++ jj)
            unique.insert(jj);
    if (unique.count(1)) return puts("-1"), 0;
    int gcd = 0;
    for (auto &i : unique) gcd = __gcd(gcd, i);
    if (gcd > 1) return puts("-1"), 0;
    println(normal(unique));
    return 0;
}