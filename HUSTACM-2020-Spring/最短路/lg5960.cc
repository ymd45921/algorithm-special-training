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

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;
using list_t = vector<int>;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 1e5 + 5, M = N * 2;

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

const dist_t inf = 0x3f3f3f3f;

dist_t pe[N];
int cnt[N];
bitset<N> inq;

bool spfa_nega_ring(int st, int n)
{
    for (int i = 1; i <= n; ++ i) pe[i] = inf;
    queue<int> hot;
    memset(cnt, 0, sizeof(int) * (n + 1)), inq.reset();
    pe[st] = 0, hot.push(st), cnt[st] = 1;
    inq[st] = true;
    using namespace FWS;
    while (!hot.empty())
    {
        const auto u = hot.front();
        hot.pop();
        inq[u] = false;
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
        {
            const edge &e = ee[c];
            const auto v = e.v;
            if (pe[u] + e.w >= pe[v]) continue;
            pe[v] = pe[u] + e.w;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] > n + 1) return true;    // Virtual Node
            if (inq[v]) continue;
            inq[v] = true, hot.push(v);
        }
    }
    return false;
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
    FWS::init(n);
    while (m --)
    {
        int u, v, w;
        scanner(u, v, w);
        FWS::addEdge(v, u, w);
    }
    for (int i = 1; i <= n; ++ i)
        FWS::addEdge(0, i, 0);
    bool ring = spfa_nega_ring(0, n);
    if (ring) puts("NO");
    else for (int i = 1; i <= n; ++ i)
        print(pe[i], " \n"[i == n]);
    return 0;
}