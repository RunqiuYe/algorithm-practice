// https://cses.fi/problemset/task/1682/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int N = 1e5 + 5;
int n, m;
vector<int> G[N];
vector<int> transpose[N];
vector<int> inc_finish;
vector<int> scc;
bool vis[N];

void print_vector(vector<int> data, int i, int j) {
    for (int k = i; k <= j; k++) {
        printf("%d ", data[k]);
    }
    printf("\n");
}

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int v : G[x]) {
        dfs(v);
    }
    inc_finish.push_back(x);
}

void dfs_transpose(int x) {
    if (vis[x]) return;
    vis[x] = true;
    scc.push_back(x);
    for (int v : transpose[x]) {
        dfs_transpose(v);
    }
}

int main() {
    scanf("%d %d", &n, &m);
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
    dfs_transpose(inc_finish[n - 1]);
    if (scc.size() == n) {
        printf("YES\n");
        return 0;
    }
    printf("NO\n");
    int v = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            v = i;
            break;
        }
    }
    printf("%d %d\n", v, scc[0]);
    return 0;
}