// https://cses.fi/problemset/task/1624

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

const int N = 8;
bool col[N];
bool up[2 * N];
bool down[2 * N];
char board[N][N];

ll solve(int i) {
    if (i == N) return 1;
    ll res = 0;
    for (int j = 0; j < N; j++) {
        if (board[i][j] == '*') continue;
        if (col[j]) continue;
        if (up[i + j]) continue;
        if (down[i - j + N]) continue;
        col[j] = up[i + j] = down[i - j + N] = true;
        res += solve(i + 1);
        col[j] = up[i + j] = down[i - j + N] = false;
    }
    return res;
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &board[i][j]);
        }
    }
    printf("%lld\n", solve(0));
}