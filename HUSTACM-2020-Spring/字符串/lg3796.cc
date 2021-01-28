#include <bits/stdc++.h>

using namespace std;

using char_t = char;
using string_t = const char *const;
const int N = 2e6 + 5;

namespace acAutomaton
{
    const int dict = 26;

    using node = array<int, dict>;
    using id_list = list<int>;
    using callback_t = function<void(bool, int, const id_list &)>;

    node go[N];
    int tot = 0, fail[N], cnt = 0;
    id_list index[N];
    bitset<N> vis;
    int match[N];

    inline int idx(char_t x) {return x - 'a';}

    void clear()
    {
        for (int i = 0; i <= tot; ++ i)
            go[i].fill(0), fail[i] = 0, index[i].clear();
        memset(match, 0, sizeof(int) * (cnt + 1));
        tot = cnt = 0;
    }

    void insert(const string_t &s, int n)
    {
        int u = 0;
        for (int i = 0, id = idx(s[0]);
            i < n; id = idx(s[++ i]))
            u = go[u][id] ? go[u][id] :
                (go[u][id] = ++ tot);
        index[u].push_back(++ cnt);
        match[index[u].back()] = u;
    }

    void build()
    {
        queue<int> q;
        for (int id = 0; id < dict; ++ id)
            if (go[0][id]) q.push(go[0][id]);
        while (!q.empty())
        {
            auto u = q.front(); q.pop();
            for (int id = 0; id < dict; ++ id)
                if (go[u][id])
                    fail[go[u][id]] = go[fail[u]][id],
                    q.push(go[u][id]);
                else go[u][id] = go[fail[u]][id];
        }
    }

    void test(const string_t &t, int n,
              const callback_t& accept)
    {
        int u = 0; vis.reset();
        for (int i = 0; i < n; ++ i)
        {
            int j = u = go[u][idx(t[i])];
            for (; j; j = fail[j])
                if (!index[j].empty())
                    accept(vis[j], i, index[j]),
                    vis.set(j);
        }
    }

    // Fail Tree Optimize: Stable O(n + m)

    struct {int v, next;} ee[N];
    int head[N], edges = 0, siz[N];

    void make()
    {
        const int n = acAutomaton::tot;
        memset(siz, 0, sizeof(int) * (n + 1));
        memset(head, -1, sizeof(int) * (n + 1));
        edges = 0;
        for (int i = 1; i <= n; ++ i)
            ee[edges] = {i, head[fail[i]]},
            head[fail[i]] = edges ++;
    }

    int dfs(int u)
    {
        for (int i = head[u];
             i != -1;
             i = ee[i].next)
            siz[u] += dfs(ee[i].v);
        return siz[u];
    }

    void test(const string_t &t, int n,
              vector<int> &stat)
    {
        stat.resize(cnt + 1);
        for (int i = 0, u = 0; i < n; ++ i)
            u = go[u][idx(t[i])], ++ siz[u];
        dfs(0);
        for (int i = 1; i <= cnt; ++ i)
            stat[i] = siz[match[i]];
    }
}

char s[160][110], t[N];
int cnt[160];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    while (cin >> n && n)
    {
        acAutomaton::clear();
        for (int i = 1; i <= n; ++ i)
        {
            cin >> s[i];
            int len = strlen(s[i]);
            acAutomaton::insert(s[i], len);
        }
        acAutomaton::build();
        cin >> t;
        int len = strlen(t), time = 0;
        memset(cnt, 0, sizeof cnt);
        acAutomaton::test(t, len, [&]
        (bool vis, int pos, const list<int> &id)
        {time = max(time, ++ cnt[id.front()]);});
        cout << time << endl;
        for (int i = 1; i <= n; ++ i)
            if (cnt[i] == time)
                cout << s[i] << endl;
    }
    return 0;
}