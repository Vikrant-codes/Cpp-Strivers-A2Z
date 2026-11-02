/*
Leetcode - 3158. Find the XOR of Numbers Which Appear Twice : Easy

You are given an array nums, where each number in the array appears either once or twice.
Return the bitwise XOR of all the numbers that appear twice in the array, or 0 if no number appears twice.

Examples :-

Input: nums = [1,2,1,3] __ Output: 1
Explanation:
The only number that appears twice in nums is 1.

Input: nums = [1,2,3] __ Output: 0
Explanation:
No number appears twice in nums.

Input: nums = [1,2,2,1] __ Output: 3
Explanation:
Numbers 1 and 2 appeared twice. 1 XOR 2 == 3.

Constraints :-
• 1 <= nums.length <= 50
• 1 <= nums[i] <= 50
• Each number in nums appears either once or twice.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (HashMap): Time Complexity : O(2n) __ Space Complexity : O(n)
/*
Use a map to store the frequencies of elements.
Iterate through the map and xor those elements which have frequency of two.
Return the xor.
*/
int duplicateNumbersXORHashMap(vector<int>& nums) {
    unordered_map<int, int> freq;

    for (int& num : nums)
        freq[num]++;
    
    int xorr = 0;

    for (auto& [num, cnt] : freq)
        if (cnt == 2)
            xorr ^= num;

    return xorr;
}

// Better Approach (HashSet): Time Complexity : O(n) __ Space Complexity : O(n)
/*
We can use a set to keep track of numbers we've already encountered.
- If a number is encountered for the first time, insert it into the set.
- If it is encountered for the second time, XOR it with our answer.
Since every number appears at most twice, we don't need to worry about encountering it again.
*/
int duplicateNumbersXORHashSet(vector<int>& nums) {
    unordered_set<int> seen;
    int xorr = 0;

    for (int num : nums) {
        if (seen.count(num)) {
            xorr ^= num;
        }
        else {
            seen.insert(num);
        }
    }

    return xorr;
}

// Optimal Approach: Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Optimal Approach – Using a Bitmask

We can use an integer as a bitmask to keep track of which numbers we've encountered.
Since numbers are between 1 and 50, we need only 51 bits to represent them. 
A long long (64 bits) is sufficient.

>> Intuition:

- For every number num, check whether its corresponding bit is already set in the bitmask.
- If the bit is already set, we've encountered this number before, so XOR it with our answer.
- Otherwise, set its corresponding bit in the bitmask.

We can use 1LL << num to represent the bit corresponding to num.

>> Complexity Analysis
- Time Complexity: O(n) – We traverse the array once, performing constant-time bitwise operations.
- Space Complexity: O(1) – We use only two variables, irrespective of the array size.
*/
int duplicateNumbersXOR(vector<int>& nums) {
    long long seen = 0;
    int xorr = 0;

    for (int num : nums) {
        if (seen & (1LL << num)) {
            xorr ^= num;
        }
        else {
            seen |= (1LL << num);
        }
    }
    
    return xorr;
}

int main() {
    return 0;
}