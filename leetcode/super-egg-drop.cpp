// https://leetcode.com/problems/super-egg-drop/

#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

const static int N = 1e4 + 5;
const static int K = 100 + 5;
int f[N][K];

int superEggDrop(int k, int n) {
    for (int i = 1; i <= n + 1; i++) {
        f[i][1] = i - 1;
    }
    for (int j = 2; j <= k; j++) {
        f[1][j] = 0;
        int opt = 1;
        for (int i = 2; i <= n + 1; i++) {
            while (opt < i - 1 && f[opt][j - 1] < f[i - opt][j]) {
                opt++;
            }
            f[i][j] = 1 + max(f[opt][j - 1], f[i - opt][j]);
            if (opt != 1) {
                f[i][j] =
                    min(f[i][j], 1 + max(f[opt - 1][j - 1], f[i - opt + 1][j]));
            }
        }
    }
    return f[n + 1][k];
}

int main() {
    int n, k;
    scanf("%d %d", &k, &n);
    printf("%d\n", superEggDrop(k, n));
}