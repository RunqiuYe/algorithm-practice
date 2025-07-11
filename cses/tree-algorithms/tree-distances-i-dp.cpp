// https://cses.fi/problemset/task/1132

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 2e5 + 5;
vector<int> G[N];
int dist[N][2];
int ans[N];

void dfs(int x, int p) {
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x);
        int d = dist[v][0] + 1;
        if (d > dist[x][0]) {
            dist[x][1] = dist[x][0];
            dist[x][0] = d;
        } else if (d > dist[x][1]) {
            dist[x][1] = d;
        }
    }
}

void dfs_ans(int x, int p, int above) {
    ans[x] = max(1 + above, dist[x][0]);
    for (int v : G[x]) {
        if (v == p) continue;
        int d = dist[v][0] + 1;
        if (d == dist[x][0]) {
            dfs_ans(v, x, max(1 + above, dist[x][1]));
        } else {
            dfs_ans(v, x, max(1 + above, dist[x][0]));
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf(" %d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    dfs_ans(1, -1, -1);
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}