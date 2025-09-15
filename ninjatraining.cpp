
/*
🔹 Problem: Ninja's Training
A ninja has planned an n-day training schedule. Each day he can perform one of three activities:
- Running
- Stealth training
- Fighting practice

Rules:
- The same activity cannot be done on two consecutive days.
- Each activity on each day gives some merit points.

Task:
Given an n x 3 matrix (matrix[i][0] = points for running on day i, 
matrix[i][1] = stealth, matrix[i][2] = fighting),
find the maximum merit points the ninja can earn.

Example:
Input: [[10, 40, 70], [20, 50, 80], [30, 60, 90]]
Output: 210
Explanation: Day1=fighting(70) + Day2=stealth(50) + Day3=fighting(90) = 210
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // 🔹 Recursion
    int recursion(int day, int last, vector<vector<int>>& points) {
        // Base case: first day
        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return maxi;
        }

        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                int merit = points[day][task] + recursion(day - 1, task, points);
                maxi = max(maxi, merit);
            }
        }
        return maxi;
    }

    // 🔹 Memoization
    int memoization(int day, int last, vector<vector<int>>& points, vector<vector<int>>& dp) {
        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return dp[day][last] = maxi;
        }

        if (dp[day][last] != -1) return dp[day][last];

        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                int merit = points[day][task] + memoization(day - 1, task, points, dp);
                maxi = max(maxi, merit);
            }
        }
        return dp[day][last] = maxi;
    }

    // 🔹 Tabulation
    int tabulation(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base case: day 0
        dp[0][0] = max(points[0][1], points[0][2]);
        dp[0][1] = max(points[0][0], points[0][2]);
        dp[0][2] = max(points[0][0], points[0][1]);
        dp[0][3] = max({points[0][0], points[0][1], points[0][2]});

        for (int day = 1; day < n; day++) {
            for (int last = 0; last < 4; last++) {
                int maxi = 0;
                for (int task = 0; task < 3; task++) {
                    if (task != last) {
                        int merit = points[day][task] + dp[day - 1][task];
                        maxi = max(maxi, merit);
                    }
                }
                dp[day][last] = maxi;
            }
        }

        return dp[n - 1][3];
    }

    // 🔹 Space Optimization
    int spaceOptimized(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> prev(4, 0);

        // Base case: day 0
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max({points[0][0], points[0][1], points[0][2]});

        for (int day = 1; day < n; day++) {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++) {
                int maxi = 0;
                for (int task = 0; task < 3; task++) {
                    if (task != last) {
                        int merit = points[day][task] + prev[task];
                        maxi = max(maxi, merit);
                    }
                }
                temp[last] = maxi;
            }
            prev = temp;
        }

        return prev[3];
    }

public:
    int ninjaTraining(int n, vector<vector<int>>& points) {
        // Recursion
        // return recursion(n - 1, 3, points);

        // Memoization
        // vector<vector<int>> dp(n, vector<int>(4, -1));
        // return memoization(n - 1, 3, points, dp);

        // Tabulation
        return tabulation(points);

        // Space Optimized
        // return spaceOptimized(points);
    }
};

int main() {
    vector<vector<int>> points = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    int n = points.size();

    Solution sol;
    cout << "Maximum merit points: " << sol.ninjaTraining(n, points) << endl;

    return 0;
}
