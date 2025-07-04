// https://cses.fi/problemset/task/1690

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 21;
const int MOD = 1e9 + 7;
int n, m;
vector<int> G[N];
ll res[1 << N][N];

ll dfs(int vis, int x) {
    if ((vis == (1 << n) - 1) && x == n) return 1;
    if ((vis == (1 << n) - 1) || x == n) return 0;
    if (res[vis][x] != -1) return res[vis][x];
    ll cnt = 0;
    for (int v : G[x]) {
        if ((vis >> (v - 1)) & 1) continue;
        int new_vis = vis | (1 << (v - 1));
        cnt += dfs(new_vis, v);
        cnt %= MOD;
    }
    res[vis][x] = cnt;
    return cnt;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(res, -1, sizeof(res));
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
    }
    int vis = 1;
    dfs(vis, 1);
    printf("%lld\n", res[vis][1]);
    return 0;
}