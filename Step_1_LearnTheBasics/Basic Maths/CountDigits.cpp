// GFG - Count Digits in a Number 
// TUF - 781. Count all Digits of a Number

#include<bits/stdc++.h>
#include<cmath>         // for log10 function
using namespace std;

/*
GFG - Count Digits in a Number : Easy

Given a number n, return the count of digits in this number.

Examples :-

Input: n = 1567 __ Output: 4
Explanation: There are 4 digits in 1567, which are 1, 5, 6 and 7.

Input: n = 99999 __ Output: 5
Explanation: Number of digit in 99999 is 5

Constraints :- 
• 1 ≤ n ≤ 10^9
*/

// Standard Approach :- Time Complexity : O(log10(n)) 
/*
>> Approach
The last digit of a number can be extract by doing n % 10.
We can then update the number itself by removing its last digit using n = n / 10.
We can do so till n does not becomes zero.
We can count the no. of times the loop ran, and this count will give us the count of digits.

Although, if n was 0 itself, we had need to handle this case explicitly.

Complexity Analysis :-
We are dividing by 10 in each iteration, and loops ends when n becomes 0. 
Thus, the total number of iterations done before n becomes 0 
is equal to count of times n can be divided by 10 before it becomes 0.

Let n = 10 ^ k, then n can be divided by 10, exactly k times before it becomes 0.
So, the number of iterations is proportional to k, which is log10(n).   (since n = 10^k => log10(n) = k)

Therefore, the time complexity of this approach is O(log10(n)).
*/
int countDigits(int n) {
    int cnt = 0;
        
    while (n > 0) {
        n /= 10;     // same as n = n/10
        cnt++;
    }
    
    return cnt;
}

// Optimized Approach :- Time Complexity : O(1)
/*
It is a mathematical fact that the number of digits in a positive integer n is given by the formula: 
    digits = floor( log10(n) ) + 1

This works because log10(n) gives us the exponent k such that 10^k is the largest power of 10 less than or equal to n.

If we had been asked the count of bits/digits in binary representation of a number, 
then it would have been log2(n) + 1.

Similarly, for octal representation, the count of digits is log8(n) + 1.
*/
int cntDigits(int n) {
    int cnt = (int) (log10(n) + 1);
    return cnt;
}

/*
TUF - 781. Count all Digits of a Number

You are given an integer n. You need to return the number of digits in the number.

The number will have no leading zeroes, except when the number is 0 itself.

Example :-

Input: n = 4 __ Output: 1
Explanation: There is only 1 digit in 4.

Input: n = 14 __ Output: 2
Explanation: There are 2 digits in 14.

Input: n = 234 __ Output: 3

Constraints :-
• 0 <= n <= 5000
• n will contain no leading zeroes except when it is 0 itself.
*/

// we need to explicitly handle the n = 0 case, and return 1 when n equals 0.
int countDigit(int n) {
    if (n == 0) return 1;

    return log10(n) + 1;
}

int main() {
    return 0;
}