/*
Leetcode - 190. Reverse Bits : Easy

Reverse bits of a given 32 bits signed integer.

Examples :-
Input: n = 43261596
Output: 964176192
Explanation:
--------------------------------------------------
|Integer	|   Binary                           |
|43261596	|   00000010100101000001111010011100 |
|964176192	|   00111001011110000010100101000000 |
--------------------------------------------------

Input: n = 2147483644
Output: 1073741822
Explanation:
--------------------------------------------------
|Integer	|   Binary                           |
|2147483644	|   01111111111111111111111111111100 |
|1073741822	|   00111111111111111111111111111110 |
--------------------------------------------------

Constraints :-
- 0 <= n <= 2^31 - 2
- n is even.

Follow up: If this function is called many times, how would you optimize it?
*/

#include <bits/stdc++.h>
using namespace std;

/*
We want to reverse the bits and we can do that by taking bits from the right side of n one by one
and building a new number from the left side (by inserting those extracted bits to some new number).
Ex- consider an example for 4 bit case (the code works on 32 bits)
number n = 1011, 
We extract its bits from the right side one by one. 
First extracted bit -- 1 -- rev = 1
Second extracted bit -- 1 -- rev = 11
Third extracted bit -- 0 -- rev = 110
Fourth exttracted bit -- 1 -- rev = 1101.
In this way, by extracting the bits from the right side of n one by one and 
repeatedly inserting them to the right of a rev number, we can get the reverse

It’s exactly like:
| Remove last digit from one number → Attach it to the end of another number.

Now, how to do this in code ? 

🧠 Step 1: Extract the Last Bit
    | int last_bit = n & 1;
Why does this work?
Binary fact: 
- 1 in binary = 000...0001
- AND operation keeps only the last bit
  Example - consider n = 5 (101), now 5 & 1 is 
    101
  & 001
    ----
    001  → 1
- If number is:
    - even → last bit = 0
    - odd → last bit = 1
- So: n & 1  →  gives LSB
We are literally plucking off the rightmost bit.

🧠 Step 2: Remove That Extracted Bit from n
| n = n >> 1;
Doing right shift removes the last bit. Example -> 101 → (after right shift) 10
We've now consumed that last bit.

🧠 Step 3: Insert the extracted bit at the end of Rev
Before inserting the extracted bit, we need to make an empty space for that bit in rev.
(a) Make Space in rev :- 
        | rev = rev << 1;
    - Doing left shift moves the bit to the left adding a zero at the end (creating empty space at the end of rev).
    - Example -> 101 → (after left shift) 1010
    - So, rev << 1 = "move everything left and open a slot"
(b) Insert Extracted Bit :- 
    - To insert the extracted bit, we need to replace the last bit of rev (empty slot bit) with the extracted bit.
    - Thus, if extracted bit is 1, we need to make the last bit of rev 1 else leave it 0.
    - This can be done using 'OR'
        | rev = (rev << 1) | last_bit;
    - Why OR works?
        Slot bit (last bit of rev is 0 due to left shift), so the 'OR' depends on the extracted bit only:
            If extracted_bit is 0: slot_bit OR extracted_bit = 0 | 0 = 0
            If extracted_bit is 1: slot_bit OR extracted_bit = 0 | 1 = 1
        So it cleanly inserts the bit.

By repeatedly doing these above steps 32 times, we can reverse the bits of the 32bit integer.
*/
int reverseBits(int n) {
    int rev = 0;
    for(int i = 0; i < 32; i++) {
        int last_bit = n & 1;
        n = n >> 1;
        rev = (rev << 1) | last_bit;
    }
    return rev;
}

// Why the constraint : n is even and Why n is less than INT_MAX (not equal)
/*
To understand why such constraint is given, we must understand what happens if n is odd.
If n were odd, its rightmost bit (LSB) is 1. Ex- 1 (1), 3 (11), 5 (101), 7 (111), 9 (1001), 11 (1011), ...
The 32 bit represntation of odd numbers is thus xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxx1. (where x is 0 or 1 depending on number).
Now, when this number is reversed, its LSB would become MSB, thus rev would look like 1xxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx.
But we are dealing with signed integers and we know that the MSB of signed integers is the sign bit.
So, having 1 as MSB would mean the reverse number is negative.
So, this problem applies this constraint (number being even) on input, so we don't get negative numbers as output.
also, due to this reason n is not equal to INT_MAX as INT_MAX is odd.
The problem could've also used unsigned integers instead of signed integers and all this problem would've never occurred.

🔹 So what does this constraint achieve?
It guarantees:
✅ The reversed result will not set the sign bit
✅ The returned int will never be negative
✅ Output stays within signed 32-bit positive range
*/

int main() {
    return 0;
}