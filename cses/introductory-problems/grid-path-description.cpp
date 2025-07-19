// https://cses.fi/problemset/task/1625

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

const int N = 48;
const int D = 7;
int res = 0;
char target[N];
bool vis[D][D];

char moves[4] = {'L', 'R', 'U', 'D'};
int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void solve(int i, int j, int cnt) {
    if (i == D - 1 && j == 0 && cnt == N) {
        res++;
        return;
    }
    if (i == D - 1 && j == 0 && cnt != N) return;
    if (cnt == N && (i != D - 1 || j != 0)) return;

    bool valid[4];
    for (int k = 0; k < 4; k++) {
        int di = directions[k][0];
        int dj = directions[k][1];
        if (i + di >= D || i + di < 0) {
            valid[k] = false;
            continue;
        }
        if (j + dj >= D || j + dj < 0) {
            valid[k] = false;
            continue;
        }
        if (vis[i + di][j + dj]) {
            valid[k] = false;
            continue;
        }
        valid[k] = true;
    }

    if (valid[0] && valid[1] && !valid[2] && !valid[3]) return;
    if (!valid[0] && !valid[1] && valid[2] && valid[3]) return;

    for (int k = 0; k < 4; k++) {
        int di = directions[k][0];
        int dj = directions[k][1];
        char move = moves[k];
        if (!valid[k]) continue;
        if (target[cnt] != '?' && move != target[cnt]) continue;
        vis[i + di][j + dj] = true;
        solve(i + di, j + dj, cnt + 1);
        vis[i + di][j + dj] = false;
    }
}

int main() {
    scanf("%s", target);
    vis[0][0] = true;
    solve(0, 0, 0);
    printf("%d\n", res);
}