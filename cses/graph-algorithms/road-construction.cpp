// https://cses.fi/problemset/task/1676

#include <iostream>

using namespace std;

const int N = 1e5 + 5;
int n, m;
int par[N];
int ran[N];
int size = 1;

// union find algorithm
int find(int x) {
    if (x != par[x]) {
        par[x] = find(par[x]);
    }
    return par[x];
}

bool unite(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) {
        return false;
    }
    if (ran[py] > ran[px]) {
        par[px] = py;
        ran[py] += ran[px];
        size = max(size, ran[py]);
    } else {
        par[py] = px;
        ran[px] += ran[py];
        size = max(size, ran[px]);
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        ran[i] = 1;
        par[i] = i;
    }
    int component = n;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (unite(u, v)) {
            component--;
        }
        printf("%d %d\n", component, size);
    }
    return 0;
}