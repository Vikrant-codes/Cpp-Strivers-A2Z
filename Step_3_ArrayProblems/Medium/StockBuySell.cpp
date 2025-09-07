/*
Leetcode - 121. Best Time to Buy and Sell Stock : Easy
You are given an array prices where prices[i] is the price of a given stock on the ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : O(n^2) __ Space Complexity : O(1)
/*
Consider we buy at ith day then to get maximum profit we sell it on the day when the stock price is maximum after that day.
So for the ith day we check for the maximum stock price from (i+1)th day to the last day and we calculate the profit we can make by selling on that day.
We repeat this for all the days and choose the maximum profit we can make from all those.
*/
int maxProfitBrute(vector<int> arr) {
    int maxPro = 0;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int buy = arr[i];
        int sell = arr[i]; // sell denotes the minimum prices after the buying day and it should be greater than arr[i] to have a profit.
        for(int j=i+1; j<n; j++){
            if (arr[j] > sell) sell = arr[j]; // check for the maximum stock price after the buying day
        }
        int profit = sell - buy; // profit made by selling on that day
        maxPro = max(maxPro, profit); // choose the maximum profit from all those
    }
    return maxPro;
}

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
To sell a stock we must firstly buy it.. Now suppose we sell a stock at a particular day say ith day (arr[i]) now to get the maximum profit for selling
on that day we must buy it when the price was minimum so we check for the minimum stock prize till the day it is sold (so from arr[0] to arr[i-1]).
Similarly we check the profit we can make for selling on each day by considering the minimum prize upto that day. Here, the variable mn denotes the 
minimum stock prize upto current day. We check for the profits that can be made on selling on each day (using cost variable) and we choose the 
maximum profit from all those. 
*/
int maxProfit(vector<int> prices){
    int maxPro = 0;
    int mini = prices[0];
    for(int i=1; i<prices.size(); i++){
        int profit = prices[i] - mini;
        maxPro = max(maxPro, profit);
        if (prices[i] < mini) mini = prices[i];
    }
    return maxPro;
}

int main() {
    vector<int> arr = {7, 1, 5, 3, 6, 4};
    cout << "Maximum Profit (Brute Force): " << maxProfitBrute(arr) << endl;
    cout << "Maximum Profit (Optimized): " << maxProfit(arr) << endl;
    return 0;
}