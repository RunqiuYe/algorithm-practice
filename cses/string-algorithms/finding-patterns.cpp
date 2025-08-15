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

const int K = 26;
const int N = 5e5 + 5;
const int M = 5e5 + 5;
const int SIZE = 5e5 + 5;

struct Node {
    int son[K];  // index for transition
    int fail;    // fail pointer
    int mark;    // time visited this node

    void init() {
        fill(son, son + K, 0);
        fail = 0;
        mark = 0;
    }
};

Node tr[SIZE];                // Aho-Corasick Automaton
vector<int> fail_tree[SIZE];  // fail tree for DFS
int mark[SIZE];               // time visited each node
int idx[M];                   // accept index for each pattern
int tot = 0;                  // total number of nodes

int k;
char pattern[N];
char text[N];

void insert(string pattern, int j) {
    int m = pattern.length();
    int u = 0;
    for (int i = 0; i < m; i++) {
        char c = pattern[i];
        int& v = tr[u].son[c - 'a'];
        if (v == 0) {
            tot++;
            v = tot;
            tr[v].init();
        }
        u = v;
    }
    idx[j] = u;
}

// build the AC automaton
void build() {
    // use BFS to process fail pointers
    // when nodes are pushed into queue, fail pointer is already processed
    queue<int> q;
    for (int i = 0; i < K; i++) {
        if (tr[0].son[i] != 0) {
            q.push(tr[0].son[i]);
            // tr[tr[0].son[i]].fail = 0;
            fail_tree[0].push_back(tr[0].son[i]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < K; i++) {
            if (tr[u].son[i] != 0) {
                // process fail pointer of son[i]
                tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                fail_tree[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);
                q.push(tr[u].son[i]);
            } else {
                // redirect son[i] using fail
                tr[u].son[i] = tr[tr[u].fail].son[i];
            }
        }
    }
}

// query the text string against patterns
void query(string text) {
    int n = text.length();
    int u = 0;
    for (int i = 0; i < n; i++) {
        u = tr[u].son[text[i] - 'a'];
        tr[u].mark++;
    }
}

// DFS to propogate marks along fail tree
void dfs(int u) {
    for (int v : fail_tree[u]) {
        dfs(v);
        tr[u].mark += tr[v].mark;
    }
    mark[u] = tr[u].mark;
}

int main() {
    scanf("%s", text);
    scanf("%d", &k);

    for (int i = 1; i <= k; i++) {
        scanf(" %s", pattern);
        insert(pattern, i);
    }
    build();
    query(text);
    dfs(0);
    for (int i = 1; i <= k; i++) {
        printf("%s\n", mark[idx[i]] != 0 ? "YES" : "NO");
    }
}