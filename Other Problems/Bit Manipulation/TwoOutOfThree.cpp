/*
Leetcode - 2032. Two Out of Three : Easy

Given three integer arrays nums1, nums2, and nums3, 
return a distinct array containing all the values that are present in at least two out of the three arrays. 
You may return the values in any order.

Examples:

Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3] __ Output: [3,2]
Explanation: The values that are present in at least two arrays are:
- 3, in all three arrays.
- 2, in nums1 and nums2.

Input: nums1 = [3,1], nums2 = [2,3], nums3 = [1,2] __ Output: [2,3,1]
Explanation: The values that are present in at least two arrays are:
- 2, in nums2 and nums3.
- 3, in nums1 and nums2.
- 1, in nums1 and nums3.

Input: nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5] __ Output: []
Explanation: No value is present in at least two arrays.

Constraints:-
- 1 <= nums1.length, nums2.length, nums3.length <= 100
- 1 <= nums1[i], nums2[j], nums3[k] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Approach1 (3 hash arrays) :- Time Complexity : O(n1 + n2 + n3) __ Space Complexity : O(1)
/*
The numbers are in the range [1,100] so for each given array, we create a hasharray which tells us whether a certain element 
is present in that array or not.
Since elements are limited in size, we use hasharrays of size 101 for the elements 1-100.
we use a bool vector and for each element of the array we set the value for that element to be 'true' 
in the corresponding hasharray.

We initialize the 3 hasharrays : present1 (for nums1), present2 (for nums2) and present3 (for nums3).
After updating the values in the corresponding hasharrays, for each element in the range [1-100], 
we check which elements are present in at least 2 of the three arrays. Insert those elements to the answer vector
*/
vector<int> twoOutOfThree1(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
    vector<bool> present1(101), present2(101), present3(101);
    vector<int> ans;
    for (int x : nums1) present1[x] = true;
    for (int y : nums2) present2[y] = true;
    for (int z : nums3) present3[z] = true;

    for (int i = 1; i < 101; i++) {
        if (present1[i]) {
            if (present2[i] || present3[i]) ans.push_back(i);
        }
        else if (present2[i] && present3[i]) ans.push_back(i);
    }

    return ans;
}

// Approach (Bit Approach) :- Time Complexity : O(n1 + n2 + n3) __ Space Complexity : O(1)
/*
Intuition
The problem asks:
| Which numbers appear in at least two of the three arrays?
Instead of counting occurrences, we only care about presence in each array.

Core idea: use a 3-bit mask per number
Think of each number having three switches:
| Bit       | Meaning            |
| --------- | ------------------ |
| `1` (001) | Present in `nums1` |
| `2` (010) | Present in `nums2` |
| `4` (100) | Present in `nums3` |
bits[x] stores this mask.

How the code builds the mask ?

bits[x] |= 1;   // turn ON bit for nums1
bits[y] |= 2;   // turn ON bit for nums2
bits[z] |= 4;   // turn ON bit for nums3

• |= is bitwise OR assignment
• |= turns on a bit and never turns it off
• Repeated numbers don’t change anything
• Order doesn’t matter

Why does this work here?
Each number in the map stores a bitmask representing presence in arrays:
| Array   | Bit value |
| ------- | --------- |
| `nums1` | `001` (1) |
| `nums2` | `010` (2) |
| `nums3` | `100` (4) |

Step-by-step intuition
1. Initially : bits[x] = 0 // default
2. When x appears in nums1 :- bits[x] |= 1 ..... // 000 | 001 = 001 (bitwise OR)
3. When x appears in nums2 :- bits[x] |= 2 ..... // 001 | 010 = 011
4. When x appears in nums3 :- bits[x] |= 4 ..... // 011 | 100 = 111
<< Each OR operation sets a bit and never unsets it. 

Why OR (|=) and not + ?
• |= guarantees idempotence
• If a number appears multiple times in the same array, the bit stays set

To check for presence in at least 2 of three arrays, the condition is bits[i] == 3 || bits[i] > 4, this is because
| Decimal | Binary | Meaning       |
| ------- | ------ | ------------- |
| 3       | `011`  | nums1 + nums2 |
| 5       | `101`  | nums1 + nums3 |
| 6       | `110`  | nums2 + nums3 |
| 7       | `111`  | all three     |
All represent at least two arrays.
*/
vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
    vector<int> bits(101);
    vector<int> ans;
    
    for (int x : nums1) bits[x] |= 1;       // bitwise OR operation , equivalent to bits[x] = bits[x] | 1 (bitwise OR)
    for (int y : nums2) bits[y] |= 2;
    for (int z : nums3) bits[z] |= 4;

    for (int i=1; i<101; i++) {
        if (bits[i] == 3 || bits[i] > 4) ans.push_back(i);
    }

    return ans;
}

int main() {
    return 0;
}