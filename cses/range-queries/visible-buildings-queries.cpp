// https://cses.fi/problemset/task/3304

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;

using namespace std;

const int N = 1e5 + 5;
const int Q = 2e5 + 5;
int n, q;
int tree[4 * N];
int buildings[N];
bool flag[N];
vector<int> left_higher[N];
array<int, 3> queries[Q];
int ans[Q];

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        tree[p] = x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (i <= mid) {
        update(2 * p, l, mid, i, x);
    } else {
        update(2 * p + 1, mid + 1, r, i, x);
    }
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tree[p];
    }
    int mid = l + (r - l) / 2;
    int res = 0;
    if (L <= mid) {
        res += query(2 * p, l, mid, L, R);
    }
    if (R > mid) {
        res += query(2 * p + 1, mid + 1, r, L, R);
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &buildings[i]);
    }
    vector<int> st;
    for (int i = n; i >= 1; i--) {
        while (st.size() != 0 && buildings[st.back()] <= buildings[i]) {
            int j = st.back();
            st.pop_back();
            left_higher[i].push_back(j);
            flag[j] = true;
        }
        st.push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        if (!flag[i]) {
            update(1, 1, n, i, 1);
        }
    }

    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        queries[i] = {a, b, i};
    }
    sort(queries + 1, queries + 1 + q);

    int lo = 1;
    for (int k = 1; k <= q; k++) {
        auto &qs = queries[k];
        int a = qs[0];
        int b = qs[1];
        int i = qs[2];
        while (lo < a) {
            for (int j : left_higher[lo]) {
                update(1, 1, n, j, 1);
            }
            lo++;
        }
        ans[i] = query(1, 1, n, a, b);
    }
    for (int i = 1; i <= q; i++) {
        printf("%d\n", ans[i]);
    }
}