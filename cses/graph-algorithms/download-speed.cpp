// https://cses.fi/problemset/task/1694/

#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 505;
int n, m;
vector<int> G[N];
ll cap[N][N];
int pre[N];
const ll LL_INF = 0x7f7f7f7f7f7f7f7f;

// Edmonds–Karp algorithm for max flow
ll bfs(int s, int t) {
    fill(pre, pre + n + 1, -1);
    pre[s] = 0;

    queue<pair<int, ll>> q;
    q.push({s, LL_INF});
    while (q.size() != 0) {
        int u = q.front().first;
        ll flow = q.front().second;
        q.pop();
        for (int v : G[u]) {
            if (pre[v] == -1 && cap[u][v] > 0) {
                pre[v] = u;
                ll new_flow = min(flow, cap[u][v]);

                if (v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(int s, int t) {
    ll flow = 0;
    ll aug = 0;
    while ((aug = bfs(s, t)) > 0) {
        flow += aug;
        int u = t;
        while (u != s) {
            cap[pre[u]][u] -= aug;
            cap[u][pre[u]] += aug;
            u = pre[u];
        }
    }
    return flow;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        G[u].push_back(v);
        G[v].push_back(u);
        cap[u][v] += w;
    }
    printf("%lld\n", maxflow(1, n));
    return 0;
}