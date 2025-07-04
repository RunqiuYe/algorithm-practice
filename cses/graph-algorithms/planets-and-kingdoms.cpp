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
vector<vector<int>> kingdoms;
bool vis[N];
int group[N];

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int v : G[x]) {
        dfs(v);
    }
    inc_finish.push_back(x);
}
 
void dfs_transpose(int x, vector<int>& scc) {
    if (vis[x]) return;
    vis[x] = true;
    scc.push_back(x);
    for (int v : transpose[x]) {
        dfs_transpose(v, scc);
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
    for (int i = n - 1; i >= 0; i--) {
        vector<int> scc;
        dfs_transpose(inc_finish[i], scc);
        if (scc.size() != 0) {
            kingdoms.push_back(scc);
        }
    }
    int k = kingdoms.size();
    printf("%d\n", k);
    for (int j = 0; j < k; j++) {
        for (int x : kingdoms[j]) {
            group[x] = j + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", group[i]);
    }
    printf("\n");
    return 0;
}