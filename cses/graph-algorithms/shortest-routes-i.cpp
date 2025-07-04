#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <bitset>
 
typedef long long ll;
 
using namespace std;
 
struct edge {
    int v, w;
};
 
struct node {
    int i;
    ll dist;
 
    bool operator>(const node &a) const {
        return dist > a.dist;
    }
};
 
const int N = 1e5 + 1;
vector<edge> G[N];
ll ans[N];
bool vis[N];
 
int n, m;
 
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        ans[i] = LLONG_MAX;
    }
    ans[1] = 0;
    memset(vis, 0, sizeof(bool) * (n + 1));
    
    int a, b, c;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> c;
        G[a].push_back({b, c});
    }
    
    // Dijkstra's algorithm for shortest path
    priority_queue<node, vector<node>, greater<node>> q;
    q.push({1, 0});
    while (q.size() != 0) {
        int x = q.top().i;
        ll d = q.top().dist;
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto e : G[x]) {
            if (d + e.w < ans[e.v]) {
                q.push({e.v, e.w + d});
                ans[e.v] = d + e.w;
            }
        }
    }
 
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}