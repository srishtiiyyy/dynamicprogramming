#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /* -------------------- 1. PURE RECURSION -------------------- */
    int recursionUtil(string& S1, string& S2, int i, int j) {
        if (i < 0) return j + 1;   // Insert remaining chars of S2
        if (j < 0) return i + 1;   // Delete remaining chars of S1

        if (S1[i] == S2[j]) return recursionUtil(S1, S2, i - 1, j - 1);

        return 1 + min({ recursionUtil(S1, S2, i - 1, j - 1),  // Replace
                         recursionUtil(S1, S2, i - 1, j),      // Delete
                         recursionUtil(S1, S2, i, j - 1) });   // Insert
    }

    /* -------------------- 2. MEMOIZATION -------------------- */
    int memoUtil(string& S1, string& S2, int i, int j, vector<vector<int>>& dp) {
        if (i < 0) return j + 1;
        if (j < 0) return i + 1;

        if (dp[i][j] != -1) return dp[i][j];

        if (S1[i] == S2[j]) 
            return dp[i][j] = memoUtil(S1, S2, i - 1, j - 1, dp);

        return dp[i][j] = 1 + min({ memoUtil(S1, S2, i - 1, j - 1, dp), 
                                    memoUtil(S1, S2, i - 1, j, dp), 
                                    memoUtil(S1, S2, i, j - 1, dp) });
    }

public:
    // Pure Recursion
    int editDistanceRecursion(string start, string target) {
        return recursionUtil(start, target, start.size() - 1, target.size() - 1);
    }

    // Memoization
    int editDistanceMemo(string start, string target) {
        int n = start.size(), m = target.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return memoUtil(start, target, n - 1, m - 1, dp);
    }

    // Tabulation
    int editDistanceTabulation(string start, string target) {
        int n = start.size(), m = target.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (start[i - 1] == target[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min({ dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1] });
            }
        }
        return dp[n][m];
    }

    // Space Optimization
    int editDistanceSpaceOpt(string start, string target) {
        int n = start.size(), m = target.size();
        vector<int> prev(m + 1, 0), cur(m + 1, 0);

        for (int j = 0; j <= m; j++) prev[j] = j;

        for (int i = 1; i <= n; i++) {
            cur[0] = i;
            for (int j = 1; j <= m; j++) {
                if (start[i - 1] == target[j - 1])
                    cur[j] = prev[j - 1];
                else
                    cur[j] = 1 + min({ prev[j - 1], prev[j], cur[j - 1] });
            }
            prev = cur;
        }
        return prev[m];
    }
};

int main() {
    Solution sol;
    string s1 = "horse", s2 = "ros";

    cout << "Recursion: " << sol.editDistanceRecursion(s1, s2) << endl;
    cout << "Memoization: " << sol.editDistanceMemo(s1, s2) << endl;
    cout << "Tabulation: " << sol.editDistanceTabulation(s1, s2) << endl;
    cout << "Space Optimization: " << sol.editDistanceSpaceOpt(s1, s2) << endl;

    return 0;
}
