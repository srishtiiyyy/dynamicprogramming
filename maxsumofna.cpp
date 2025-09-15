/*
🔹 Problem Statement:
You are given an array `arr` of integers. 
Your task is to find the maximum sum of elements such that 
no two chosen elements are adjacent in the array.

Example:
Input: arr = [2, 1, 4, 9]
Output: 11
Explanation: We pick 2 and 9 → sum = 11
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // 🔹 1. Recursive approach
    int recursion(int ind, vector<int>& arr) {
        if (ind == 0) return arr[ind];
        if (ind < 0)  return 0;

        int pick = arr[ind] + recursion(ind - 2, arr);
        int nonPick = 0 + recursion(ind - 1, arr);

        return max(pick, nonPick);
    }

    // 🔹 2. Recursion with Memoization
    int memoization(int ind, vector<int>& arr, vector<int>& dp) {
        if (ind == 0) return arr[ind];
        if (ind < 0)  return 0;

        if (dp[ind] != -1) return dp[ind];

        int pick = arr[ind] + memoization(ind - 2, arr, dp);
        int nonPick = 0 + memoization(ind - 1, arr, dp);

        return dp[ind] = max(pick, nonPick);
    }

public:
    // Wrapper for recursion
    int nonAdjacentRecursion(vector<int>& nums) {
        return recursion(nums.size() - 1, nums);
    }

    // Wrapper for memoization
    int nonAdjacentMemo(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        return memoization(n - 1, nums, dp);
    }

    // 🔹 3. Tabulation (Bottom-Up DP)
    int nonAdjacentTabulation(vector<int>& nums) {
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

    // 🔹 4. Space Optimized DP
    int nonAdjacentSpaceOptimized(vector<int>& nums) {
        int n = nums.size();
        int prev = nums[0];
        int prev2 = 0;

        for (int i = 1; i < n; i++) {
            int pick = nums[i];
            if (i > 1) pick += prev2;
            int nonPick = prev;

            int cur_i = max(pick, nonPick);
            prev2 = prev;
            prev = cur_i;
        }
        return prev;
    }
};

int main() {
    vector<int> arr{2, 1, 4, 9};
    Solution sol;

    cout << "Recursion: " << sol.nonAdjacentRecursion(arr) << endl;
    cout << "Memoization: " << sol.nonAdjacentMemo(arr) << endl;
    cout << "Tabulation: " << sol.nonAdjacentTabulation(arr) << endl;
    cout << "Space Optimized: " << sol.nonAdjacentSpaceOptimized(arr) << endl;

    return 0;
}
