// https://cses.fi/problemset/task/1751/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int n;
int G[N];
bool vis[N];
bool cycle[N];
int ans[N];
int scc_index[N];
vector<int> inc_finish;
vector<vector<int>> scc_nodes;
vector<int> scc_edge;
vector<int> scc_vis;

void dfs(int u) {
    vis[u] = true;
    int v = G[u];
    if (!vis[v]) {
        dfs(v);
    }
    inc_finish.push_back(u);
}

void dfs_transpose(int u, int j, vector<vector<int>>& transpose) {
    vis[u] = true;
    cycle[u] = true;
    for (int v : transpose[u]) {
        if (cycle[v]) continue;
        if (vis[v]) {
            scc_edge[scc_index[v]] = j;
            continue;
        }
        dfs_transpose(v, j, transpose);
    }
    scc_nodes[j].push_back(u);
    scc_index[u] = j;
    cycle[u] = false;
}

void dfs_scc(int i) {
    int j = scc_index[i];
    if (scc_vis[j]) return;
    scc_vis[j] = 1;
    dfs_scc(G[i]);
    ans[i] = ans[G[i]] + 1;
}

int main() {
    scanf("%d", &n); 
    vector<vector<int>> transpose(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &G[i]);
        transpose[G[i]].push_back(i);
    }
    // first dfs
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    // second dfs for SCC
    memset(vis, 0, sizeof(vis));
    for (int i = n - 1; i >= 0; i--) {
        int u = inc_finish[i];
        int j = scc_nodes.size();
        if (!vis[u]) {
            scc_nodes.push_back(vector<int>());
            scc_vis.push_back(0);
            scc_edge.push_back(-1);
            dfs_transpose(u, j, transpose);
            if (scc_nodes[j].size() != 1) {
                for (int x : scc_nodes[j]) {
                    ans[x] = scc_nodes[j].size();
                }
                scc_vis[j] = 1;
            }
        }
    }
    // final dfs for answer
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) {
            dfs_scc(i);
        }
    }
    // print answer
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}