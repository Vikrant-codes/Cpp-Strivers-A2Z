/*
Leetcode - 2483. Minimum Penalty for a Shop : Medium

You are given the customer visit log of a shop represented by a 0-indexed string customers 
consisting only of characters 'N' and 'Y':
• if the ith character is 'Y', it means that customers come at the ith hour
• whereas 'N' indicates that no customers come at the ith hour.

If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
• For every hour when the shop is open and no customers come, the penalty increases by 1.
• For every hour when the shop is closed and customers come, the penalty increases by 1.

Return the earliest hour at which the shop must be closed to incur a minimum penalty.

Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.

Examples :-

Input: customers = "YYNY" __ Output: 2
Explanation: 
- Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
- Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
- Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
- Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
- Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.

Input: customers = "NNNNN" __ Output: 0
Explanation: It is best to close the shop at the 0th hour as no customers arrive.

Input: customers = "YYYY" __ Output: 4
Explanation: It is best to close the shop at the 4th hour as customers arrive at each hour.

Constraints :-
- 1 <= customers.length <= 10^5
- customers consists only of characters 'Y' and 'N'.
*/

#include <bits/stdc++.h>
using namespace std;

// Prefix/Suffix-Sum Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Problem restated in simple terms
For any closing time t:
• If the shop is open at hour i < t and customer is 'N' → penalty, i.e. if no customer arrives while open ('N') → penalty
• If the shop is closed at hour i ≥ t and customer is 'Y' → penalty, i.e. if customer arrives after closing ('Y') → penalty
Goal: 👉 Choose the closing time 't' that minimizes total penalty

✨ Key observation (core intuition)
The total penalty is made of two independent parts:
1. Penalty from hours BEFORE closing → 'N' customers while open
2. Penalty from hours AFTER closing → 'Y' customers while closed

| So for any closing time t :- penalty = count of 'N' before closing-time + count of 'Y' after closing-time 
| penalty(t) = (count of 'N' in [0, t-1]) + (count of 'Y' in [t, end])

Main Idea :- Instead of recomputing this penalty for every closing-time t (which would be O(n²)):
👉 Start from one extreme and adjust penalties incrementally depending on countY and countN 

>> Step 1: Start with “shop never closes” -> If the shop closes after the last hour:
• All 'N' customers cause penalty
• No 'Y' customer causes penalty
So initial penalty is equal to the total count of N.
    countN = total number of 'N'
    countY = 0
    minPenalty = countN
    closingTime = n

>> Step 2: Move closing time backwards (right → left) -> Now imagine shifting the closing time one hour earlier.
Loop i from right end to start of string i.e. from customers.size() to 0.
Now, assume we close the shop at ith hour, then the ith customer will affect penalty depending whether customer[i] is 'Y' or 'N'
1. Case 1: customers[i] == 'Y' :- 
    Since this customer arrives after closing, it will increment penalty. ➡️ countY++
2. Case 2: customers[i] == 'N' :- 
    Earlier this was increasing penalty due to not having customer during open hour.
    But now since the shop is closed at ith hour, penalty due to this customer will decrement. ➡️ countN--

>> Step 3: Compute penalty at this closing time: At every closing hour i :-
| penalty = countY + countN
Because :
• countY = penalties after closing
• countN = penalties before closing

If this penalty is better, update answer:
    if (minPenalty >= penalty) {
        minPenalty = penalty;
        closingTime = i;
    }
We use >= in code, because we want the earliest closing time with minimum penalty

|   "We could also have approached this problem by maintaining a prefixSum of N instead of maintaining the suffixSum of Y.
|    As we know penalty = 'N' before closing + 'Y' after closing, so we can either countY while traversing from right to left
|    or, countN while traversing from left to right. Both approach are correct. 

⚛️ Algorithm --
1. Count total 'N' → initial penalty
2. Set closing time = n
3. Traverse customers from right to left:
    • Update countY / countN
    • Compute current penalty
    • Update minimum penalty and closing time
4. Return closing time

Time & Space Complexity
    • Time: O(n)
    • Space: O(1)

Final intuition in one sentence
|   “Start with the shop always open, then move the closing time left step-by-step while updating penalties 
|   locally instead of recomputing globally.”
*/
int bestClosingTime(string customers) {
    int closingTime = customers.size();
    int countY = 0, countN = 0;
    for (char c : customers) if (c == 'N') countN++;
    int minPenalty = countN;

    for (int i = customers.size()-1; i >= 0; i--) {
        if (customers[i] == 'Y') countY++;
        else countN--;
        int penalty = countY + countN;
        if (minPenalty >= penalty) {
            closingTime = i;
            minPenalty = penalty;
        }
    }

    return closingTime;
}

int main() {
    return 0;
}