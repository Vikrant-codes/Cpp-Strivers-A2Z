/*
Leetcode - 2894. Divisible and Non-divisible Sums Difference : Easy

You are given positive integers n and m.
Define two integers as follows:
• num1: The sum of all integers in the range [1, n] (both inclusive) that are not divisible by m.
• num2: The sum of all integers in the range [1, n] (both inclusive) that are divisible by m.
Return the integer num1 - num2.

Examples :-

Input: n = 10, m = 3 __ Output: 19
Explanation: In the given example:
- Integers in the range [1, 10] that are not divisible by 3 are [1,2,4,5,7,8,10], num1 is the sum of those integers = 37.
- Integers in the range [1, 10] that are divisible by 3 are [3,6,9], num2 is the sum of those integers = 18.
We return 37 - 18 = 19 as the answer.

Input: n = 5, m = 6 __ Output: 15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 6 are [1,2,3,4,5], num1 is the sum of those integers = 15.
- Integers in the range [1, 5] that are divisible by 6 are [], num2 is the sum of those integers = 0.
We return 15 - 0 = 15 as the answer.

Input: n = 5, m = 1 __ Output: -15
Explanation: In the given example:
- Integers in the range [1, 5] that are not divisible by 1 are [], num1 is the sum of those integers = 0.
- Integers in the range [1, 5] that are divisible by 1 are [1,2,3,4,5], num2 is the sum of those integers = 15.
We return 0 - 15 = -15 as the answer.

Constraints :- 1 <= n, m <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :- 
Initialize two variables num1 = 0, num2 = 0.
loop through the range [1, n] and check whether the integer is divisble by m or not.
If not divisible, add it to num1. Else num2
Return num 1 - num 2 after the loop ends. 

In case (m > n) :- 
all the integers in the range [1, n] would be non-divisible since m > n. So, num2 will remain 0.
and in this case num1 will have the sum of all integers in the range [1, n] which is n * (n + 1) / 2.
*/
int differenceOfSumsBrute(int n, int m) {
    if (m > n) 
        return (n * (n + 1))/2 ;
    int num1 = 0, num2 = 0;
    for (int i=1; i<=n; i++) {
        if (i % m != 0) num1 += i;
        else num2 += i;
    }
    return num1 - num2;
}

// Optimal Approach : Time Complexity : O(1) __ Space Complexity : O(1)
/*
✅ Optimal O(1) Approach — Intuition
🔍 Goal :-
We want: (num1) – (num2)
where,
num1 = sum of numbers NOT divisible by m
num2 = sum of numbers divisible by m

Now, assume we know that in the range [1,n], total 'd' integers are divisible by m.
In that case the integers would be like :- m, 2m, 3m, 4m, ...., d*m. 
Now, num2 = sum of divisible = m + 2m + 3m + 4m + ... + d*m 
=> m * (1 + 2 + 3 + .. + d) = m * d * (d+1) / 2.     [using integer sum formula]
so, num2 = m * d * (d+1) / 2. 
Now, we can find this d easily using n/m. Since for the range [1,n], n/m tells us how many integers are divisble by m.

Also, num1 = sum of numbers NOT divisible by m = sum of all integers in range [1, n] - sum of numbers divisible by m.
Thus, num1 = sum of all integers in range [1, n] - num2 = n * (n + 1) / 2 - num2.           [using integer sum formula]
So, num1 - num2 = (n * (n + 1) / 2 - num2) - num2 = n * (n + 1) / 2 - 2 * num2.
This gives us:- num1 - num2 = n * (n + 1) / 2 - 2 * m * d * (d+1) / 2           [substituting value of num2]
=> num1 - num2 = n * (n + 1) / 2 - m * d * (d+1).

Algorithm :-
1. Calculate d i.e. the count of numbers divisible by m in the range [1, n] using d = n / m.
2. We derived that num1 - num2 = n * (n + 1) / 2 - m * d * (d+1). So,
3. Let x = n * (n + 1) / 2
4. Let y = m * d * (d+1)
5. Return x - y as the answer.
*/
int differenceOfSums(int n, int m) {
    int d = n/m;
    int x = (n*(n+1))/2;
    int y = m*d*(d+1);
    return x - y;
}

int main() {
    return 0;
}