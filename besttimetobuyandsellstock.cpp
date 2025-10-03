#include <bits/stdc++.h>
using namespace std;

/*
Problem: Best Time to Buy and Sell Stock (LeetCode 121)
--------------------------------------------------------
You are given an array prices where prices[i] is the price of a given stock on the i-th day.

You want to maximize your profit by choosing a single day to buy one stock 
and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction.
If you cannot achieve any profit, return 0.

Example:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
*/

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int mini = prices[0];   // Minimum price seen so far
    int maxprofit = 0;      // Maximum profit
    
    for(int i = 1; i < n; i++) {
        int cost = prices[i] - mini;        // Profit if sold today
        maxprofit = max(maxprofit, cost);   // Update max profit
        mini = min(mini, prices[i]);        // Update minimum price
    }
    return maxprofit;
}

int main() {
    int n;
    cout << "Enter number of days: ";
    cin >> n;
    
    vector<int> prices(n);
    cout << "Enter stock prices: ";
    for(int i = 0; i < n; i++) cin >> prices[i];
    
    int ans = maxProfit(prices);
    cout << "Maximum Profit: " << ans << endl;
    
    return 0;
}
