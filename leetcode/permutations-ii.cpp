// https://leetcode.com/problems/permutations-ii/

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

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> stack;
        int n = nums.size();

        function<void()> dfs = [&]() {
            if (stack.size() == n) {
                res.push_back(stack);
                return;
            }
            // put last instance of nums[i] at this position
            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                if (i != n - 1 && nums[i] == nums[i + 1] && (!vis[i + 1]))
                    continue;
                vis[i] = true;
                stack.push_back(nums[i]);
                dfs();
                vis[i] = false;
                stack.pop_back();
            }
        };

        dfs();
        return res;
    }
};