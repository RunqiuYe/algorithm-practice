// https://cses.fi/problemset/task/1130

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
int dp[N][2];

void dfs(int x, int p) {
    for (int v : G[x]) {
        if (v == p) continue;
        dfs(v, x);
        dp[x][0] += dp[v][1];
    }
    int s = dp[x][0];
    for (int v : G[x]) {
        if (v == p) continue;
        dp[x][1] = max(dp[x][1], 1 + s - dp[v][1] + dp[v][0]);
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
    printf("%d\n", dp[1][1]);
}