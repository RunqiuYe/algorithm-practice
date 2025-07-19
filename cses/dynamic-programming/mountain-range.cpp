// https://cses.fi/problemset/task/3314

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
int n;
int heights[N];

// index for next building with greater or equal heights
int left_higher[N];
int right_higher[N];

// pointer to same height
int left_same[N];
int right_same[N];

// segment tree for left most and right most with max height
array<int, 2> tree[4 * N];

int dp[N];

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = {l, l};
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    if (heights[tree[2 * p][0]] > heights[tree[2 * p + 1][0]]) {
        tree[p] = tree[2 * p];
    } else if (heights[tree[2 * p][0]] < heights[tree[2 * p + 1][0]]) {
        tree[p] = tree[2 * p + 1];
    } else {
        tree[p] = {tree[2 * p][0], tree[2 * p + 1][1]};
    }
}

array<int, 2> query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    array<int, 2> ans1 = {0, 0};
    array<int, 2> ans2 = {0, 0};
    if (L <= mid) {
        ans1 = query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        ans2 = query(2 * p + 1, mid + 1, r, L, R);
    }
    if (ans2[0] == 0 || heights[ans1[0]] > heights[ans2[0]]) {
        return ans1;
    } else if (ans1[0] == 0 || heights[ans1[0]] < heights[ans2[0]]) {
        return ans2;
    } else {
        return {ans1[0], ans2[1]};
    }
}

void solve(int i) {
    if (dp[i] != 0) {
        return;
    }
    int l = left_higher[i];
    int r = right_higher[i];
    int res = 0;
    if (l + 1 < i) {
        int j = query(1, 1, n, l + 1, i - 1)[1];
        while (j > l && j != 0) {
            solve(j);
            res = max(res, dp[j]);
            j = left_same[j];
        }
    }
    if (i < r - 1) {
        int j = query(1, 1, n, i + 1, r - 1)[0];
        while (j < r && j != 0) {
            solve(j);
            res = max(res, dp[j]);
            j = right_same[j];
        }
    }
    dp[i] = 1 + res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &heights[i]);
    }
    build(1, 1, n);
    // use monoton stack to get left higher and right higher
    vector<int> st;
    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        if (mp.find(heights[i]) != mp.end()) {
            left_same[i] = mp[heights[i]];
        }
        mp[heights[i]] = i;

        while (!st.empty() && heights[st.back()] <= heights[i]) {
            right_higher[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    while (!st.empty()) {
        right_higher[st.back()] = n + 1;
        st.pop_back();
    }
    mp = map<int, int>();
    for (int i = n; i >= 0; i--) {
        if (mp.find(heights[i]) != mp.end()) {
            right_same[i] = mp[heights[i]];
        }
        mp[heights[i]] = i;

        while (!st.empty() && heights[st.back()] <= heights[i]) {
            left_higher[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    while (!st.empty()) {
        left_higher[st.back()] = 0;
        st.pop_back();
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        solve(i);
        res = max(res, dp[i]);
    }
    printf("%d\n", res);
}