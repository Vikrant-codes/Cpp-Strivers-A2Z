/*
Leetcode - 762. Prime Number of Set Bits in Binary Representation : Easy

Given two integers left and right, return the count of numbers in the inclusive range [left, right] 
having a prime number of set bits in their binary representation.

Recall that the number of set bits an integer has is the number of 1's present when written in binary.
- For example, 21 written in binary is 10101, which has 3 set bits.

Examples :-

Input: left = 6, right = 10
Output: 4
Explanation:
6  -> 110 (2 set bits, 2 is prime)
7  -> 111 (3 set bits, 3 is prime)
8  -> 1000 (1 set bit, 1 is not prime)
9  -> 1001 (2 set bits, 2 is prime)
10 -> 1010 (2 set bits, 2 is prime)
4 numbers have a prime number of set bits.

Input: left = 10, right = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
5 numbers have a prime number of set bits.

Constraints :-
• 1 <= left <= right <= 10^6
• 0 <= right - left <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// My Approach : Time Complexity : O(n * 20) ~ O(n) __ Space Complexity : O(1)
/*
Approach :-
We want the count of all those numbers which have prime no. of 1 bits (set bits) in their binary representation.
We can manually count the set bits of a number by 
    repeatedly extracting the last bit (using num & 1) and then right shifting the number (num = num >> 1).
We can use a counter variable to count the 1 bits for the number
Now, we need to check whether this count of set bits is prime or not.
According to the constraints, the maximum value of the number can be 10^6 (which is 1,000,000)
Now, if we represent 10^6 in binary, it can be represented using 20 bits only (since 2^19 = 524288 and 2^20 = 1048576).
So, the numbers we are dealing with can have at most 20 bits in their binary representation.
Even if all these bits were set to 1 for a certain number, the maximum no. of set bits can be 20.
Thus, the count of set bits will not exceed 20 according to the given constraints. 
Now, we need to check whether the count of set bits is prime or not 
    and since this count can be at most 20, we don't need to use an explicit funtion to check whether this count is prime or not.
The primes upto 20 are = {2, 3, 5, 7, 11, 13, 17, 19}.
We store them in a set (or other useful data structure).
Now, to check whether the count of set bits for a certain number is prime or not, 
    we can do so by checking for its existence in the set (existence check in set is easy using count function)

Key Observations (Clean Structure)
- We iterate from left to right.
- For each number:
    - Count set bits using:
        num & 1
        num >>= 1
- The count of set bits is at most 20, because:
    10^6 < 2^20
    So any number ≤ 10^6 needs at most 20 bits.
- Therefore, maximum possible set bits = 20.
*/
int countPrimeSetBits(int left, int right) {
    set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};     // prime numbers upto 20
    int ans = 0;
    for (int i = left; i <= right; i++) {
        int temp = i;
        int cnt1bits = 0;            // count of set bits (1 bits) for the current number
        while (temp) {
            int last_bit = temp & 1;
            cnt1bits += last_bit;    // if last_bit is 1, cnt increases, else remains same (adding 0)
            temp >>= 1;              // right shift temp
        }
        // check if count of 1 bits for the current number is prime, if yes incremenet ans
        if (primes.count(cnt1bits)) ans++;
    }
    return ans;
}

// Because the domain is so small (0–20), even set<int> is slightly overkill. We could use a boolean array to check for prime
int countPrimeSetBits2(int left, int right) {
    bool isPrime[21] = {false};             
    // isPrime[i] tells whether the number 'i' is prime or not
    // initially all numbers are marked as non-primes (numbers are in range [0, 20] = 21 size)
    isPrime[2] = isPrime[3] = isPrime[5] = isPrime[7] = isPrime[11] = isPrime[13] = isPrime[17] = isPrime[19] = true;
    // marking the prime numbers as prime

    int ans = 0;
    for (int i = left; i <= right; i++) {
        int temp = i;
        int cnt1bits = 0;            // count of set bits (1 bits) for the current number
        while (temp) {
            int last_bit = temp & 1;
            cnt1bits += last_bit;    // if last_bit is 1, cnt increases, else remains same (adding 0)
            temp >>= 1;              // right shift temp
        }
        // check if count of 1 bits for the current number is prime, if yes incremenet ans
        if (isPrime[cnt1bits]) ans++;
    }
    return ans;
}

int main() {
    return 0;
}