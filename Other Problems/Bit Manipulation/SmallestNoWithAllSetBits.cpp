/*
Leetcode - 3370. Smallest Number With All Set Bits

You are given a positive number n.
Return the smallest number x greater than or equal to n, such that the binary representation of x contains only set bits.

Examples :-

Input: n = 5 __ Output: 7
Explanation: The binary representation of 7 is "111".

Input: n = 10 __ Output: 15
Explanation: The binary representation of 15 is "1111".

Input: n = 3 __ Output: 3
Explanation: The binary representation of 3 is "11".

Constraints :- 1 <= n <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// For all approaches :- Time Complexity : O(1) __ Space Complexity : O(1)

/*
We need to find the smallest number 'x' (>= n) such that the binary representation of x contains only set bits i.e. 1s.
Given the constraints :- 1<=n<=1000 we know that the powers of two are 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024.
And the integers which contain only set bits are power_of_2 - 1 i.e. 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023.
So, we run a for loop 10 times(since 2 ^ 10 = 1024 and 1023 is the largest number that contain all set bits for the given range)
We do maintain a power of 2 and check if current no. is power_of_2 - 1 or, power_of_2 is n + 1. In that case return n.
Ex- for n = 3 we see 4 = 3+1 so return 3, for n = 63, we see 64 = 63+1 so return 63

In case power of 2 is not n + 1 but has exceeded n so we return power_of_n - 1 because this value is the next all set int.
*/
int smallestNumber1(int n) {
    if (n == 1) return n;
    int mul = 1;
    for (int i=1; i<11; i++) {
        mul *= 2;
        if (mul == n+1) return n;
        else if (mul > n) return mul-1;
    }
    return -1;
}

/*
🔹 Problem goal :- We want the smallest number with all bits set to 1 that is greater than or equal to n.
Numbers with all bits set look like this: 1 (1), 3 (11), 7 (111), 15 (1111), 31 (11111), ...
Each of them has the form: 2^k - 1
🔹 Now, think in binary
Let’s say n = 5 → 101 :- The next number with all 1s and having at least as many bits as 5 is 111 (which is 7).

Algorithm :-
🔹 Step 1: Find how many bits are needed
We want to know how many bits k are needed to represent a number ≥ n that looks like all 1s (111...111).
If you take n + 1, then: n = 5 (101) → n+1 = 6 (110)
log2(6) ≈ 2.58 → ceil(2.58) = 3 → means we need 3 bits to represent numbers up to 5.
So, k = ceil(log2(n + 1)) gives us the minimum number of bits needed.
🔹 Step 2: Make all those bits 1
A number with k bits all set to 1 is: 2^k - 1
So:
For k = 3 → 2^3 - 1 = 7 → binary 111
For k = 4 → 2^4 - 1 = 15 → binary 1111
🔹 Step 3: Combine both steps
int k = ceil(log2(n + 1));
return pow(2, k) - 1;

🔹This works because:
- log2(n + 1) finds the minimum number of bits needed.
- pow(2, k) - 1 creates a number where all those bits are 1.

Think it like this :-
k = ceil(log2(n+1)) will help us get next greater power of two which can be calculated as 2 ^ k.
So return 2 ^ k - 1.
*/
int smallestNumber2(int n) {
    int k = ceil(log2(n+1));
    return pow(2, k) - 1;
}

/*
pow(2, k) is equivalent as 1 << k.
As we know right shifting a number once multiplies that number by 2.
So, is we right shift 1 'k' times it actually means multiplying 1 by 2 k times i.e. doing 2 ^ k
So we can do pow(2, k) by doing 1 << k (1 right shift k times)
*/
int smallestNumber3(int n) {
    int k = ceil(log2(n+1));
    return (1 << k) - 1;
}

/*
We want to find the smallest number (>= n) such that the number has only set bits. 
Assume we have n = 5, in binary 5 is 101, the next all set number is 111 (i.e. 7) 
now, if we see 111 and 101 we observe that 111 is actually 101 + ~(101), where '~' represents bitwise not.
Take few more examples like n = 61. In binary its 111101. The answer should be 111111 (i.e. 63)
Now ~63 is 000010 which is 2, adding 111101 (61) + 000010 (2) = 111111 (63)

So, we see that the answer should be n + ~n, but if we directly return it, it gives unexpected results. 

That is because in C++ the ~ operator flips all the bits of the integer, not just the bits representing n. 
For a 32-bit signed integer, ~n flips all 32 bits, including the higher-order bits and the sign bit. 
This causes the result to become a negative number or include extra bits you don’t want. 
For example, ~5 is not 010 as you might expect from looking at just 3 bits—
it’s actually 11111111111111111111111111111010 in 32-bit signed representation, which is -6 in decimal. 
Adding this directly to n clearly does not produce the intended “all bits set” number.

To fix this, we mask the flipped number so that we only consider the bits that correspond to the original number n. 
First, we calculate the number of bits in n using floor(log2(n)) + 1, which gives the position of the highest set bit plus one.
(n bits can represent upto 2^n - 1. So, for a number x we can get no of bits as ceil(log2(x+1)) or floor(log2(n)) + 1.) 
Then we create a mask with all those bits set to 1 using (1 << bits) - 1. 
Finally, we AND the bitwise NOT of n with this mask: not_n = (~n) & ((1 << bits) - 1);
This ensures that only the relevant bits are flipped, ignoring the higher-order bits that would cause incorrect results. 
Now, when we add n + not_n, we get a number where all bits in the width of n are set to 1, 
which is exactly the smallest number greater than or equal to n with all set bits.
*/
int smallestNumber4(int n) {
    int bits = floor(log2(n)) + 1;      // equivalent to ceil( log2 (n+1) ).
    int not_n = (~n) & ((1 << bits) - 1);       // mask with appropriate all set number ((1 << bits) -1) to find not n.
    return n + not_n;
}
/*Solution 4 is not actually very good for implementation since we see during masking that we need 1<<bits - 1 to get 
the next all 1 set number to mask and get the not. this 1<<bits-1 is the answer itself. So, in a way this solution 
uses the answer to get the answer itself.*/

int main() {
    return 0;
}