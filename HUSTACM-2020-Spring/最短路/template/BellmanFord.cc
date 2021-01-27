#include "public.h"

dist_t dis[N];

bool bellman_ford(int st, int n)
{
    fill(dis, dis + 1 + n, inf);
    using FWS::ee, FWS::tot;
    dis[st] = 0;
    for (int i = 1; i < n; ++ i)    // 0 is not a node
        for (int j = 0; j < tot; ++ j)
            if (dis[ee[j].u] + ee[j].w < dis[ee[j].v])
                dis[ee[j].v] = dis[ee[j].u] + ee[j].w;
    for (int j = 0; j < tot; ++ j)
        if (dis[ee[j].u] + ee[j].w < dis[ee[j].v])
            return true;
    return false;                    
}