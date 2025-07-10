// https://leetcode.com/problems/subsets-ii/

#include <cstring>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

class Solution {
   public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> st;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                res.push_back(st);
            } else {
                st.push_back(nums[i]);
                dfs(i + 1);
                st.pop_back();
                i++;
                while (i < n && nums[i] == nums[i - 1]) {
                    i++;
                }
                dfs(i);
            }
        };

        dfs(0);
        return res;
    }
};