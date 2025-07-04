// https://cses.fi/problemset/task/1686/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
int n, m;
vector<int> G[N];
vector<int> transpose[N];
vector<int> inc_finish;
vector<ll> scc_coins;
vector<int> scc_dag[N];
bool scc_vis[N];
ll max_gain[N];

bool vis[N];
ll coin[N];
int group[N];

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int v : G[x]) {
        dfs(v);
    }
    inc_finish.push_back(x);
}

void dfs_transpose(int x, int j) {
    if (vis[x]) {
        if (group[x] != j) {
            scc_dag[group[x]].push_back(j);
        }
        return;
    }
    vis[x] = true;
    group[x] = j;
    scc_coins[j] += coin[x];
    for (int v : transpose[x]) {
        dfs_transpose(v, j);
    }
}

ll dfs_scc(int j) {
    if (scc_vis[j]) return max_gain[j];
    scc_vis[j] = true;
    ll res = 0;
    for (int nextj : scc_dag[j]) {
        ll branch = dfs_scc(nextj);
        res = max(res, branch);
    }
    max_gain[j] = res + scc_coins[j];
    return max_gain[j];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &coin[i]);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        transpose[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = n - 1; i >= 0; i--) {
        if (!vis[inc_finish[i]]) {
            int j = scc_coins.size();
            scc_coins.push_back(0);
            dfs_transpose(inc_finish[i], j);
        }
    }

    int m = scc_coins.size();

    ll res = 0;
    for (int j = 0; j < m; j++) {
        ll gain = dfs_scc(j);
        res = max(res, gain);
    }
    printf("%lld\n", res);
    return 0;
}