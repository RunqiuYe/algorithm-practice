// https://cses.fi/problemset/task/1646

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
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
int nums[N];
ll prefix[N];
ll ans[N];
int n, q;

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        prefix[i + 1] = prefix[i] + nums[i];
    }
    int a, b;
    for (int i = 1; i <= q; i++) {
        cin >> a >> b;
        ans[i] = prefix[b + 1] - prefix[a];
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
}