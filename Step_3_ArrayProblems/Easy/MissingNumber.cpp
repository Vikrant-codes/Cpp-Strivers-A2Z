/* 
Leetcode - 268. Missing Number : Easy

Given an array nums containing n distinct numbers in the range [0, n], 
return the only number in the range that is missing from the array.

Examples :-

Input: arr = [3,0,1] __ Output: 2
Explanation:
n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 
2 is the missing number in the range since it does not appear in nums.

Input: nums = [0,1] __ Output: 2
Explanation:
n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 
2 is the missing number in the range since it does not appear in nums.

Input: nums = [9,6,4,2,3,5,7,0,1] __ Output: 8
Explanation:
n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 
8 is the missing number in the range since it does not appear in nums.

Constraints :-
• n == nums.length
• 1 <= n <= 10^4
• 0 <= nums[i] <= n
• All the numbers of nums are unique.

Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
*/
#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach: Time Complexity: O(n²) __ Space Complexity: O(1)
/*
The array contains n elements from the range [0, n], with exactly one number missing. 
So, we can manually check each number in this range to find the missing one.

For each number `x` in [0, n], we linearly search the array to check if it is present. 
We use a boolean flag `found`, initially set to `false`, and set it to `true` if `x` is found in the array. 
If `found` remains `false` after checking the entire array, it means `x` is missing, so we return it.
*/
int missingNumberNaive(vector<int>& nums) {
    int n = nums.size();

    for (int x = 0; x <= n; x++) {
        bool found = false;
        
        for (int& num : nums) {
            if (num == x) {
                found = true;
                break;
            }
        }
        if (!found) return x;
    }

    return -1;      // dummy return, this return would never execute
}

// Better Approach (Using Hashing): Time Complexity: O(n) __ Space Complexity: O(n)
/*
To optimize our approach, we need to efficiently check whether a number is present in the array or not, 
for all numbers in the range [0, n].

We can use hashing to keep track of the numbers present in the array. 
We store the presence of each number, so we can efficiently check whether a number exists or not. 
We can use a hashmap, hashset, frequency array, or boolean vector for this purpose.

Then, we iterate through the range [0, n] and return the first number that is not marked as present, 
as it is the missing number.
*/
int missingNumberHashing(vector<int>& nums) {
    int n = nums.size();

    vector<bool> exists(n+1);

    for (int& x : nums) 
        exists[x] = true;

    for (int i = 0; i <= n; i++) 
        if (!exists[i])
            return i;
    /*
    vector<int> freq(n+1);
    
    for (int& x : nums) 
        freq[x]++;

    for (int i = 0; i <= n; i++) 
        if (freq[i] == 0)
            return i;
    */
    
    return -1;
}
/*
Approach 2 :-
We can use XOR to find the missing number. The XOR of a number with itself is 0 and the XOR of a number with 0 is the number itself.
So if we XOR all the numbers from 0 to n and also XOR all the elements of the array, the result will be the missing number.
ex - consider the array [0,1,4,3] and the missing number is 2 since range is [0,4].
XOR of all numbers from 0 to 4 = 0^1^2^3^4 = 4
XOR of all elements of the array = 0^1^4^3 = 6
So the final XOR will be 4^6 = 2 which is the missing number.
This can be shown as (0^1^2^3^4) ^ (0^1^4^3) = (0^0) ^ (1^1) ^ (2) ^ (3^3) ^ (4^4) = 0 ^ 0 ^ 2 ^ 0 ^ 0 .... since xor of a no. with itself is zero
thus (0^1^2^3^4) ^ (0^1^4^3) = 0 ^ 0 ^ 2 ^ 0 ^ 0 = 2 ... since xor of zero with any number is that number itself
*/

// Optimal Approach-1 (Mathematical Approach): Time Complexity: O(n) __ Space Complexity: O(1)
/*
>> Mathematical intuition:
The array contains n numbers from the range [0, n], with exactly one number missing.
Instead of checking which number is missing, we can use the sum of numbers to find it mathematically.

The sum of all numbers from 0 to n can be calculated using the formula: n * (n + 1) / 2

We calculate the expected sum of all numbers in the range and the actual sum of the elements present in the array, 
then subtract the actual sum from the expected sum.
When we subtract this, every number which is present in the array, 
is cancelled out by the number present in the sum of range [0, n], leaving only the missing number.

For example, assume n = 3 and nums = [3, 0, 1]. 
The expected numbers are 0, 1, 2, 3, while the actual numbers present are 3, 0, 1.
expected_sum = 6, actual_sum = 4. 
Subtracting expected_sum - actual_sum: 6 - 4 = 2 (missing number)

This happens because when subtracting actual_sum from expected_sum, 
the present values are cancelled leaving only the missing number.

like, for nums = [3, 0, 1].
expected_sum = 0 + 1 + 2 + 3
actual_sum = 3 + 0 + 1 

expected_sum - actual_sum = (0 + 1 + 2 + 3) - (3 + 0 + 1) 
                          = (0 - 0) + (1 - 1) + 2 + (3 - 3) 
                          = 2
As we can see, all the numbers present in the array cancel each other out, leaving only the missing number, 2.
*/
int missingNumber(vector<int>& nums) {
    int n = nums.size();

    int expectedSum = (n * (n + 1)) / 2;
    
    int sum = 0;
    for (int& x : nums) 
        sum += x;
    
    return expectedSum - sum;       // missing_no = expected_sum - actual_sum
}

// Optimal Approach-2 (using XOR): Time Complexity: O(n) __ Space Complexity: O(1)
/*
>> Intuition (XOR Approach)
The array contains n numbers from the range [0, n], with exactly one number missing.
We can use the XOR operation (^) to find the missing number. 
The key property of XOR is that a number XORed with itself becomes 0 (x ^ x = 0), 
and XORing any number with 0 gives the number itself (x ^ 0 = x).
i.e., x ^ x = 0
      x ^ 0 = x

So, if we XOR all numbers in the range [0, n] with all the numbers present in the array, 
every number that appears in both will cancel itself out, leaving only the missing number.

For example, assume n = 3 and nums = [3, 0, 1]. 
The expected numbers are 0, 1, 2, 3, while the actual numbers are 3, 0, 1.
( 0 ⊕ 1 ⊕ 2 ⊕ 3 ) ⊕ (3 ⊕ 0 ⊕ 1)
= (0 ⊕ 0) ⊕ (1 ⊕ 1) ⊕ (2) ⊕ (3 ⊕ 3)
= 0 ⊕ 0 ⊕ 2 ⊕ 0
= 2
Thus, the missing number is 2.

Complexity:
- Time: O(n), as we traverse the array once.
- Space: O(1), as we use only a constant amount of extra space.
*/
int missingNumberXOR(vector<int>& nums) {
    int n = nums.size();

    int xor1 = 0, xor2 = 0;
    
    // XOR all array elements
    for (int i = 0; i < n; i++) 
        xor1 ^= nums[i];
    
    // XOR all numbers from 0 to n
    for (int i = 0; i <= n; i++) 
        xor2 ^= i;

    // Missing number is the XOR of xor1 and xor2
    return xor1 ^ xor2;
}

// other implementations for XOR approach
int missingNumberXOR1(vector<int>& nums) {
    int n = nums.size();
    int xr = 0;

    for (int i = 0; i < n; i++) {
        xr ^= nums[i];
        xr ^= (i + 1);
    }
    
    return xr;
}

int missingNumberXOR2(vector<int>& nums) {
    int n = nums.size();
    int result = n;

    for (int i = 0; i < n; i++) {
        result ^= i ^ nums[i];
    }
    
    return result;
}

// GFG Variant
/*
GFG - Missing in Array : Easy

You are given an array arr[] of size n - 1 that contains distinct integers in the range from 1 to n (inclusive). 
This array represents a permutation of the integers from 1 to n with one element missing. 
Your task is to identify and return the missing element.

Examples :-

Input: arr[] = [1, 2, 3, 5] __ Output: 4
Explanation: All the numbers from 1 to 5 are present except 4.

Input: arr[] = [8, 2, 4, 5, 3, 7, 1] __ Output: 6
Explanation: All the numbers from 1 to 8 are present except 6.

Input: arr[] = [1] __ Output: 2
Explanation: Only 1 is present so the missing element is 2.

Constraints :-
• 1 ≤ arr.size() ≤ 10^6
• 1 ≤ arr[i] ≤ arr.size() + 1
*/

int missingNum(vector<int>& arr) {
    int n = arr.size() + 1;
    int xor1 = 0, xor2 = 0;

    // XOR all array elements
    for (int i = 0; i < n - 1; i++) {
        xor2 ^= arr[i];
    }

    // XOR all numbers from 1 to n
    for (int i = 1; i <= n; i++) {
        xor1 ^= i;
    }

    // Missing number is the XOR of xor1 and xor2
    return xor1 ^ xor2;
}

int missingNum2(vector<int>& arr) {
    int n = arr.size();
    
    int xr = n + 1;
    
    for(int i = 0; i < n; i++) {
        xr ^= arr[i];
        xr ^= (i + 1);
    }
    
    return xr;
}

int main() {
    return 0;
}