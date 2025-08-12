// https://cses.fi/problemset/task/1110

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

const int N = 2e6 + 5;
int F[N];  // F[p] = longest border of s[k, ..., k + p]

// Booth's algorithm
int main() {
    string s;
    getline(cin, s);
    s += s;
    int n = s.length();
    int k = 0;

    for (int i = 1; i < n; ++i) {
        int j = F[i - k - 1];
        while (j != 0 && s[i] != s[k + j]) {
            if (s[i] < s[k + j]) {
                k = i - j;
            }
            j = F[j - 1];
        }
        if (s[i] == s[k + j]) {
            F[i - k] = j + 1;
        } else {
            // j = 0
            if (s[i] < s[k]) {
                k = i;
            }
            F[i - k] = 0;
        }
    }
    printf("%s\n", s.substr(k, n / 2).c_str());
}