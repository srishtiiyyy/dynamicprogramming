/*
    🔹 Problem: Climbing Stairs (LeetCode 70)

    You are climbing a staircase. It takes 'n' steps to reach the top.
    Each time you can either climb 1 step or 2 steps. 
    In how many distinct ways can you climb to the top?

    Example:
    Input: n = 5
    Output: 8
    Explanation: 
        There are 8 distinct ways to climb to the top:
        (1,1,1,1,1), (2,1,1,1), (1,2,1,1), (1,1,2,1), (1,1,1,2),
        (2,2,1), (2,1,2), (1,2,2)

    Constraints:
        • 1 <= n <= 45
*/

#include <bits/stdc++.h>
using namespace std;

// 1️⃣ Pure Recursion (Exponential Time)
int climbingstairsrecursion(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    return climbingstairsrecursion(n - 1) + climbingstairsrecursion(n - 2);
}

// 2️⃣ Recursion + Memoization (Top-Down DP)
int memoization(int n, vector<int>& dp) {
    if (n <= 1) return 1;
    if (dp[n] != -1) return dp[n];
    return dp[n] = memoization(n - 1, dp) + memoization(n - 2, dp);
}
int climbStairsMemo(int n) {
    vector<int> dp(n + 1, -1);
    return memoization(n, dp);
}

// 3️⃣ Tabulation (Bottom-Up DP)
int climbStairsTabulation(int n) {
    vector<int> dp(n + 1, -1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 4️⃣ Space Optimization (Only store last 2 values)
int climbStairsSpace(int n) {
    int prev2 = 1, prev = 1;
    for (int i = 2; i <= n; i++) {
        int cur = prev + prev2;
        prev2 = prev;
        prev = cur;
    }
    return prev;
}

int main() {
    int n;
    cin >> n;

    cout << "Recursion: " << climbingstairsrecursion(n) << endl;
    cout << "Memoization: " << climbStairsMemo(n) << endl;
    cout << "Tabulation: " << climbStairsTabulation(n) << endl;
    cout << "Space Optimized: " << climbStairsSpace(n) << endl;

    return 0;
}
