#include "public.h"

bitset<N> vis;
dist_t dis[N], k[N];
const dist_t inf = 0x3f3f3f3f;

void CongruenceSP(const list_t &a, int st)
{
    int n = *a.rbegin();
    memset(k, 0x3f, sizeof(dist_t) * (n + 1));
    deque<dist_t> tab; vis.reset();
    k[st] = 0, tab.push_front(st);
    while (!tab.empty())
    {
        int u = tab.front();
        tab.pop_front();
        if (vis[u]) continue;
        else vis[u] = true;
        for (auto j : a) if (j != n)
            if (u + j < n)
                minimize(k[u + j], k[u]),
                tab.push_front(u + j);
            else
            {
                int v = (u + j) % n;
                minimize(k[v], k[u] + 1);
                tab.push_back(v);
            } else continue;
    }
    for (int i = 0; i < n; ++ i)
        dis[i] = k[i] * n + i;
}