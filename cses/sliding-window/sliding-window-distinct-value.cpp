// https://cses.fi/problemset/task/3222

#include <algorithm>
#include <array>
#include <bit>
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

using namespace std;

typedef long long ll;

const static int N = 2e5 + 5;
int n, k;
int ans[N];
int nums[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
    }
    map<int, int> mp;
    for (int i = 1; i < k; i++) {
        int x = nums[i];
        if (mp.find(x) == mp.end()) {
            mp[x] = 0;
        }
        mp[x]++;
    }
    for (int i = k; i <= n; i++) {
        int x = nums[i];
        if (mp.find(x) == mp.end()) {
            mp[x] = 0;
        }
        mp[x]++;
        ans[i] = mp.size();

        int y = nums[i - k + 1];
        mp[y]--;
        if (mp[y] == 0) {
            mp.erase(y);
        }
    }
    for (int i = k; i <= n; i++) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
}
