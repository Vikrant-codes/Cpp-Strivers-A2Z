/*
Leetcode - 258. Add Digits : Easy

Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.

Examples :-

Input: num = 38 __ Output: 2
Explanation: The process is
38 --> 3 + 8 --> 11
11 --> 1 + 1 --> 2 
Since 2 has only one digit, return it.

Input: num = 0 __ Output: 0

Constraints :-
• 0 <= num <= 2^31 - 1

Follow up: Could you do it without any loop/recursion in O(1) runtime?
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Simulation Based Approach) : Time Complexity : O( log10 (​n) ) __ Space Complexity : O(1)
/*
Approach :- 
1. We simulate the process of adding the digits until we get a single digit.
2. Firstly add the digits of the number. 
3. If this sum is a single digit number, return it.
4. If not, repeat the process by considering this sum as the new value of num till we get a single digit result.

>> Complexity Analysis

-> sumOfDigits(n): 
|    while (n) {
|        sum += n % 10;
|        n /= 10;
|    }

Finding sum of digits of a number `n` takes O(d) time, 
where d is the count of digits, precisely d = O(log10(n)) + 1.
Thus, sumOfDigits(n) takes O(log n)

-> addDigits():
|    while (num > 9) {
|        num = sumOfDigits(num);
|    }

The important observation is that after summing the digits, num becomes much smaller.
For example:
999999999
   ↓
   81
   ↓
   9

So there are only a few iterations relative to the number of digits. 
More formally, the total work is dominated by the first digit-sum operation.

Therefore:
Time:  O(log n)
Space: O(1), for the iterative solution.
*/

// helper method
int sumOfDigits(int n) {
    int sum = 0;
    
    while (n) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

// Recursive Implementation for Simulation Approach: Time Complexity : O(log n) __ Space Complexity : O(log log n)
/*
>> Space Complexity Analysis [Recursive Stack Space]

Each call to addDigits() stays on the call stack until the recursive call returns.

For example:
    addDigits(999999999)
        ↓
    addDigits(81)
        ↓
    addDigits(9)
        ↓
    return 9

For a general n, the number of recursive calls is actually O(log log n), 
because each sumOfDigits() reduces the number from roughly n to at most 9 × number_of_digits.

So, more precisely:
- sumOfDigits() → O(log n) time, O(1) space
- addDigits() recursion depth → O(log log n)

Overall space complexity → O(log log n)
*/
int addDigits(int num) {
    if (num < 10) 
        return num;
    
    num = sumOfDigits(num);

    return addDigits(num);
}

int main() {
    return 0;
}