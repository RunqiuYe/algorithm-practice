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

const int N = 1005;
int n, q;
int prefix[N][N];

int main() {
    scanf("%d %d ", &n, &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            scanf(" %c", &c);
            prefix[i][j] = prefix[i][j - 1];
            if (c == '*') {
                prefix[i][j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] += prefix[i - 1][j];
        }
    }
    for (int i = 1; i <= q; i++) {
        int y1, x1, y2, x2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", prefix[y2][x2] - prefix[y1 - 1][x2] -
                           prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1]);
    }
    return 0;
}