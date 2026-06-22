/*
Leetcode - 1833. Maximum Ice Cream Bars : Medium

It is a sweltering summer day, and a boy wants to buy some ice cream bars.
At the store, there are n ice cream bars. 
You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. 
The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 
Note: The boy can buy the ice cream bars in any order.
Return the maximum number of ice cream bars the boy can buy with coins coins.
You must solve the problem by counting sort. 

Examples :-

Input: costs = [1,3,2,4,1], coins = 7 __ Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.

Input: costs = [10,6,8,7,7,8], coins = 5 __ Output: 0
Explanation: The boy cannot afford any of the ice cream bars.

Input: costs = [1,6,3,1,2,5], coins = 20 __ Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.

Constraints :-
- costs.length == n
- 1 <= n <= 10^5
- 1 <= costs[i] <= 10^5
- 1 <= coins <= 10^8
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Greedy + Sorting) :- Time Complexity : O(n log n) + O(n) __ Space Complexity : O(1)
/*
>> Intuition
To maximize the number of ice cream bars purchased, we should always buy the cheapest available bar first.
In this way by buying the cheapest bars, we can maximize the number of bars purchased before running out of coins.

>> Solution 
Sort the costs array in ascending order (so that the cheapest bars come first).
Keep buying bars one by one, maintaining the total amount spent. 
As soon as the total cost exceeds the available coins, we know we cannot afford the current bar 
(or any later bar, since they are even more expensive), 
so the number of bars bought so far is the maximum possible.

>> Algorithm
1. Sort the costs array.
2. Initialize a counter to keep track of the number of bars purchased and a variable to keep track of the total cost spent so far.
3. Iterate through the sorted costs array:
    - For each cost, add it to the total cost spent so far.
    - If the total cost exceeds the available coins, return the counter (the number of bars purchased so far).
    - If the total cost is still within the available coins, increment the counter and continue to the next bar.
4. If we finish iterating through the costs array without exceeding the available coins, return counter.

>> Complexity Analysis

-> Time Complexity
    Sorting the array takes O(n log n).
    The subsequent traversal takes O(n).
    Overall: O(n logn) + O(n)
-> Space Complexity
    Ignoring the space used by the sorting algorithm's implementation, the algorithm only uses a few variables (cnt, sum).
    thus O(1)
    (If considering the internal stack space used by C++ sort, it is typically O(log n).)
*/
int maxIceCreamNaive(vector<int>& costs, int coins) {
    sort(costs.begin(), costs.end());

    int cnt = 0, sum = 0;
    for (int x : costs) {
        // if (sum + x <= coins) {
        //     sum += x;
        //     cnt++;
        // }
        // else {
        //     return cnt;
        // }

        sum += x;
        if (sum > coins)
            return cnt;
        cnt++;
    }
    return cnt;
}

// Counting Sort Approach :- Time Complexity : O(n + 10^5) ~ O(n) __ Space Complexity : O(10^5) ~ O(1)
/*
>> Intuition

The previous approach sorts the costs array and then buys the cheapest ice cream bars first. 
However, the problem specifically asks us to use counting sort.
Notice that the constraints guarantee: 1 <= costs[i] <= 10^5
Since the range of possible costs is limited, instead of sorting the entire array, 
we can count how many ice cream bars exist for each cost.
We create a frequency array where:
    freq[i] = number of ice cream bars costing i coins.
Then, we process costs from 1 to 100000 in increasing order. 
This effectively simulates the sorted order without actually sorting the array.
For each cost i, we purchase all available bars of that cost one by one until:
    we run out of bars of that cost, or
    the total spent exceeds the available coins.
Since we always consider cheaper costs before more expensive ones, 
this greedy strategy guarantees the maximum number of bars purchased.

>> Complexity Analysis
-> Time Complexity
    Building the frequency array: O(n)
    Traversing the frequency array: O(10^5)
    The inner while loop collectively executes exactly n times because every ice cream bar is processed once.
    Therefore, O(n+10^5) ~ O(n)

Since 10^5 is the maximum possible cost value, this satisfies the counting sort requirement 
and is better than the O(n \log n) sorting approach.

-> Space Complexity
    The frequency array stores counts for costs from 1 to 10^5.
    thus O(10^5)
    No additional space proportional to n is used.
*/
int maxIceCream1(vector<int>& costs, int coins) {
    int n = costs.size();
    vector<int> freq(1e5 + 1);

    for (int x : costs) 
        freq[x]++;
        
    int cnt = 0, sum = 0;
    for (int i = 1; i <= 1e5; i++) {
        if (freq[i] != 0) {
            int fr = freq[i];
            while (fr--) {
                sum += i;
                if (sum > coins)
                    return cnt;
                cnt++;
            }
            if (cnt == n)
                return cnt;
        }
    }
    return -1;
}

/*
Instead of manually counting each ice cream bar of a given cost, 
we can calculate how many bars we can afford at that cost in one step.
We can compute the remaining coins we have (remCoins = coins - sum) and 
determine how many bars of the current cost we can buy (canBuy = min(freq[i], remCoins / i)).
ex- assume we have 10 coins left and the current cost is 3,
then we can buy at most 3 bars (10 / 3 = 3). 
but if there are only 2 bars of that cost available, we can only buy 2 bars.
so, canBuy = min(freq[i], remCoins / i).
*/
int maxIceCream2(vector<int>& costs, int coins) {
    int n = costs.size();
    vector<int> freq(1e5 + 1);

    for (int x : costs) 
        freq[x]++;
        
    int bars = 0, sum = 0;
    for (int i = 1; i <= 1e5; i++) {
        if (freq[i] == 0)
            continue;

        int remCoins = coins - sum;
        int canBuy = min(freq[i], remCoins / i);
        if (canBuy == 0) 
            return bars;

        bars += canBuy;
        sum += canBuy * i;

        if (bars == n)
            return bars;
    }
    return bars;
}

// ChatGPT's solution 
// no need to use sum variable, we can directly use coins variable and update it (spend the coins) as we purchase bars
int maxIceCream(vector<int>& costs, int coins) {
    vector<int> freq(100001, 0);

    for (int cost : costs)
        freq[cost]++;
        
    int bars = 0;

    for (int cost = 1; cost <= 100000; cost++) {
        if (freq[cost] == 0)
            continue;

        if (coins < cost)
            return bars;

        int canBuy = min(freq[cost], coins / cost);

        bars += canBuy;
        coins -= canBuy * cost;         // spend the coins

        if (bars == costs.size())
            return bars;
    }

    return bars;
}


int main() {
    return 0;
}