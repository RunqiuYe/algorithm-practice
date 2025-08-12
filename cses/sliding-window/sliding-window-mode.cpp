// https://cses.fi/problemset/task/3224

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

int n, k;
int nums[N];
int ans[N];
map<int, int> freq;
map<int, set<int>> S;

void ins(int x) {
    if (freq.find(x) == freq.end()) {
        freq[x] = 0;
    }
    if (freq[x] != 0) {
        S[freq[x]].erase(x);
    }
    freq[x]++;
    if (S.find(freq[x]) == S.end()) {
        S[freq[x]] = set<int>();
    }
    S[freq[x]].insert(x);
}

void del(int x) {
    S[freq[x]].erase(x);
    if (S[freq[x]].empty()) {
        S.erase(freq[x]);
    }
    freq[x]--;
    if (freq[x] != 0) {
        if (S.find(freq[x]) == S.end()) {
            S[freq[x]] = set<int>();
        }
        S[freq[x]].insert(x);
    }
}

int query() {
    auto it = S.rbegin()->second;
    return *it.begin();
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