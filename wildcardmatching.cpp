#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
-----------------
You are given two strings:
- str (the text)
- pat (the pattern which may contain wildcard characters)

Wildcard rules:
1. '?' matches exactly one character.
2. '*' matches zero or more characters.

Return true if the pattern matches the entire string, otherwise false.

Examples:
---------
Input: str = "abdefcd", pat = "ab*cd"
Output: true

Input: str = "abcdef", pat = "a*d?f"
Output: true

Input: str = "abc", pat = "a*c?"
Output: false
*/

class Solution {
private:
    // Utility: check if substring pat[0..i] is all '*'
    bool isAllStars(string &pat, int i) {
        for (int j = 0; j <= i; j++) {
            if (pat[j] != '*') return false;
        }
        return true;
    }

    /* -------------------- 1. PURE RECURSION -------------------- */
    bool recursionUtil(string &pat, string &str, int i, int j) {
        if (i < 0 && j < 0) return true;
        if (i < 0 && j >= 0) return false;
        if (j < 0 && i >= 0) return isAllStars(pat, i);

        if (pat[i] == str[j] || pat[i] == '?')
            return recursionUtil(pat, str, i - 1, j - 1);
        if (pat[i] == '*')
            return recursionUtil(pat, str, i - 1, j) || recursionUtil(pat, str, i, j - 1);

        return false;
    }

    /* -------------------- 2. MEMOIZATION -------------------- */
    bool memoUtil(string &pat, string &str, int i, int j, vector<vector<int>> &dp) {
        if (i < 0 && j < 0) return true;
        if (i < 0 && j >= 0) return false;
        if (j < 0 && i >= 0) return isAllStars(pat, i);

        if (dp[i][j] != -1) return dp[i][j];

        if (pat[i] == str[j] || pat[i] == '?')
            return dp[i][j] = memoUtil(pat, str, i - 1, j - 1, dp);
        if (pat[i] == '*')
            return dp[i][j] = memoUtil(pat, str, i - 1, j, dp) || memoUtil(pat, str, i, j - 1, dp);

        return dp[i][j] = false;
    }

public:
    // Recursion
    bool wildCardRecursion(string str, string pat) {
        return recursionUtil(pat, str, pat.size() - 1, str.size() - 1);
    }

    // Memoization
    bool wildCardMemo(string str, string pat) {
        int n = str.size(), m = pat.size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return memoUtil(pat, str, m - 1, n - 1, dp);
    }

    // Tabulation
    bool wildCardTabulation(string str, string pat) {
        int n = str.size(), m = pat.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        dp[0][0] = true;
        for (int i = 1; i <= m; i++) {
            dp[i][0] = isAllStars(pat, i - 1);
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (pat[i - 1] == str[j - 1] || pat[i - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if (pat[i - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = false;
            }
        }
        return dp[m][n];
    }

    // Space Optimization
    bool wildCardSpaceOpt(string str, string pat) {
        int n = str.size(), m = pat.size();
        vector<bool> prev(n + 1, false), curr(n + 1, false);

        prev[0] = true;
        for (int i = 1; i <= m; i++) {
            curr[0] = isAllStars(pat, i - 1);
            for (int j = 1; j <= n; j++) {
                if (pat[i - 1] == str[j - 1] || pat[i - 1] == '?')
                    curr[j] = prev[j - 1];
                else if (pat[i - 1] == '*')
                    curr[j] = prev[j] || curr[j - 1];
                else
                    curr[j] = false;
            }
            prev = curr;
        }
        return prev[n];
    }
};

int main() {
    Solution sol;
    string str = "abdefcd";
    string pat = "ab*cd";

    cout << "Recursion: " << (sol.wildCardRecursion(str, pat) ? "Match" : "No Match") << endl;
    cout << "Memoization: " << (sol.wildCardMemo(str, pat) ? "Match" : "No Match") << endl;
    cout << "Tabulation: " << (sol.wildCardTabulation(str, pat) ? "Match" : "No Match") << endl;
    cout << "Space Optimization: " << (sol.wildCardSpaceOpt(str, pat) ? "Match" : "No Match") << endl;

    return 0;
}
