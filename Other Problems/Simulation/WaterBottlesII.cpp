/*
Leetcode - 3100. Water Bottles II -- Medium

You are given two integers numBottles and numExchange.
numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one 
of the following operations:
- Drink any number of full water bottles turning them into empty bottles.
- Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. 
For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.

Return the maximum number of water bottles you can drink.

Examples :- 
Input: numBottles = 13, numExchange = 6 __ Output: 15
Input: numBottles = 10, numExchange = 3 __ Output: 13

Constraints :- 1 <= numBottles <= 100 __ 1 <= numExchange <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation Based Approach
/*
Start with ans = numBottles and empty = numBottles.
While you have enough empty bottles to perform an exchange (empty >= numExchange):
- empty = empty - numExchange → you spend numExchange empty bottles to get 1 new full bottle.
- ans++ → you drink the newly received full bottle.
- empty++ → after drinking, it becomes an empty bottle.
- numExchange++ → the number of empty bottles required for the next exchange increases by 1.
*/

int maxBottlesDrunk(int numBottles, int numExchange) {
    int ans = numBottles;
    int empty = numBottles;
    while (empty >= numExchange) {
        empty = empty - numExchange;
        numExchange++;   // numExchange increases since 1 bottle is exchanged
        ans++;           // 1 new bottle is drink
        empty++;         // empty count again increases by 1 
    }
    return ans;
}

int main() {

    return 0;
}