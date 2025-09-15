/*
🔹 Problem Statement: House Robber I
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed, but adjacent houses 
have security systems that trigger an alarm if two adjacent houses are robbed.

Return the maximum amount of money you can rob without alerting the police.

Example:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob houses with money {2,9,1}.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // 🔹 Recursion
    int recursion(int ind, vector<int>& nums) {
        if (ind == 0) return nums[0];
        if (ind < 0) return 0;

        int pick = nums[ind] + recursion(ind - 2, nums);
        int nonPick = recursion(ind - 1, nums);

        return max(pick, nonPick);
    }

    // 🔹 Memoization
    int memoization(int ind, vector<int>& nums, vector<int>& dp) {
        if (ind == 0) return nums[0];
        if (ind < 0) return 0;
        if (dp[ind] != -1) return dp[ind];

        int pick = nums[ind] + memoization(ind - 2, nums, dp);
        int nonPick = memoization(ind - 1, nums, dp);

        return dp[ind] = max(pick, nonPick);
    }

    // 🔹 Tabulation
    int tabulation(vector<int>& nums) {
        int n = nums.size();
        vector<int> t(n + 1, 0);

        t[0] = 0;
        t[1] = nums[0];

        for (int i = 2; i <= n; i++) {
            int steal = nums[i - 1] + t[i - 2];
            int skip = t[i - 1];
            t[i] = max(steal, skip);
        }

        return t[n];
    }

    // 🔹 Space Optimization
    int spaceOptimized(vector<int>& nums) {
        int n = nums.size();
        int prev = nums[0];  // like dp[i-1]
        int prev2 = 0;       // like dp[i-2]

        for (int i = 1; i < n; i++) {
            int pick = nums[i] + (i > 1 ? prev2 : 0);
            int nonPick = prev;
            int cur = max(pick, nonPick);

            prev2 = prev;
            prev = cur;
        }
        return prev;
    }

public:
    // Wrapper function
    int rob(vector<int>& nums) {
        int n = nums.size();

        // Recursion
        // return recursion(n - 1, nums);

        // Memoization
        // vector<int> dp(n, -1);
        // return memoization(n - 1, nums, dp);

        // Tabulation
        return tabulation(nums);

        // Space Optimized
        // return spaceOptimized(nums);
    }
};

int main() {
    vector<int> nums{2, 7, 9, 3, 1};
    Solution sol;

    cout << "Maximum money robbed: " << sol.rob(nums) << endl;
    return 0;
}
