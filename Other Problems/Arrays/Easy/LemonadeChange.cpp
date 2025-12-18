/*
Leetcode - 860. Lemonade Change : Easy

At a lemonade stand, each lemonade costs $5. 
Customers are standing in a queue to buy from you and order one at a time (in the order specified by bills). 
Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill. 
You must provide the correct change to each customer so that the net transaction is that the customer pays $5.

Note that you do not have any change in hand at first.

Given an integer array bills where bills[i] is the bill the ith customer pays, 
return true if you can provide every customer with the correct change, or false otherwise.

Examples :-

Input: bills = [5,5,5,10,20] __ Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.

Input: bills = [5,5,10,10,20] __ Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can not give the change of $15 back because we only have two $10 bills.
Since not every customer received the correct change, the answer is false.

Constraints :-
- 1 <= bills.length <= 10^5
- bills[i] is either 5, 10, or 20.
*/

#include <bits/stdc++.h>
using namespace std;

// Greedy Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
Observations :-
• Each customer can pay with either a 5$, 10$ or 20$ bill and can buy only one lemonade worth 5$.
• We need to return true only if it is possible to provide correct change to each customer.
• We also need to consider that we don't have any change in hand at first. 
• Assume, the customer buys a lemonade then what are the different possible scenarios of providing change to him.
- Case 1 : Customer provides 5$ bill :- No need to provide change.
- Case 2 : Customer provides 10$ bill :- We need to provide 5$ change to the customer.
- Case 3 : Customer provides 20$ bill :- We need to provide 15$ change to the customer.

• We see that the we would either need to provide 5$ or 15$ worth of change depending on the amount the customer pays.
• Change providing conditions :- 
- Case 1 : 5$ change
    • The 5$ worth of change can only be given by a 5$ bill that we have received by early customers.
- Case 2 : 15$ change
    • The 15$ worth of change can be given as either a 10$ bill + 5$ bill or three 5$ bills , i.e., 5$ + 5$ + 5$.
    • We will provide the 15 $ change (either 10$ + 5$ or 5$ + 5$ + 5$) based on availability of bills we have.
    • Since, 5$ are the smallest bills we need to conserve them for future changes, so if we have 10$ bills available 
    we will firstly use them to provide change. i.e., give out 10$ + 5$.
    • If we don't have 10$ bill, then we will provide 5$ + 5$ + 5$ bills as change (if possible)

• In any case we won't be using 20$ bills to pay change.
• So, we only need to keep track of the 5$ & 10$ bills we have received till the current customer.

✅ Intuition - Algorithm - Working :
1. Initialize two variables with zero (since we don't have any change in hand at first) to keep track of 5$ & 10$ bills. 
  i.e., count5 = 0, count10 = 0.
2. Now, for each customer, assume the customer provides 'x'$ worth :
    • If x = 5$ : No need to provide change. Increment count of 5$ bills.
        count5++
    • If x = 10$ : We need to provide 5$ change. Check if it is possible. If yes, do the necessary things.
        - If count5 != 0 : increment count10 & decrement count5. :- count10++, count5--
        - Else → Not possible to provide change → return false
    • If x = 20$ : We either provide 10$ + 5$ or 5$ + 5$ + 5$.
        - If count5 != 0 : (only then we can provide either of the change)
            • If count10 != 0 : we provide 10$ + 5$ change. So, do count10--, count5--.
            • Else if count5 >= 3 :  (we couldn't provide 10$ + 5$ so now check provide 5$ + 5$ + 5$). do, count5 = count5 - 3.
            • Else : return false (as we couldn't provide any change)
3. Return true (since the loop will terminate naturally only when change providing is possible).
*/
bool lemonadeChange(vector<int>& bills) {
    int count5 = 0, count10 = 0;
    for (int bill : bills) {
        if (bill == 5) count5++;
        // Forr 10$ bill, provide 5$ change
        else if (bill == 10) {
            if (count5 != 0) {
                count5--;           // 5$ bill is given out as change
                count10++;          // 10$ bill is received from customer
            }
            // Unable to provide change because 5$ count is 0.
            else return false;
        }
        // For 20$ bill, change could be 10$ + 5$, or 5$ + 5$ + 5$.
        // If we have 10$ bills, we will try to get rid of them first by giving them out as changes
        else {
            if (count5 != 0) {
                if (count10 != 0) {
                    count10--; count5--;
                }
                else if (count5 >= 3) {
                    count5 -= 3;
                }
                // Unable to provide change because 10$ count is 0 and 5$ count is less than 3.
                else return false;
            }
            // Unable to provide either of the change because 5$ count is 0.
            else return false;
        }
    }
    return true;
}

int main() {
    return 0;
}