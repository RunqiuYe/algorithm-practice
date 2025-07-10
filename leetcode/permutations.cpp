// https://leetcode.com/problems/permutations/

#include <cstring>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

class Solution {
   public:
    const static int N = 10;
    bool vis[N];

    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> st;

        function<void()> dfs = [&]() {
            if (st.size() == n) {
                res.push_back(st);
                return;
            }
            // put nums[i] at next position
            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                vis[i] = true;
                st.push_back(nums[i]);
                dfs();
                st.pop_back();
                vis[i] = false;
            }
        };

        dfs();
        return res;
    }
};