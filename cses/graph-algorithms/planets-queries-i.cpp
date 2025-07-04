// https://cses.fi/problemset/task/1750/

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>

using namespace std;

const int N = 2e5 + 5;
const int logK = 31;

int n, q;
// p[i][j] gives the position after 2^j teleporatation starting at planet i
int p[N][logK];
int ans[N];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i][0]);
    }
    for (int j = 1; j < logK; j++) {
        for (int i = 1; i <= N; i++) {
            p[i][j] = p[p[i][j-1]][j-1];
        }
    }
    int x, k;
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &k);
        for (int j = 0; j < logK; j++) {
            if (k & (1 << j)) {
                x = p[x][j];
            }
        }
        ans[i] = x;
    }
    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}