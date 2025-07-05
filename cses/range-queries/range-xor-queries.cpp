// https://cses.fi/problemset/task/1650

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

const int N = 2e5 + 5;
const int INT_INF = 0x7f7f7f7f;
int n, q;
int nums[N];
int prefix[N];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        nums[i] = x;
        prefix[i + 1] = prefix[i] ^ x;
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", prefix[b + 1] ^ prefix[a]);
    }
    return 0;
}