// https://cses.fi/problemset/task/1753

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

const int N = 1e6 + 5;
int pi[N];

// KMP algorithm
int main() {
    string s, t;
    getline(cin, s);
    getline(cin, t);
    t += '#';
    int n = s.length();
    int m = t.length();
    int res = 0;

    if (m > n) {
        printf("0\n");
        return 0;
    }
    // calculate prefix function pi for pattern t
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && t[i] != t[j]) {
            j = pi[j - 1];
        }
        if (t[i] == t[j]) {
            j++;
        }
        pi[i] = j;
    }
    // find occurrence of t in s
    j = pi[m];
    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != t[j]) {
            j = pi[j - 1];
        }
        if (s[i] == t[j]) {
            j++;
        }
        if (j == m - 1) {
            res++;
        }
    }
    printf("%d\n", res);
}