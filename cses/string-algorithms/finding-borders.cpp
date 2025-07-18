// https://cses.fi/problemset/task/1732

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
int z[N];
string s;
int n;

void z_function() {
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
}

int main() {
    getline(cin, s);
    n = s.length();
    z_function();
    vector<int> res;
    for (int i = n - 1; i > 0; i--) {
        if (z[i] >= n - i) {
            res.push_back(n - i);
        }
    }
    for (int l : res) {
        printf("%d ", l);
    }
    printf("\n");
}