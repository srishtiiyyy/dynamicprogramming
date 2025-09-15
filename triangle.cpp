#include <bits/stdc++.h>
using namespace std;

/*
QUESTION:
You are given a triangle array, return the minimum path sum from top to bottom.
At each step, you may move to an adjacent number on the row below.

Example:
Input:
triangle = [[2],
            [3,4],
            [6,5,7],
            [4,1,8,3]]
Output: 11
Explanation: Path = 2 -> 3 -> 5 -> 1 = 11
*/

class Solution {
private:
    // ---------------- Recursion ----------------
    int recHelper(int i, int j, vector<vector<int>>& triangle, int n) {
        if (i == n - 1) return triangle[i][j];
        int down = triangle[i][j] + recHelper(i + 1, j, triangle, n);
        int diagonal = triangle[i][j] + recHelper(i + 1, j + 1, triangle, n);
        return min(down, diagonal);
    }

    // ---------------- Memoization ----------------
    int memoHelper(int i, int j, vector<vector<int>>& triangle, int n, vector<vector<int>>& dp) {
        if (i == n - 1) return triangle[i][j];
        if (dp[i][j] != -1) return dp[i][j];
        int down = triangle[i][j] + memoHelper(i + 1, j, triangle, n, dp);
        int diagonal = triangle[i][j] + memoHelper(i + 1, j + 1, triangle, n, dp);
        return dp[i][j] = min(down, diagonal);
    }

    // ---------------- Tabulation ----------------
    int tabHelper(vector<vector<int>>& triangle, int n) {
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // initialize bottom row
        for (int j = 0; j < n; j++) {
            dp[n - 1][j] = triangle[n - 1][j];
        }

        // bottom-up filling
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i; j >= 0; j--) {
                int down = triangle[i][j] + dp[i + 1][j];
                int diagonal = triangle[i][j] + dp[i + 1][j + 1];
                dp[i][j] = min(down, diagonal);
            }
        }
        return dp[0][0];
    }

    // ---------------- Space Optimization ----------------
    int spaceHelper(vector<vector<int>>& triangle, int n) {
        vector<int> front(n, 0), curr(n, 0);

        // initialize last row
        for (int j = 0; j < n; j++) {
            front[j] = triangle[n - 1][j];
        }

        // bottom-up
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i; j >= 0; j--) {
                int down = triangle[i][j] + front[j];
                int diagonal = triangle[i][j] + front[j + 1];
                curr[j] = min(down, diagonal);
            }
            front = curr;
        }
        return front[0];
    }

public:
    // Wrapper functions
    int recursion(vector<vector<int>>& triangle) {
        int n = triangle.size();
        return recHelper(0, 0, triangle, n);
    }

    int memoization(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return memoHelper(0, 0, triangle, n, dp);
    }

    int tabulation(vector<vector<int>>& triangle) {
        int n = triangle.size();
        return tabHelper(triangle, n);
    }

    int spaceOptimized(vector<vector<int>>& triangle) {
        int n = triangle.size();
        return spaceHelper(triangle, n);
    }
};

int main() {
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    Solution sol;

    cout << "Recursion: " << sol.recursion(triangle) << endl;
    cout << "Memoization: " << sol.memoization(triangle) << endl;
    cout << "Tabulation: " << sol.tabulation(triangle) << endl;
    cout << "Space Optimized: " << sol.spaceOptimized(triangle) << endl;

    return 0;
}
