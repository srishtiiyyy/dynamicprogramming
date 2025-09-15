/*
    🔹 Problem: Frog Jump with K Distance

    A frog is at the 1st step of a staircase and wants to reach the nth step. 
    The frog can jump either 1, 2, ..., or up to k steps at a time.
    The cost of a jump from step i to step j is |heights[i] - heights[j]|.

    Task: Find the minimum total energy the frog requires to reach the last step.

    Example:
    Input: heights = [15, 4, 1, 14, 15], k = 3
    Output: 13
    Explanation: 
        Path: 15 -> 1 -> 15
        Energy = |15-1| + |1-15| = 14 + 14 = 28
        Minimum is: 15 -> 4 -> 14 -> 15
        Energy = |15-4| + |4-14| + |14-15| = 11 + 10 + 1 = 22
        Even better path: 15 -> 14 -> 15
        Energy = |15-14| + |14-15| = 1 + 1 = 2 ✅
*/

#include <bits/stdc++.h>
using namespace std;

// 1️⃣ Recursion
int frogJumpRec(int ind, vector<int> &heights, int k) {
    if (ind == 0) return 0;
    int mmStep = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = frogJumpRec(ind - j, heights, k) + abs(heights[ind] - heights[ind - j]);
            mmStep = min(mmStep, jump);
        }
    }
    return mmStep;
}

// 2️⃣ Memoization
int frogJumpMemo(int ind, vector<int> &heights, int k, vector<int>& dp) {
    if (ind == 0) return 0;
    if (dp[ind] != -1) return dp[ind];
    int mmStep = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = frogJumpMemo(ind - j, heights, k, dp) + abs(heights[ind] - heights[ind - j]);
            mmStep = min(mmStep, jump);
        }
    }
    return dp[ind] = mmStep;
}

// 3️⃣ Tabulation
int frogJumpTab(vector<int> &heights, int k) {
    int n = heights.size();
    vector<int> dp(n, 0);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        int mmSteps = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int jump = dp[i - j] + abs(heights[i] - heights[i - j]);
                mmSteps = min(mmSteps, jump);
            }
        }
        dp[i] = mmSteps;
    }
    return dp[n - 1];
}

// 4️⃣ Space Optimization
int frogJumpSpace(vector<int> &heights, int k) {
    int n = heights.size();
    vector<int> dp(k, 0); // rolling array of size k
    for (int i = 1; i < n; i++) {
        int mmSteps = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int prevIndex = (i - j) % k;
                int jump = dp[prevIndex] + abs(heights[i] - heights[i - j]);
                mmSteps = min(mmSteps, jump);
            }
        }
        dp[i % k] = mmSteps;
    }
    return dp[(n - 1) % k];
}

int main() {
    vector<int> heights = {15, 4, 1, 14, 15};
    int k = 3;
    int n = heights.size();

    cout << "Recursion: " << frogJumpRec(n - 1, heights, k) << endl;

    vector<int> dp(n, -1);
    cout << "Memoization: " << frogJumpMemo(n - 1, heights, k, dp) << endl;

    cout << "Tabulation: " << frogJumpTab(heights, k) << endl;

    cout << "Space Optimized: " << frogJumpSpace(heights, k) << endl;

    return 0;
}
