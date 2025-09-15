/*
🔹 Problem Statement: House Robber II
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed, but adjacent houses 
have security systems that trigger an alarm if two adjacent houses are robbed.

Now, houses are arranged in a CIRCLE. 
This means the first and the last house are also adjacent.

Return the maximum amount of money you can rob without alerting the police.

Example:
Input: nums = [1,5,1,2,6]
Output: 11
Explanation: Rob houses with money {5,6}.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // 🔹 Recursion
    int recursion(int ind, vector<int> &arr) {
        if (ind == 0) return arr[ind];
        if (ind < 0) return 0;
        int pick = arr[ind] + recursion(ind - 2, arr);
        int nonPick = recursion(ind - 1, arr);
        return max(pick, nonPick);
    }

    // 🔹 Memoization
    int memoization(int ind, vector<int> &arr, vector<int>& dp) {
        if (ind == 0) return arr[ind];
        if (ind < 0) return 0;
        if (dp[ind] != -1) return dp[ind];

        int pick = arr[ind] + memoization(ind - 2, arr, dp);
        int nonPick = memoization(ind - 1, arr, dp);

        return dp[ind] = max(pick, nonPick);
    }

    // 🔹 Tabulation
    int tabulation(vector<int> &nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];

        for (int i = 1; i < n; i++) {
            int pick = nums[i];
            if (i > 1) pick += dp[i - 2];
            int nonPick = dp[i - 1];
            dp[i] = max(pick, nonPick);
        }
        return dp[n - 1];
    }

    // 🔹 Space Optimization
    int spaceOptimized(vector<int> &nums) {
        int n = nums.size();
        int prev = nums[0];
        int prev2 = 0;

        for (int i = 1; i < n; i++) {
            int pick = nums[i];
            if (i > 1) pick += prev2;
            int nonPick = prev;
            int cur = max(pick, nonPick);

            prev2 = prev;
            prev = cur;
        }
        return prev;
    }

public:
    // Wrapper for House Robber II
    int houseRobber(vector<int>& money) {
        int n = money.size();
        if (n == 1) return money[0];

        vector<int> arr1(money.begin(), money.end() - 1); // exclude last
        vector<int> arr2(money.begin() + 1, money.end()); // exclude first

        // You can test with any approach below 👇
        // Recursion
        int ans1 = recursion(arr1.size() - 1, arr1);
        int ans2 = recursion(arr2.size() - 1, arr2);

        // Memoization
        // vector<int> dp1(arr1.size(), -1), dp2(arr2.size(), -1);
        // int ans1 = memoization(arr1.size() - 1, arr1, dp1);
        // int ans2 = memoization(arr2.size() - 1, arr2, dp2);

        // Tabulation
        // int ans1 = tabulation(arr1);
        // int ans2 = tabulation(arr2);

        // Space Optimized
        // int ans1 = spaceOptimized(arr1);
        // int ans2 = spaceOptimized(arr2);

        return max(ans1, ans2);
    }
};

int main() {
    vector<int> arr{1, 5, 1, 2, 6};
    Solution sol;

    cout << "Maximum money robbed: " << sol.houseRobber(arr) << endl;
    return 0;
}
