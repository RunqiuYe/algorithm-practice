// https://cses.fi/problemset/task/1674

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

void dfs(int x) {
    int res = 0;
    for (int v : G[x]) {
        dfs(v);
        res += ans[v] + 1;
    }
    ans[x] = res;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        G[x].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}