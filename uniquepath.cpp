/*
🔹 Problem: Unique Paths (Leetcode 62)
A robot is located at the top-left corner of an m x n grid (0,0). 
The robot can only move either down or right at any point in time.

The robot is trying to reach the bottom-right corner (m-1, n-1). 
How many possible unique paths are there?

Example:
Input: m = 3, n = 2
Output: 3
Explanation:
Right -> Right -> Down
Right -> Down -> Right
Down -> Right -> Right
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // 🔹 Recursion
    int recursion(int i, int j) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;

        int up = recursion(i - 1, j);
        int left = recursion(i, j - 1);

        return up + left;
    }

    // 🔹 Memoization
    int memoization(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int up = memoization(i - 1, j, dp);
        int left = memoization(i, j - 1, dp);

        return dp[i][j] = up + left;
    }

    // 🔹 Tabulation
    int tabulation(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else {
                    int up = (i > 0) ? dp[i - 1][j] : 0;
                    int left = (j > 0) ? dp[i][j - 1] : 0;
                    dp[i][j] = up + left;
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    // 🔹 Space Optimization
    int spaceOptimized(int m, int n) {
        vector<int> prev(n, 0);

        for (int i = 0; i < m; i++) {
            vector<int> cur(n, 0);
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    cur[j] = 1;
                } else {
                    int up = (i > 0) ? prev[j] : 0;
                    int left = (j > 0) ? cur[j - 1] : 0;
                    cur[j] = up + left;
                }
            }
            prev = cur;
        }
        return prev[n - 1];
    }

public:
    int uniquePaths(int m, int n) {
        // Recursion
        // return recursion(m - 1, n - 1);

        // Memoization
        // vector<vector<int>> dp(m, vector<int>(n, -1));
        // return memoization(m - 1, n - 1, dp);

        // Tabulation
        return tabulation(m, n);

        // Space Optimized
        // return spaceOptimized(m, n);
    }
};

int main() {
    int m = 3, n = 2;
    Solution sol;
    cout << "Number of unique paths: " << sol.uniquePaths(m, n) << endl;
    return 0;
}
