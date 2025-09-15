/*
    🔹 Problem: Frog Jump (Dynamic Programming)

    A frog is at the 1st step of a staircase and wants to reach the nth step. 
    The frog can jump either 1 step or 2 steps at a time.
    The cost of a jump from step i to step j is |heights[i] - heights[j]|.

    Task: Find the minimum total energy the frog requires to reach the last step.

    Example:
    Input: heights = [30, 10, 60, 10, 60, 50]
    Output: 40
    Explanation: 
        The frog jumps as follows:
        30 -> 10 -> 60 -> 50
        Energy = |30-10| + |10-60| + |60-50| = 20 + 50 + 10 = 80
        But the minimum is with:
        30 -> 60 -> 50
        Energy = |30-60| + |60-50| = 30 + 10 = 40
*/

#include <bits/stdc++.h>
using namespace std;

// 1️⃣ Recursion (Exponential Time)
int frogJumpRec(int ind, vector<int>& heights) {
    if (ind == 0) return 0;
    int jumpOne = frogJumpRec(ind - 1, heights) + abs(heights[ind] - heights[ind - 1]);
    int jumpTwo = INT_MAX;
    if (ind > 1) {
        jumpTwo = frogJumpRec(ind - 2, heights) + abs(heights[ind] - heights[ind - 2]);
    }
    return min(jumpOne, jumpTwo);
}

// 2️⃣ Memoization (Top-Down DP)
int frogJumpMemo(int ind, vector<int>& heights, vector<int>& dp) {
    if (ind == 0) return 0;
    if (dp[ind] != -1) return dp[ind];
    int jumpOne = frogJumpMemo(ind - 1, heights, dp) + abs(heights[ind] - heights[ind - 1]);
    int jumpTwo = INT_MAX;
    if (ind > 1) {
        jumpTwo = frogJumpMemo(ind - 2, heights, dp) + abs(heights[ind] - heights[ind - 2]);
    }
    return dp[ind] = min(jumpOne, jumpTwo);
}

// 3️⃣ Tabulation (Bottom-Up DP)
int frogJumpTab(vector<int>& heights) {
    int n = heights.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int ind = 1; ind < n; ind++) {
        int jumpOne = dp[ind - 1] + abs(heights[ind] - heights[ind - 1]);
        int jumpTwo = INT_MAX;
        if (ind > 1)
            jumpTwo = dp[ind - 2] + abs(heights[ind] - heights[ind - 2]);
        dp[ind] = min(jumpOne, jumpTwo);
    }
    return dp[n - 1];
}

// 4️⃣ Space Optimization (Only store last 2 values)
int frogJumpSpace(vector<int>& heights) {
    int n = heights.size();
    int prev = 0, prev2 = 0; // dp[i-1], dp[i-2]
    for (int i = 1; i < n; i++) {
        int jumpOne = prev + abs(heights[i] - heights[i - 1]);
        int jumpTwo = INT_MAX;
        if (i > 1) jumpTwo = prev2 + abs(heights[i] - heights[i - 2]);
        int cur = min(jumpOne, jumpTwo);
        prev2 = prev;
        prev = cur;
    }
    return prev;
}

int main() {
    vector<int> heights = {30, 10, 60, 10, 60, 50};
    int n = heights.size();

    cout << "Recursion: " << frogJumpRec(n - 1, heights) << endl;
    vector<int> dp(n, -1);
    cout << "Memoization: " << frogJumpMemo(n - 1, heights, dp) << endl;
    cout << "Tabulation: " << frogJumpTab(heights) << endl;
    cout << "Space Optimized: " << frogJumpSpace(heights) << endl;

    return 0;
}
