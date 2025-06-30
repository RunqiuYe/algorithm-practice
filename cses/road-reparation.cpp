// https://cses.fi/problemset/task/1675

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <cstring>
#include <queue>

typedef long long ll;

using namespace std;

struct Edge {
    int v;
    int w;
};

struct Node {
    int u;
    ll w;

    bool operator>(const Node &a) const {
        return w > a.w;
    }
};

const int N = 1e5 + 5;
int n, m;

vector<Edge> G[N];
bool vis[N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    priority_queue<Node, vector<Node>, greater<Node>> q;
    q.push({1, 0});
    int count = 0;
    ll cost = 0;

    // Prim's algorithm for MST
    while (q.size() != 0) {
        int u = q.top().u;
        ll w = q.top().w;
        q.pop();

        if (vis[u]) continue;
        vis[u] = true;
        count++;
        cost += w;

        if (count == n) {
            printf("%lld\n", cost);
            return 0;
        }
        for (Edge& e : G[u]) {
            q.push({e.v, e.w});
        }
    }

    printf("IMPOSSIBLE\n");

    return 0;
}