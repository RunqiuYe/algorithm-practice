// https://cses.fi/problemset/task/1687

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
const int logN = 18;
int boss[N][logN];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    boss[1][0] = -1;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &boss[i][0]);
    }
    for (int k = 1; k < logN; k++) {
        for (int i = 1; i <= n; i++) {
            if (boss[i][k - 1] == -1) {
                boss[i][k] = -1;
            } else {
                boss[i][k] = boss[boss[i][k - 1]][k - 1];
            }
        }
    }
    for (int j = 1; j <= q; j++) {
        int x, k;
        scanf("%d %d", &x, &k);
        for (int i = 0; i < logN; i++) {
            if (k & (1 << i)) {
                x = boss[x][i];
                if (x == -1) {
                    break;
                }
            }
        }
        printf("%d\n", x);
    }
}