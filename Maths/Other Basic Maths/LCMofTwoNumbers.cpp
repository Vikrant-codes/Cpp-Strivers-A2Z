/*
LCM of two numbers

You are given two integers n1 and n2. 
You need find the Lowest Common Multiple (LCM) of the two given numbers. 
Return the LCM of the two numbers.

The Lowest Common Multiple (LCM) of two integers is the lowest positive integer that is divisible by both the integers.

Examples :-

Input: n1 = 4, n2 = 6
Output: 12
Explanation: 4 * 3 = 12, 6 * 2 = 12.
12 is the lowest integer that is divisible both 4 and 6.

Input: n1 = 3, n2 = 5
Output: 15
Explanation: 3 * 5 = 15, 5 * 3 = 15.
15 is the lowest integer that is divisible both 3 and 5.

Constraints :-
• 1 <= n1, n2 <= 1000
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(n1 * n2) __ Space Complexity : O(1)
/*
We know that the number `n1 * n2` is a multiple of both n1 and n2.
So, the naive approach could be to search in the range [1, n1 * n2] 
and return the first number which is divisible by both n1 & n2 (i.e., the number is a multiple of both).
*/
int LCM1(int n1,int n2) {
    for (int i = 1; i <= n1 * n2; i++)
        if (i % n1 == 0 && i % n2 == 0)
            return i;

    return -1;
}

// Optimized Naive Approach: Time Complexity : O( (n1 * n2) - max(n1, n2) ) __ Space Complexity : O(1)
/*
We can slightly optimize the search by starting the search from max(n1, n2).
This can be done since we know that LCM >= max(n1, n2).
Thus, the search space can be [ max(n1, n2), n1 * n2 ], and we can search each number in this range, 
and return the first number which is divisible by both n1 and n2.

The time complexity for this solution will be O( (n1 * n2) - max(n1, n2) )
*/
int LCM2(int n1,int n2) {
    int num = max(n1, n2);

    while (true) {
        if (num % n1 == 0 && num % n2 == 0)
            return num;
        num++;
    }

    return -1;  // dummy return
}

// Better Approach: Time Complexity : O(min(n1, n2)) __ Space Complexity : O(1)
/*
Instead of checking for all numbers in range [ max(n1, n2), n1 * n2], 
we can simply check the multiples of n1 or n2 only.

Assume we traverse the multiples of n1, then we can return the first multiple of n1 which is divisible by n2 as well.
Similarly, if we traverse the multiples of n2, then we can return the first multiple of n2 which is divisible by n1 also.

The best choice would be to traverse the multiples of the bigger number, since doing so will get the LCM in lesser iterations.

So, we pick the bigger number, explore its multiples and return the first multiple which is divisible by the smaller number.

This will help us get the LCM in O(min(n1, n2)) time,
since if we start checking the multiples of the bigger number (i.e., max(n1, n2)), even in the worst case
we can reach (n1 * n2) in min(n1, n2) iterations.
*/
int LCM3(int n1,int n2) {
    // we assume that n2 >= n1, so if n1 > n2, swap the values (or call LCM method with swapped values)
    if (n1 > n2)
        return LCM3(n2, n1);

    // check the multiples of the larger number, return the first multiple which is divisible by the smaller number
    int mul = n2;
    
    while (mul % n1 != 0) {
        mul += n2;
    }
    
    return mul;
}

// Same approach, implementation using for loop
int LCM4(int n1,int n2) {
    // we assume that n2 >= n1, so if n1 > n2, swap the values (or call LCM method with swapped values)
    if (n1 > n2)
        return LCM4(n2, n1);

    // check the multiples of the larger number, return the first multiple which is divisible by the smaller number

    // we can also use the loop valid condition as `i <= n1 * n2`
    for (int i = n2; ; i += n2)
        if (i % n1 == 0) 
            return i;
    
    return -1;      // dummy return
}

// we can also directly work with max(n1, n2) and min(n1, n2)
int LCM5(int n1,int n2) {
    int a = min(n1, n2);
    int b = max(n1, n2);

    int mul = b;
    while (mul % a != 0) 
        mul += b;
    
    return mul;
}

// Optimal Approach : Time Complexity : O( log Φ (min(n1, n2)) ) __ Space Complexity : O(1)
/*
There's this mathematical identity: For two numbers a & b, LCM(a, b) * GCD(a, b) = a * b.
This gives us: LCM(a, b) = (a * b) / GCD(a, b)

GCD can be found efficiently using Euclidean Algorithm, which takes O( log Φ (min(a, b)) ) time.
Thus, LCM can then also be found essentially in the same time, since we just have to do O(1) work on GCD to get LCM.
*/

int GCD(int n1, int n2) {

    while (n2 % n1 != 0) {
        int rem = n2 % n1;
        n2 = n1;
        n1 = rem;
    }

    return n1;
}

int LCM(int n1,int n2) {
    
    return (n1 * n2) / GCD(n1, n2);
}

int main() {
    return 0;
}