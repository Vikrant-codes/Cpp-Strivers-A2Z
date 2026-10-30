/*
Leetcode - 260. Single Number III : Medium

Given an integer array nums, in which exactly two elements appear only once and 
all the other elements appear exactly twice. 
Find the two elements that appear only once. You can return the answer in any order.

You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Examples :-

Input: nums = [1,2,1,3,2,5] __ Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Input: nums = [-1,0] __ Output: [-1,0]

Input: nums = [0,1] __ Output: [1,0]

Constraints :-
• 2 <= nums.length <= 3 * 10^4
• -2^31 <= nums[i] <= 2^31 - 1
• Each integer in nums will appear twice, only two integers will appear once.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity : O(n²) __ Space Complexity : O(1)
/*
>> Intuition
For each element, count how many times it appears in the array by comparing it with every other element. 
If its frequency is 1, add it to answer vector. Return the answer vector.

>> Complexity Analysis:
- Time: O(n²) — For each element, we traverse the entire array to count its frequency.
- Space: O(1) — Only a constant amount of extra space is used.
*/
vector<int> singleNumberBrute(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        int cnt = 0;
    
        for (int j = 0; j < n; j++)
            if (nums[j] == nums[i])
                cnt++;
    
        if (cnt == 1)
            ans.push_back(nums[i]);
    }

    return ans;
}

// Naive Approach: Time Complexity : O(n) __ Space Complexity : O( (n / 2) + 1 )
/*
We can use a hash map to store each element and its frequency. 
First, traverse the array and increment the frequency of each element. 
Then, traverse the map and add those elements with frequency 1 to the answer/result vector.

This approach is straightforward, but it doesn't satisfy the problem's constant extra space requirement, 
because the hash map takes extra space to store the distinct elements.
Since nums has all elements appearing twice except for two elements, 
total no. of distinct elements = (n - 2) / 2 + 2 = (n / 2) + 1. 

>> Complexity Analysis:
- Time: O(n) average — One traversal to count frequencies and another to find the single element.
- Space: O( (n / 2) + 1 ) — The hash map stores the distinct elements and their frequencies.
*/
vector<int> singleNumberNaive(vector<int>& nums) {
    unordered_map<int, int> mpp;

    for (int& x : nums)
        mpp[x]++;
    
    vector<int> ans;
    for (auto& [num, freq] : mpp) 
        if (freq == 1)
            ans.push_back(num);

    return ans;
}

// Optimal Approach: Time Complexity : O(2n) __ Space Complexity : O(1)
/*
>> Intuition — XOR + Bit Manipulation

The key idea is to use XOR to cancel out duplicate numbers, 
then use one differing bit to separate the two unique numbers.

1. XOR all the elements
|   long xorr = 0;
|   
|   for (int num : nums)
|       xorr ^= num;

We know that:
- a ^ a = 0
- a ^ 0 = a
- XOR is commutative and associative.
Since every number appears exactly twice except the two unique numbers, all duplicate pairs cancel each other out.

Therefore, after XORing the entire array: xorr = unique_1 ^ unique_2
This gives us the XOR of the two unique numbers.

Important: Since the two unique numbers are different, their XOR cannot be zero. 
This means at least one bit in xorr must be set.

xorr will have set bits at positions where the bits of the two unique numbers differ.

2. Find a bit where the two unique numbers differ
|   int rightmostBit = (xorr & (xorr - 1)) ^ xorr;

The two unique numbers must differ at every bit position where their XOR has a 1.
We need to find just one such position so that we can separate the two numbers into different groups.

The expression: `xorr & (xorr - 1)` removes the rightmost set bit of xorr.
XORing that result with the original xorr isolates the removed bit: `(xorr & xorr - 1) ^ (xorr)`
So, rightmostBit contains only the rightmost set bit of xorr.

For example:
xorr              = 101100
xorr - 1          = 101011
xorr & (xorr - 1) = 101000
XOR               = 000100

Therefore: rightmostBit = 000100

This bit is set in one unique number and unset in the other.

3. Divide the numbers into two buckets
|   int bucket1 = 0, bucket2 = 0;
|   
|   for (int num : nums) {
|       if (num & rightmostBit)
|           bucket1 ^= num;
|       else
|           bucket2 ^= num;
|   }

We use the bit we just isolated to divide all numbers into two groups:
- Bucket 1: Numbers where rightmostBit is set.
- Bucket 2: Numbers where rightmostBit is not set.

Why does this work?
The two unique numbers have different values at this particular bit position, 
so they are guaranteed to go into different buckets.

Also, every duplicate number has exactly the same bit pattern in both occurrences. 
Therefore, both copies always go into the same bucket and cancel each other out when XORed.

As a result:
- bucket1 contains one unique number.
- bucket2 contains the other unique number.

4. Return the two unique numbers `return {bucket1, bucket2};`
Both buckets now contain exactly one unique number, which gives us the required answer.
_______________________________________________________________________________________________________________

>> Why is xorr declared as long instead of int?

The reason is to avoid integer overflow when calculating xorr - 1, particularly when xorr is equal to INT_MIN.

Consider this example: nums = {1, 0, 2, -2147483648, 1, 2};

After XORing all elements, the duplicate pairs cancel out, leaving: xorr = 0 ^ -2147483648 = -2147483648;  // INT_MIN

In a 32-bit signed integer, INT_MIN has the following binary representation: 10000000000000000000000000000000

Notice that its leftmost bit (sign bit) is set.
Now, to isolate the rightmost set bit, we calculate: xorr & (xorr - 1)

But if xorr is an int equal to INT_MIN, 
calculating xorr - 1 would go below the minimum representable value of a 32-bit signed integer.
This causes signed integer overflow, which is undefined behavior in C++.

By declaring xorr as long, we give it a wider integer range (on platforms where long is 64-bit). 
Therefore, xorr - 1 can be calculated without overflowing.

One important platform note: On typical 64-bit Linux systems, long is 64-bit, but on 64-bit Windows, long is still 32-bit. 
For portable C++, we can use long long instead.
_______________________________________________________________________________________________________________

>> Complexity Analysis
- Time Complexity: O(2n) — We traverse the array twice, and each XOR/bitwise operation takes constant time.
- Space Complexity: O(1) — We use only a few variables, regardless of the input size.
_______________________________________________________________________________________________________________

>> The core intuition
XOR the entire array to obtain the XOR of the two unique numbers. 
Find a bit where they differ, use that bit to separate the array into two groups, 
and XOR each group independently to recover the two unique numbers.
_______________________________________________________________________________________________________________
*/
vector<int> singleNumber(vector<int>& nums) {
    long xorr = 0;          // Why is xorr declared as long? 
    
    for (int num : nums) 
        xorr ^= num;
    
    int rightmostBit = (xorr & xorr - 1) ^ (xorr);      // number having only the rightmost bit set
    
    int bucket1 = 0, bucket2 = 0;
    
    for (int num : nums) {

        if (num & rightmostBit) 
            bucket1 ^= num;

        else
            bucket2 ^= num;
    }
    
    return {bucket1, bucket2};
}

int main() {
    return 0;
}