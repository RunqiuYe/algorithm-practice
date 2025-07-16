// https://cses.fi/problemset/task/2079

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
int n;
vector<int> G[N];
int size[N];

void dfs(int u, int p) {
    size[u]++;
    for (int v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
        size[u] += size[v];
    }
}

int dfs_ans(int u, int p, int above) {
    bool flag = true;
    if (above > n / 2) {
        flag = false;
    }
    for (int v : G[u]) {
        if (v == p) continue;
        if (size[v] > n / 2) {
            flag = false;
        }
    }
    if (flag) {
        return u;
    }
    for (int v : G[u]) {
        if (v == p) continue;
        int sol = dfs_ans(v, u, above + size[u] - size[v]);
        if (sol != -1) {
            return sol;
        }
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, -1);
    int res = dfs_ans(1, -1, 0);
    printf("%d\n", res);
}