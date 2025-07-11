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
int ans[N];

pair<int, int> dfs(int x, int p) {
    int dist = 0;
    int node = x;
    for (int v : G[x]) {
        if (v == p) continue;
        pair<int, int> res = dfs(v, x);
        if (res.first + 1 > dist) {
            dist = res.first + 1;
            node = res.second;
        }
    }
    return {dist, node};
}

void dfs_ans(int x, int p, int d) {
    ans[x] = max(ans[x], d);
    for (int v : G[x]) {
        if (v == p) continue;
        dfs_ans(v, x, d + 1);
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
    pair<int, int> res = dfs(1, -1);
    int a = res.second;
    int b = dfs(a, -1).second;
    dfs_ans(a, -1, 0);
    dfs_ans(b, -1, 0);
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}