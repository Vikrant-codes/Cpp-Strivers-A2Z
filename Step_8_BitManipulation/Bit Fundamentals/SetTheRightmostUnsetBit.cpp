/*
GFG - Set Rightmost Unset Bit

Given a non-negative number n. The problem is to set the rightmost unset bit in the binary representation of n.

Examples :-

Input: n = 6 __ Output: 7
Explanation: The binary representation of 6 is 110. After setting right most bit it becomes 111 which is 7.

Input: n = 15 __ Output: 31
Explanation: The binary representation of 15 is 01111. After setting right most bit it becomes 11111 which is 31.

Constraints :-
• 1 ≤ n.size() ≤ 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity: O(3log₂ n) __ Space Complexity : O(log₂ n)
/*
>> Intuition:

1. Convert n into its binary representation and store it in a string.
2. Start traversing the string from the rightmost bit.
3. Skip all the consecutive 1s until the first 0 is encountered.
4. If a 0 is found, change it to 1.
5. If all the bits are 1, append a new 1 at the beginning/end of the binary representation.
6. Convert the modified binary string back to decimal and return it.

>> Complexity Analysis:

-> Time Complexity: O(3log₂ n)
- convert2Binary takes O(log₂ n) time.
- Traversing the binary string takes O(log₂ n) time in the worst case.
- convert2Decimal takes O(log₂ n) time.

Total Time Complexity: O(log₂ n) + O(log₂ n) + O(log₂ n) = O(3log₂ n).

-> Space Complexity: O(log₂ n)
- The binary representation is stored in a string of length O(log₂ n).
- The additional variables use O(1) space.
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
    int multiplier = 1;  // Initial multiplier is 2^0 = 1.

    for (int i = n - 1; i >= 0; i--) {
        if (binary[i] == '1')
            num = num + multiplier;

        multiplier *= 2;
    }

    return num;
}

int setBitNaive(int n) {
    string s = convert2Binary(n);

    int i = s.size() - 1;
    while (i >= 0 && s[i] == '1') i--;

    // if string contains all 1s
    if (i < 0) {
        s.push_back('1');
    }

    else {
        s[i] = '1';
    }

    return convert2Decimal(s);
}

// Better Approach: Time Complexity: O(log₂ n) __ Space Complexity: O(1)
/*
Intuition:

1. Create a temporary variable temp = n.
2. Start checking the bits from the rightmost position.
3. As long as the current bit is 1, right-shift temp and
   increment the bit position.
4. Stop when the first unset bit (0) is encountered.
5. Create a bitmask using (1 << pos), which has only that
   bit set to 1.
6. Use bitwise OR (|) with n to set that bit to 1.

Since the identified bit is guaranteed to be 0, 
adding (1 << pos) to n also sets that bit without affecting the other bits.

>> Complexity Analysis:

-> Time Complexity: O(log₂ n)
- In the worst case, the loop traverses all the bits of n.
- The number of bits in n is O(log₂ n).

-> Space Complexity: O(1) - Only a constant number of integer variables are used.
*/
int setBit_Bitmask(int n) {
    int temp = n;
    
    int pos = 0;
    while (temp != 0 && (temp & 1) == 1) {
        pos++;
        temp >>= 1;
    }
    
    return n + (1 << pos);
    // return n | (1 << pos);
}

// Optimal Approach: Time Complexity : O(1) __ Space Complexity : O(1)
/*
>> Intuition:

The key observation is that n + 1 flips all the trailing
1s of n into 0s and changes the first 0 to their left into 1.

For example:
    n     = 10111  (23)
    n + 1 = 11000  (24)

Now consider n | (n + 1):
      10111
    | 11000
    -------
      11111  (31)

The OR operation sets the rightmost unset bit to 1.
All the bits to its right remain 1, and all the bits to its left remain unchanged.

Therefore, n | (n + 1) directly sets the rightmost unset bit of n.
*/
int setBit(int n) {
    return n | (n + 1);
}

int main() {
    return 0;
}