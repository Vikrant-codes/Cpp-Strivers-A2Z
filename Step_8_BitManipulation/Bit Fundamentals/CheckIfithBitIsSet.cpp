/*
TUF - 730. Check if the i-th bit is Set or Not

Given two integers n and i, return true if the ith bit in the binary representation of n 
(counting from the least significant bit, 0-indexed) is set (i.e., equal to 1). 
Otherwise, return false.

Examples :-

Input: n = 5, i = 0
Output: true
Explanation: Binary representation of 5 is 101. The 0-th bit from LSB is set (1).

Input: n = 10, i = 1
Output: true
Explanation: Binary representation of 10 is 1010. The 1-st bit from LSB is set (1).

Constraints :-
• 1 <= n <= 10^9
• 0 <= i <= 31
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(log₂ n) __ Space Complexity : O(log₂ n)
/*
First, convert the number into its binary representation.
To check the i-th bit (using 0-based indexing from the right), access str[len - 1 - i]. 
If the index exceeds the binary representation's length, the bit is considered unset, so return false.

>> Complexity Analysis:
-> Time: O(log₂ n)
Converting to binary takes O(log₂ n), and reversing the string takes O(log₂ n). Checking the bit takes O(1).

-> Space: O(log₂ n) — The binary string stores O(log₂ n) bits.
*/
string convert2Binary(int n) {
    string str = "";

    while (n) {
        if (n % 2 == 1) str += '1';
        else str += '0';
        n /= 2;
    }

    reverse(str.begin(), str.end());
    return str;
}

bool checkIthBitNaive(int n, int i) {
    string str = convert2Binary(n);

    int len = str.size();

    if (i >= len) return false;

    return (str[len - 1 - i] == '1') ? true : false;
}

// Better Approach: Time Complexity : O(log₂ n) __ Space Complexity : O(1)
/*
We can simulate the binary conversion process and check the i-th bit during the conversion itself, 
without storing the entire binary representation.

Since binary conversion processes bits from right to left, we start with k = 0, representing the rightmost bit.
- At each step, extract the rightmost bit of n to determine whether it is set or unset.
- If k == i, we have reached the required bit, so return true/false considering whether the bit is set or not.
- Otherwise, increment k and divide n by 2 to remove the rightmost bit and move to the next bit position.
- If n becomes 0 before reaching the required position, the remaining higher bits are all zero, so the i-th bit is unset.

>> Complexity Analysis:
-> Time: O(log₂ n) — Each division by 2 removes one bit, requiring at most O(log₂ n) iterations.
-> Space: O(1) — Only a counter is used; no binary string is stored.
*/
bool checkIthBitBetter(int n, int i) {
    int k = 0;

    while (n) {
        if (k == i) 
            return (n % 2);     // return (n & 1);

        k++;
        n /= 2;                 // n >>= 1;
    }

    return false;
}

// Optimal Approach: Time Complexity : O(1) __ Space Complexity : O(1)

// Using left shift -- Bitmasking (Left Shift and AND)
/*
Bitmasking (Left Shift and AND)

Instead of processing the bits one by one, we can directly check the required bit using bitmasking.
- Start with 1 (binary ...0001) and left-shift it by i positions. 
  This creates a bitmask with only the i-th bit set.
- Perform a bitwise AND (&) between n and the bitmask. 
  The result will be non-zero if the i-th bit of n is set; otherwise, it will be zero.

Note: This assumes i is a valid shift amount and the operation 1 << i does not cause signed integer overflow.
*/
bool checkIthBit1(int n, int i) {
    int num = 1 << i;

    return n & num;
}

// Using right shift
/*
Instead of creating a bitmask, we can shift the required bit directly to the rightmost position and check it.
- Right-shift n by i positions so that the i-th bit becomes the rightmost bit.
- Use bitwise AND with 1 to isolate the rightmost bit. The result tells us whether the required bit is set or unset.
*/
bool checkIthBit2(int n, int i) {
    int num = n >> i;

    return num & 1;
}

int main() {
    return 0;
}