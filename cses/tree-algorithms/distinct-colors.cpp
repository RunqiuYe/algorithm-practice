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
int n;
int k = 1;
vector<int> G[N];
int color[N];

int trav[N];
int subtree_size[N];
int trav_color[N];
int unique_color[N];
int p[N];
int ans[N];

int tree[4 * N];

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = unique_color[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        tree[p] = x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (i <= mid) {
        update(2 * p, l, mid, i, x);
    } else {
        update(2 * p + 1, mid + 1, r, i, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    int res = 0;
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

void dfs(int u, int p) {
    subtree_size[u]++;
    trav[k] = u;
    trav_color[k] = color[u];
    k++;
    for (int v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);

    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        if (mp.find(trav_color[i]) == mp.end()) {
            unique_color[i] = 1;
        } else {
            p[mp[trav_color[i]]] = i;
        }
        mp[trav_color[i]] = i;
    }
    build(1, 1, n);

    for (int k = 1; k <= n; k++) {
        int u = trav[k];
        ans[u] = query(1, 1, n, k, k + subtree_size[u] - 1);
        update(1, 1, n, k, 0);
        update(1, 1, n, p[k], 1);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
}