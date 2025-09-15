#include <bits/stdc++.h>
using namespace std;

/*
QUESTION:
You are given an m x n grid filled with non-negative numbers.
You start at the top-left corner and must reach the bottom-right corner.
At each step, you can only move either down or right.

Return the minimum path sum.

Example:
Input:
grid = [
  {1,3,1},
  {1,5,1},
  {4,2,1}
]
Output: 7
Explanation: Path = 1 → 3 → 1 → 1 → 1 = 7
*/

class Solution {
private:
    // ------------------ Recursion ------------------
    int recHelper(int i, int j, vector<vector<int>>& grid) {
        if (i < 0 || j < 0) return 1e9; // invalid path
        if (i == 0 && j == 0) return grid[0][0];
        return grid[i][j] + min(recHelper(i - 1, j, grid), recHelper(i, j - 1, grid));
    }

    // ------------------ Memoization ------------------
    int memoHelper(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
        if (i < 0 || j < 0) return 1e9;
        if (i == 0 && j == 0) return grid[0][0];
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = grid[i][j] + min(memoHelper(i - 1, j, grid, dp), memoHelper(i, j - 1, grid, dp));
    }

public:
    // Recursion
    int recursion(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        return recHelper(m - 1, n - 1, grid);
    }

    // Memoization
    int memoization(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return memoHelper(m - 1, n - 1, grid, dp);
    }

    // Tabulation
    int tabulation(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) dp[i][j] = grid[i][j];
                else {
                    int up = (i > 0 ? dp[i - 1][j] : 1e9);
                    int left = (j > 0 ? dp[i][j - 1] : 1e9);
                    dp[i][j] = grid[i][j] + min(up, left);
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    // Space Optimized
    int spaceOptimized(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> prev(n, 0);

        for (int i = 0; i < m; i++) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) curr[j] = grid[i][j];
                else {
                    int up = (i > 0 ? prev[j] : 1e9);
                    int left = (j > 0 ? curr[j - 1] : 1e9);
                    curr[j] = grid[i][j] + min(up, left);
                }
            }
            prev = curr;
        }
        return prev[n - 1];
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    Solution sol;

    cout << "Recursion: " << sol.recursion(grid) << endl;
    cout << "Memoization: " << sol.memoization(grid) << endl;
    cout << "Tabulation: " << sol.tabulation(grid) << endl;
    cout << "Space Optimized: " << sol.spaceOptimized(grid) << endl;

    return 0;
}
