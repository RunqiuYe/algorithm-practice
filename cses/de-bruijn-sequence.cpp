// https://cses.fi/problemset/result/13567081/

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

const int N = 15;
const int M = 1 << N;
bool edge[M][2];
vector<int> res;

int n;

// Hierholzer algorithm, use res to keep track of edge
void dfs(int x, int option, int mask) {
    for (int i = 0; i < 2; i++) {
        if (edge[x][i]) continue;
        edge[x][i] = true;
        int v = ((x << 1) | i) & mask;
        dfs(v, i, mask);
    }
    res.push_back(option);
}

int main() {
    scanf("%d", &n);
    int mask = (1 << 31) >> (32 - n);
    mask = ~mask;
    dfs(0, -1, mask);
    res.pop_back();
    // always start with 0 node, add correct number of 0
    for (int i = 0; i < n - 1; i++) {
        res.push_back(0);
    }
    // print answer
    int m = res.size();
    for (int i = 0; i < m; i++) {
        printf("%d", res[i]);
    }
    printf("\n");
    return 0;
}