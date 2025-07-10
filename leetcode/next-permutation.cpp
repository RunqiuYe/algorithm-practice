// https://leetcode.com/problems/next-permutation/

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
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 1;
        while (i > 0 && nums[i - 1] >= nums[i]) {
            i--;
        }
        if (i != 0) {
            int j = i;
            while (j < n && nums[j] > nums[i - 1]) {
                j++;
            }
            j -= 1;
            int x = nums[i - 1];
            nums[i - 1] = nums[j];
            nums[j] = x;
        }
        for (int k = i; k < (n + i) / 2; k++) {
            int x = nums[k];
            nums[k] = nums[n + i - 1 - k];
            nums[n + i - 1 - k] = x;
        }
    }
};