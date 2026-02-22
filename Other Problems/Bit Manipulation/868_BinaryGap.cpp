/*
Leetcode - 868. Binary Gap : Easy

Given a positive integer n, find and return the longest distance between any two adjacent 1's in the binary representation of n. 
If there are no two adjacent 1's, return 0.

Two 1's are adjacent if there are only 0's separating them (possibly no 0's). 
The distance between two 1's is the absolute difference between their bit positions. 
For example, the two 1's in "1001" have a distance of 3.

Examples :-

Input: n = 22
Output: 2
Explanation: 22 in binary is "10110".
The first adjacent pair of 1's is "10110" with a distance of 2.
The second adjacent pair of 1's is "10110" with a distance of 1.
The answer is the largest of these two distances, which is 2.
Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.

Input: n = 8
Output: 0
Explanation: 8 in binary is "1000".
There are not any adjacent pairs of 1's in the binary representation of 8, so we return 0.

Input: n = 5
Output: 2
Explanation: 5 in binary is "101".

Constraints :-
- 1 <= n <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O( ⌊log2 ​(n)⌋ + 1 ) __ Space Complexity : O(1)
/*
Think of the binary number as a sequence of bits from right to left.
Example: 22 → 10110

🔹 Step 1: Ignore leading zeros
We first remove trailing 0s (from LSB side) until we hit the first 1.
Why?
    Because a binary gap is defined between two 1s.
    Anything before the first 1 is useless — there’s no left boundary yet.

🔹 Step 2: Start measuring distance
Once the first 1 is found:
- We start counting distance (cnt = 1)
- Move bit by bit
- Every time we see:
    - 0 → increase distance
    - 1 → we found the next boundary
At that moment:
    - We update the maximum gap
    - Reset counter to start measuring the next gap

🔹 Why cnt starts from 1?
    Because you're counting distance between positions, not just number of zeros.
Example: 101
Positions:
1 _ 1
0 1 2
Distance = 2 - 0 = 2
This counter correctly captures that.

🧠 Core Insight
We're treating:
Every 1 as a checkpoint
Counting how far the next 1 is
Keeping the maximum distance
So mentally it is:
    “From one 1, how far is the next 1?”
That’s exactly what binary gap means.
*/
int binaryGap1(int n) {
    int temp = n;
    // extract the 1st 1 bit
    while (temp) {
        int lbit = temp & 1;
        temp >>= 1;
        if (lbit == 1) break;
    }

    // now start counting the distance between the adjacent 1s
    int cnt = 1;
    int ans = 0;
    while (temp) {
        int lbit = temp & 1;
        temp >>= 1;
        if (lbit == 1) {
            ans = max(ans, cnt);    // update answer if this gap/distance is larger
            cnt = 1;                // reset counter
        }
        else 
            cnt++;
    }

    return ans;
}

// Time Complexity : O( ⌊log2 ​(n)⌋ + 1 ) __ Space Complexity : O(1)
/*
Intuition Behind This Approach
This version is thinking in terms of bit positions, not counting zeros.
Instead of counting the gap step-by-step, we're doing:
|   “Whenever I see a 1, I record its position.
|   If I see another 1, I compute the distance between their positions.”

🔹 Core Idea
Binary gap = (position of current 1) − (position of previous 1)
So we just need:
    Current bit position (pos)
    Last position where you saw a 1 (last)
That’s it.

🔹 What Each Variable Represents
- pos → index of current bit (0, 1, 2, …)
- last → position of the previous 1
- ans → maximum distance found so far

🔹 Mental Picture
Example: n = 22 → 10110
Positions (from right):
    Bit:      0 1 1 0 1
    Position: 0 1 2 3 4

Step-by-step thinking:
pos 1 → first 1 → store last = 1
pos 2 → another 1 __ distance = 2 - 1 = 1
pos 4 → another 1 __ distance = 4 - 2 = 2
Maximum = 2
*/
int binaryGap(int n) {
    int last = -1;          // last seen position of 1
    int pos = 0;            // current position
    int ans = 0;            // answer, i.e., the maximum distance between two 1s (initially 0)

    while (n) {
        // the last bit can be extracted using n & 1, if it is 1, update distance
        if (n & 1) {
            // if 1 has previously appeared, i.e., if last is not -1.
            if (last != -1)
                ans = max(ans, pos - last);     // pos-last gives the distance between the current adjacent 1s
            last = pos;             // last seen 1 is at position pos
        }
        n >>= 1;            // right shift n to extract the next bits
        pos++;              // increment position
    }

    return ans;
}

int main() {
    return 0;
}