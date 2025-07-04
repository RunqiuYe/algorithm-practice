// https://cses.fi/problemset/task/1693

#include <cstring>
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

const int N = 1e5 + 5;
int n, m;
vector<int> G[N];
int deg[N];
vector<int> res;

void dfs(int x) {
    while (G[x].size() != 0) {
        int v = G[x].back();
        G[x].pop_back();
        dfs(v);
    }
    res.push_back(x);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        deg[u]++;
        deg[v]--;
    }
    bool flag = false;
    for (int i = 2; i < n; i++) {
        if (deg[i] != 0) {
            flag = true;
            break;
        }
    }
    if (deg[1] != 1 || deg[n] != -1) {
        flag = true;
    }
    if (flag) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    dfs(1);
    if (res.size() != m + 1) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    for (int i = m; i >= 0; i--) {
        printf("%d ", res[i]);
    }
    printf("\n");
    return 0;
}