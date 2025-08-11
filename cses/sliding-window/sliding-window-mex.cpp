// https://cses.fi/problemset/task/3219

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
int nums[N];
int ans[N];

int n, k;
map<int, int> freq;
map<int, int> intervals;

void ins(int x) {
    if (x >= k) {
        return;
    }
    if (freq.find(x) == freq.end()) {
        freq[x] = 0;
    }
    freq[x]++;

    if (freq[x] > 1) {
        return;
    }
    auto rit = intervals.upper_bound(x);
    map<int, int>::iterator lit;
    bool rflag = rit != intervals.end() && rit->first == x + 1;
    bool lflag = false;
    if (rit != intervals.begin()) {
        lit = rit;
        --lit;
        lflag = lit->second == x - 1;
    }
    if (rflag && lflag) {
        int l = lit->first;
        int r = rit->second;
        intervals.erase(lit);
        intervals.erase(rit);
        intervals.insert({l, r});
    } else if (rflag) {
        int r = rit->second;
        intervals.erase(rit);
        intervals.insert({x, r});
    } else if (lflag) {
        int l = lit->first;
        intervals.erase(lit);
        intervals.insert({l, x});
    } else {
        intervals.insert({x, x});
    }
}

void del(int x) {
    if (x >= k) {
        return;
    }
    freq[x]--;

    if (freq[x] > 0) {
        return;
    }
    auto it = intervals.upper_bound(x);
    if (it == intervals.begin()) {
        return;
    }
    --it;
    int l = it->first;
    int r = it->second;
    intervals.erase(it);
    if (l == r) {
        return;
    }
    if (l <= x - 1) {
        intervals.insert({l, x - 1});
    }
    if (x + 1 <= r) {
        intervals.insert({x + 1, r});
    }
}

int query() {
    if (intervals.empty()) {
        return 0;
    }
    auto it = intervals.begin();
    return it->first == 0 ? it->second + 1 : 0;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &nums[i]);
    }
    for (int i = 1; i < k; ++i) {
        ins(nums[i]);
    }
    for (int i = k; i <= n; ++i) {
        ins(nums[i]);
        ans[i] = query();
        del(nums[i - k + 1]);
    }
    for (int i = k; i <= n; ++i) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
}