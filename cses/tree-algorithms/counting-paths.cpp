// https://cses.fi/problemset/task/1136

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
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

const int N = 2e5 + 5;
const int logN = 18;
vector<int> G[N];
int boss[N][logN];
int mark[N];

int timer = 0;
int start[N];
int finish[N];

void dfs(int x, int p) {
    timer++;
    start[x] = timer;
    boss[x][0] = p;
    for (int j = 1; j < logN; j++) {
        boss[x][j] = boss[boss[x][j - 1]][j - 1];
    }
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x);
    }
    timer++;
    finish[x] = timer;
}

void dfs_ans(int x, int p) {
    for (int v : G[x]) {
        if (v == p) continue;
        dfs_ans(v, x);
        mark[x] += mark[v];
    }
}

bool ancestor(int u, int v) {
    return start[u] <= start[v] && finish[u] >= finish[v];
}

int lca(int u, int v) {
    if (ancestor(u, v)) return u;
    if (ancestor(v, u)) return v;
    for (int j = logN - 1; j >= 0; j--) {
        if (!ancestor(boss[u][j], v)) {
            u = boss[u][j];
        }
    }
    return boss[u][0];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 1);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int anc = lca(u, v);
        mark[u]++;
        mark[v]++;
        mark[anc]--;
        if (anc != 1) {
            mark[boss[anc][0]]--;
        }
    }
    dfs_ans(1, -1);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", mark[i], " \n"[i == n]);
    }
}