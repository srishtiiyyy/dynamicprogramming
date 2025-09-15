#include <bits/stdc++.h>
using namespace std;

/*
QUESTION:
You are given an m x n grid `matrix` filled with 0's and 1's.
- 0 represents an empty cell.
- 1 represents an obstacle.

You start at the top-left cell (0, 0) and your goal is to reach the bottom-right cell (m-1, n-1).
At each step, you can only move either **down** or **right**.

Return the number of unique paths from start to finish, considering obstacles.

Example:
Input:
matrix = [
  {0, 0, 0},
  {0, 1, 0},
  {0, 0, 0}
]
Output: 2
Explanation: There are two paths around the obstacle.
*/

class Solution {
private:
    // ------------------ Recursion ------------------
    int recHelper(int i, int j, vector<vector<int>>& matrix) {
        if (i < 0 || j < 0 || matrix[i][j] == 1) return 0; 
        if (i == 0 && j == 0) return 1;
        return recHelper(i - 1, j, matrix) + recHelper(i, j - 1, matrix);
    }

    // ------------------ Memoization ------------------
    int memoHelper(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
        if (i < 0 || j < 0 || matrix[i][j] == 1) return 0;
        if (i == 0 && j == 0) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = memoHelper(i - 1, j, matrix, dp) + memoHelper(i, j - 1, matrix, dp);
    }

public:
    // Recursion
    int recursion(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        return recHelper(m - 1, n - 1, matrix);
    }

    // Memoization
    int memoization(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return memoHelper(m - 1, n - 1, matrix, dp);
    }

    // Tabulation
    int tabulation(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = 0;
                }
                else if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    int up = (i > 0 ? dp[i - 1][j] : 0);
                    int left = (j > 0 ? dp[i][j - 1] : 0);
                    dp[i][j] = up + left;
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    // Space Optimized Tabulation
    int spaceOptimized(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> prev(n, 0);

        for (int i = 0; i < m; i++) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    curr[j] = 0;
                }
                else if (i == 0 && j == 0) {
                    curr[j] = 1;
                }
                else {
                    int up = (i > 0 ? prev[j] : 0);
                    int left = (j > 0 ? curr[j - 1] : 0);
                    curr[j] = up + left;
                }
            }
            prev = curr;
        }
        return prev[n - 1];
    }
};

int main() {
    vector<vector<int>> maze = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    Solution sol;

    cout << "Recursion: " << sol.recursion(maze) << endl;
    cout << "Memoization: " << sol.memoization(maze) << endl;
    cout << "Tabulation: " << sol.tabulation(maze) << endl;
    cout << "Space Optimized: " << sol.spaceOptimized(maze) << endl;

    return 0;
}
