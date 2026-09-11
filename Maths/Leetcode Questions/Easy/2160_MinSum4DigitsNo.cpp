/*
Leetcode - 2160. Minimum Sum of Four Digit Number After Splitting Digits : Easy

You are given a positive integer num consisting of exactly four digits. Split num into two new integers new1 and new2 by using the digits
found in num. Leading zeros are allowed in new1 and new2, and all the digits found in num must be used.

For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the possible pairs [new1, new2] are
[22, 93], [23, 92], [223, 9] and [2, 329].
Return the minimum possible sum of new1 and new2.

Examples :-
Input: num = 2932 __ Output: 52
Explanation: Some possible pairs [new1, new2] are [29, 23], [223, 9], etc.
The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.

Input: num = 4009 __ Output: 13
Explanation: Some possible pairs [new1, new2] are [0, 49], [490, 0], etc.
The minimum sum can be obtained by the pair [4, 9]: 4 + 9 = 13.

Constraints : 1000 <= num <= 9999
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach :-
1. Extract digits (digits.push_back(num % 10)).
2. Sort digits in ascending order.
3. Build numbers as:
-- n1 = digits[0]*10 + digits[3]
-- n2 = digits[1]*10 + digits[2]
4. Return n1 + n2.

To minimize the sum, distribute small digits evenly across the two numbers.
By sorting and pairing smallest with largest, second smallest with second largest, we balance the values.
*/
int minimumSum(int num) {
    vector<int> digits;
    while (num != 0) {
        int digit = num % 10;
        digits.push_back(digit);
        num = num / 10;
    }

    sort(digits.begin(), digits.end());
    int n1 = digits[0] * 10 + digits[3];
    int n2 = digits[1] * 10 + digits[2];
    return n1 + n2;
}

int main()
{

    return 0;
}