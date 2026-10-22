// Turn off the rightmost set bit

#include<bits/stdc++.h>
using namespace std;

// Niave Approach: Time Complexity : O(3 log₂ n) __ Space Complexity : O(log₂ n)
/*
Get the binary representation string of n.
Toggle the rightmost set bit in this binary string. (Turn off the rightmost set bit)
Return the integer corresponding to this updated string.

>> Complexity Analysis

-> Time Complexity
- getting the binary representation (convert2Binary): O(log₂ n)
- Unsetting the rightmost set bit (reach the rightmost set bit, then unset it): O(k) ~ O(log₂ n)
  ,where k = position of the rightmost set bit from the right end. 
  (In worst case, it can be equal to size of binary string, which is log₂n)
- convert2Decimal takes O(len) time, where len = size of binary string, which is O(log₂ n) again.

Total time: O(log₂ n) + O(log₂ n) + O(log₂ n) = O(3 log₂ n)

-> Space Complexity
We are using a string to store the binary representation of n, which takes O(log₂ n) space.
*/

string convert2Binary(int n) {
    string res = "";
    while (n != 0) {
        if (n & 1) res += '1';  
        else res += '0';
        n = n >> 1;
    }
    reverse(res.begin(), res.end());
    return res;
}

int convert2Decimal(string& binary) {
    int n = binary.size();
    int num = 0;
    int multiplier = 1;         // initial multiplier is 2^0, which is 1.
    for (int i = n - 1; i >= 0; i--) {
        if (binary[i] == '1')
            num = num + multiplier;
        multiplier *= 2;
    }
    return num;
}

int unsetLastSetBitNaive(int n) {
    if (n == 0) return 0;       // nothing to unset, no set bit in 0

    string s = convert2Binary(n);

    int i = s.size() - 1;
    while (s[i] == '0') i--;    // reach the last set bit
    s[i] = '0';                 // unset the last set bit

    return convert2Decimal(s);
}

// Better Approach: Time Complexity : O(log₂ n) __ Space Complexity : O(1)
/*
>> Unset the Rightmost Set Bit Using Bitwise Operations

The idea is to unset the rightmost set bit of a given number 
by first identifying its position using bitwise operations. 

We traverse the bits from right to left using right shift (>>) until we encounter the first set bit (1), 
which gives the position of the rightmost set bit. 
Once this position is found, we create a mask using (1 << pos) that has only that bit set. 
Then, we apply XOR of the bit-mask with the original number, which flips that bit from 1 to 0. 
This effectively unsets the rightmost set bit of the number.
*/
int unsetLastSetBit_Bitmask(int n) {
    if (n == 0)
        return 0;

    // Find the position of the rightmost set bit
    int pos = 0;
    while (((n >> pos) & 1) == 0) {
        pos++;
    }

    // Unset the rightmost set bit
    n = n ^ (1 << pos);
  
    return n;
}

// Optimal Approach-1 (Brian Kernighan’s Method): Time Complexity : O(1) __ Space Complexity : O(1)
/*
First, observe what happens when we subtract 1 from n: the rightmost set bit (1) becomes 0, 
and all the bits to its right become 1.

Now, if we perform a bitwise AND (&) between n and n - 1, the rightmost set bit becomes 0, 
while all the bits to its right become 0 as well (because the corresponding bits in n are already 0). 
All the bits to the left remain unchanged.

Therefore, n & (n - 1) unsets the rightmost set bit of n, leaving all the other bits unchanged.
*/
int unsetLastSetBit(int n) {
    return n & (n - 1);
}

// Optimal Approach-2 (Using 2’s Complement): Time Complexity : O(1) __ Space Complexity : O(1)
/*
The idea is to find the rightmost set bit using a property of 2's complement arithmetic. 
When we perform n & (~n + 1) or equivalently n & (-n), we get a number with only the rightmost set bit of n.

By subtracting this value from n, we can unset the rightmost set bit.
*/
int unsetLastSetBit2(int n) {
    return n - (n & (-n));
}

int main() {
    cout << unsetLastSetBit(7) << endl;
    cout << unsetLastSetBit(12) << endl;
    cout << unsetLastSetBit(0) << endl;

    return 0;
}