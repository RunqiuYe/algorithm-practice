// https://leetcode.com/problems/subsets-ii/

#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
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
                return;
            }
            // take this element
            st.push_back(nums[i]);
            dfs(i + 1);
            st.pop_back();

            // if skipping this element, skip every instance
            i++;
            while (i < n && nums[i] == nums[i - 1]) {
                i++;
            }
            dfs(i);
        };

        dfs(0);
        return res;
    }
};