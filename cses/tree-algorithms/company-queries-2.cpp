// https://cses.fi/problemset/task/1688

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
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        G[x].push_back(i);
    }
    dfs(1, 1);
    for (int i = 1; i <= q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u, v));
    }
}