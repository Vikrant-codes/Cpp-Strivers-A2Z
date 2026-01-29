/*
Leetcode - 476. Number Complement

The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's 
in its binary representation.

For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
Given an integer num, return its complement.

Examples :-

Input: num = 5 __ Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.

Input: num = 1 __ Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.

Constraints :-
- 1 <= num < 2^31
*/

#include <bits/stdc++.h>
using namespace std;

// Bit Manipulation Method : Time Complexity : O(1) __ Space Complexity : O(1)
/*
Basic Intuition that anyone would come up with is to use the bitwise NOT operator (~)to complement a number 
by flipping its bits, but, this won't work.

Ex- consider the num '5' whose binary representation is '101'. 
The compliment of this number should be '010' which is 2, but
when we compute bitwise NOT of 5 i.e. (~ 5), we get '-6', i.e., bitwise NOT of 5 = ~5 = -6.
This is because integer numbers are stored in 4 bytes which is 32 bits.
So, binary representation of 5 = 0000......101   (total 32 bits out of which only last 3 bits represent the number 5)
Now when we do bitwise NOT, it flips all the 32 bits and not just the 3 bits that actually represents the number.
So, NOT (5) = ~5 = ~ (0000......101) = 1111......010.
This is a negative number (since its first bit (sign bit) is 1).
We can get the corresponding number for this binary representation by doing 2's compliment of it.
(Because -ve numbers are represented in 2's compliment & we can get the no. again by doing 2's compliment of the representation)
Now 2's compliment of (1111......010) is -6. (Thus, 1111......010 represents -6).
This is why when we do ~5 we get -6 instead of 2.

>> Now, how to get the actual compliment
To get the actual compliment we must first know how many bits does the number actually uses (like 5 has 3 bits, 8 has 4 bits)
The no. of bits for a number 'num' can be calculated by doing log2(num) + 1. 
Let this no of bits be 'noBits'

Now, that we know how many bits the number have, we can now try to get the compliment.
To get the compliment, we firstly need to create a mask that will filter out only the necessary bits.
Here, we created the mask which contains all 1s for the same no of bits as the num.
Ex- for 5 -> 101, the mask will be 111 which is 7. For 9 -> 1001, the mask would be 1111 which is 15.
We can get this mask by finding power (2, no. of bits) and subtracting 1.
Ex- for 5, the no of bits was 3 and 2 ^ 3 = 8, the mask is 2 ^ 3 - 1 = 7.
so mask = pow(2, noBits) - 1.

Now, to get the compliment, we simply return XOR of mask and num. 
This works because 
• all the non-significant bits (the 0s to the left in binary representation) remains 0 after XOR (since 0 ^ 0 = 0) 
• the 1 bits of the number flips to 0 after XOR with the 1 bits of mask (since 1 ^ 1 = 0)
• the 0 bits of the number flips to 1 after XOR with the 1 bits of mask (since 0 ^ 1 = 1)
In this way, only the required bits are flipped and we get the actual compliment.

num = 5  → 0000......101
mask = 7 → 0000......111
------------------------
XOR :      0000......010 → 2
*/
int findComplement(int num) {
    int noBits = (int) log2(num) + 1;
    int mask = pow(2, noBits) - 1;
    return mask ^ num;
}

// There is another way to get the mask without using log2 function or power function.
// If we knew the no of bits, we could get the mask by : int mask = (1 << noBits) - 1;
// Below code calculates mask & then returns compliment without using log2 or pow function
int findComplement2(int num) {
    int mask = 0;
    int temp = num;

    while (temp) {
        mask = (mask << 1) | 1;
        temp >>= 1;
    }

    return mask ^ num;
}

// Further ways 
// the compliment of number 'num' can also be get as (~num) & mask.
// This is because doing & with mask again flips the accidentally flipped bits and we get correct ans.

int main() {

    return 0;
}