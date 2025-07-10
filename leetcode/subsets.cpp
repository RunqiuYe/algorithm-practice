// https://leetcode.com/problems/subsets/

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
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> st;
        int n = nums.size();

        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                res.push_back(st);
                return;
            }
            // skip this element
            dfs(i + 1);

            // take this element
            st.push_back(nums[i]);
            dfs(i + 1);
            st.pop_back();
        };

        dfs(0);
        return res;
    }
};