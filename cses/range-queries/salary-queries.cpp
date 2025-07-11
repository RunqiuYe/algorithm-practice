// https://cses.fi/problemset/task/1144

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
int n, q;
int salary[N];
int disc_salary[2 * N];
int tree[8 * N];
array<int, 3> queries[N];

int binsearch(int x, int m) {
    int lo = 1;
    int hi = m + 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (disc_salary[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

void update(int p, int l, int r, int i, int x) {
    if (l == r) {
        tree[p] += x;
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
    if (L > R) return 0;
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
    set<int> S;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &salary[i]);
        S.insert(salary[i]);
    }
    for (int i = 1; i <= q; i++) {
        char c;
        int a, b;
        scanf(" %c %d %d", &c, &a, &b);
        int op = c == '?' ? 0 : 1;
        queries[i] = {op, a, b};
        if (op == 1) {
            S.insert(b);
        }
    }
    int cnt = 0;

    for (auto iter = S.begin(); iter != S.end(); iter++) {
        cnt++;
        disc_salary[cnt] = *iter;
    }
    int m = cnt;

    for (int i = 1; i <= n; i++) {
        update(1, 1, m, binsearch(salary[i], m), 1);
    }
    for (int i = 1; i <= q; i++) {
        int op = queries[i][0];
        if (op == 0) {
            int a = queries[i][1];
            int b = queries[i][2];
            int l = binsearch(a, m);
            if (l == m + 1) {
                printf("0\n");
                continue;
            }
            int r = binsearch(b + 1, m) - 1;
            printf("%d\n", query(1, 1, m, l, r));
        } else {
            int k = queries[i][1];
            int x = queries[i][2];
            update(1, 1, m, binsearch(salary[k], m), -1);
            salary[k] = x;
            update(1, 1, m, binsearch(salary[k], m), 1);
        }
    }
}