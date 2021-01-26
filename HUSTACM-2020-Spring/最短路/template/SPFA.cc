#include "public.h"

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
            if (cnt[v] > n) return true;
            if (inq[v]) continue;
            inq[v] = true, hot.push(v);
        }
    }
    return false;
}

dist_t dis[N];
dist_t sum = 0, in = 0;

void spfa_optimize(int st, int n)
{
    fill(dis, dis + 1 + n, inf);
    deque<int> hot; inq.reset();
    dis[st] = 0, hot.push_back(st);
    in = 1, sum = 0;
    inq[st] = true;
    using namespace FWS;
    while (!hot.empty())
    {
        auto u = hot.front();
        while (in * dis[u] > sum)   // LLL optimize
            hot.pop_front(),
            hot.push_back(u),
            u = hot.front();
        hot.pop_front();
        inq[u] = false;
        -- in, sum -= dis[u];
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
        {
            const edge &e = ee[c];
            const auto v = e.v;
            if (dis[u] + e.w >= dis[v]) continue;
            if (inq[v]) sum -= dis[v];
            dis[v] = dis[u] + e.w;
            if (inq[v]) {sum += dis[v]; continue;}
            else inq[v] = true;
            ++ in, sum += dis[v];
            if (!hot.empty() &&     // SLF optimize
                dis[v] < dis[hot.front()])
                hot.emplace_front(v);
            else hot.emplace_back(v);    
        }
    }
}

void spfa(int st, int n)
{
    fill(dis, dis + 1 + n, inf);
    queue<int> hot; inq.reset();
    dis[st] = 0, hot.push(st);
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
            if (dis[u] + e.w >= dis[v]) continue;
            dis[v] = dis[u] + e.w;
            if (inq[v]) continue;
            inq[v] = true, hot.push(v);
        }
    }
}