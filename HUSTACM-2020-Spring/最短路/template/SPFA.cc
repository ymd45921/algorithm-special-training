#include "public.h"

dist_t pe[N];
int cnt[N];
bitset<N> inq; 

bool spfa_nega_ring(int st, int n)
{
    for (int i = 1; i <= n; ++ i) pe[i] = inf;
    queue<pair<int, int>> hot;
    memset(cnt, 0, sizeof(int) * (n + 1)), inq.reset();
    pe[st] = 0, hot.push({0, st}), cnt[st] = 1;
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
            if (pe[u] + e.w >= pe[v]) continue;
            pe[v] = pe[u] + e.w;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] > n) return true;
            if (inq[v]) continue;
            inq[v] = true, hot.push({e.w, v});
        }
    }
    return false;
}