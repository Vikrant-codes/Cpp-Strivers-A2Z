/*
Leetcode - 1518. Water Bottles

There are numBottles water bottles that are initially full of water. You can exchange numExchange empty water bottles from 
the market with one full water bottle.
The operation of drinking a full water bottle turns it into an empty bottle.
Given the two integers numBottles and numExchange, return the maximum number of water bottles you can drink.

Examples :-

Input: numBottles = 9, numExchange = 3 __ Output: 13
Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
Number of water bottles you can drink: 9 + 3 + 1 = 13.

Input: numBottles = 15, numExchange = 4 __ Output: 19
Explanation: You can exchange 4 empty bottles to get 1 full water bottle. 
Number of water bottles you can drink: 15 + 3 + 1 = 19.

Constraints :-
1 <= numBottles <= 100
2 <= numExchange <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation Approach :- Time Complexity : O(numBottles) __ Space Complexity : O(1)
/*
Initially we can drink all the bottles and empty them. Afterwards we try to exchange some empty bottles to get new full bottles.
We keep doing this exchanging unless we can't exchange the bottles anymore i.e. when empty bottles are less than required 
to exchange.
*/
int numWaterBottles(int numBottles, int numExchange) {
    int ans = numBottles;
    int emptyBottles = ans;
    while (emptyBottles >= numExchange) {
        int newBottles = emptyBottles / numExchange;
        emptyBottles = emptyBottles % numExchange;
        ans += newBottles;
        emptyBottles += newBottles;
    }
    return ans;
}

// Direct Formula Approach :- Time Complexity : O(1) __ Space Complexity : O(1)
/*
We want the total bottles drunk = initial full bottles + all bottles gained by exchanging
Step 1: Initial : You start with numBottles full bottles. So answer ≥ numBottles.
Step 2: Exchanges
-- 1. What happens in each exchange cycle?
   You need numExchange empty bottles to get 1 new full bottle.
   After drinking it, you get 1 empty back.
   So effectively:
   You “spend” numExchange empties but “recover” 1 empty again.
   Net cost per exchange = (numExchange - 1) empties.

-- 2. How many times can you pay that cost?
   You start with numBottles empties after drinking them all.
   Each extra bottle requires paying numExchange - 1.
   So the number of extra bottles you can get is: floor ( (numBottles - 1) / (numExchange - 1) )
   >> Why -1 in numerator?
      Because when you are down to exactly numExchange - 1 empties, you cannot make another full bottle (you’d need one more). 
      So effectively you can only spend up to numBottles - 1.

Step 3: Formula
Thus total bottles = ans = numBottles + (numBottles - 1) / (numExchange - 1)
*/

int numWaterBtls(int numBottles, int numExchange) {
    return numBottles + (numBottles - 1) / (numExchange - 1);
}

int main() {

    return 0;
}