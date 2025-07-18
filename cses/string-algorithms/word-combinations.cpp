// https://cses.fi/problemset/task/1731

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

const int N = 5005;
const int MOD = 1e9 + 7;
ll cnt[N];

class Trie {
   public:
    bool end;
    Trie *data[26];
    bool used[26];

    Trie() : end(false) {
        for (int i = 0; i < 26; i++) {
            used[i] = false;
            data[i] = nullptr;
        }
    }

    void insert(string word) {
        int n = word.length();
        Trie *p = this;
        for (int i = 0; i < n; i++) {
            char c = word[i];
            if (!p->used[c - 'a']) {
                p->used[c - 'a'] = true;
                p->data[c - 'a'] = new Trie();
            }
            p = p->data[c - 'a'];
        }
        p->end = true;
    }
};

void free_trie(Trie *t) {
    for (int i = 0; i < 26; i++) {
        if (t->used[i]) {
            free_trie(t->data[i]);
        }
    }
    delete t;
}

int main() {
    string target;
    getline(cin, target);
    int n = target.length();

    Trie *t = new Trie();
    int k;
    scanf("%d ", &k);
    for (int i = 1; i <= k; i++) {
        string s;
        getline(cin, s);
        reverse(s.begin(), s.end());
        t->insert(s);
    }
    cnt[0] = 1;
    for (int i = 0; i < n; i++) {
        Trie *p = t;
        for (int j = i; j >= 0; j--) {
            char c = target[j];
            if (!p->used[c - 'a']) break;
            p = p->data[c - 'a'];
            if (p->end) {
                cnt[i + 1] += cnt[j];
                cnt[i + 1] %= MOD;
            }
        }
    }
    free_trie(t);
    printf("%lld\n", cnt[n]);
}