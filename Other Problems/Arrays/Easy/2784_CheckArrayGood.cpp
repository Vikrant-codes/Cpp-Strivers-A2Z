/*
Leetcode - 2784. Check if Array is Good : Easy

You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].
base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, 
plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].
Return true if the given array is good, otherwise return false.

Note: A permutation of integers represents an arrangement of these numbers.

Examples :-

Input: nums = [2, 1, 3] __ Output: false
Explanation: Since the maximum element of the array is 3, 
the only candidate n for which this array could be a permutation of base[n], is n = 3. 
However, base[3] has four elements but array nums has three. 
Therefore, it can not be a permutation of base[3] = [1, 2, 3, 3]. So the answer is false.

Input: nums = [1, 3, 3, 2] __ Output: true
Explanation: Since the maximum element of the array is 3, 
the only candidate n for which this array could be a permutation of base[n], is n = 3. 
It can be seen that nums is a permutation of base[3] = [1, 2, 3, 3] (by swapping the second and fourth elements in nums, 
we reach base[3]). Therefore, the answer is true.

Input: nums = [1, 1] __ Output: true
Explanation: Since the maximum element of the array is 1, 
the only candidate n for which this array could be a permutation of base[n], is n = 1. 
It can be seen that nums is a permutation of base[1] = [1, 1]. Therefore, the answer is true.

Input: nums = [3, 4, 4, 1, 2, 1] __ Output: false
Explanation: Since the maximum element of the array is 4, 
the only candidate n for which this array could be a permutation of base[n], 
is n = 4. However, base[4] has five elements but array nums has six. 
Therefore, it can not be a permutation of base[4] = [1, 2, 3, 4, 4]. So the answer is false.

Constraints :-
- 1 <= nums.length <= 100
- 1 <= nums[i] <= 200
*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1 (Sorting) : Time Complexity : O(n logn) + O(n) __ Space Complexity : O(1)
/*
>> Intuition
A good array for some n must contain all the elements in the range [1, n] with n appearing twice.

As explained in problem statement, We consider an array good if it is a permutation of an array base[n].
base[n] = [1, 2, ..., n - 1, n, n] 
(in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences of n).

So, if we sort a given array of size 'k + 1', then the array must look like: [1, 2, 3, ..., k-1, k, k]
So, to check whether an array is good or not, we can simply sort it and check whether it is like the above array or not.
After sorting an array of length 'n': 
- Indices 0 to n - 2 should contain values 1 to n-1 i.e. nums[index] must equal value 'index + 1'
- The last index i.e. n-1 must contain value 'n-1' (this is the duplicate maximum)

>> Approach:
- Sort the array
- Run a loop from 0 to index n-2 and check value at index 'i' must be equal to 'i + 1'
- The last element at index n-1 must be equal to n-1 itself.

>> Complexity Analysis
Sorting takes: O(nlogn)
Traversal takes: O(n)
Overall Time Complexity: O(nlogn) + O(n)

Space Complexity: O(1)
*/
bool isGoodSorting(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 0; i < n-1; i++)
        if (nums[i] != i+1)
            return false;

    return nums[n-1] == n-1;
}

// Approach 2 (Frequency Array): Time Compelxity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
Instead of sorting, this approach uses a frequency array (hashArr) to count how many times each number appears.

For a good array of size n:
- numbers 1 to n-2 must appear exactly once
- the maximum number (n-1) must appear exactly twice
- no other frequencies are allowed

Given the constraints: 1 <= nums[i] <= 200, a frequency array of size 201 is sufficient.
We store the frequency of number k at index k, so indices 0 to 200 are required.

The frequency array for a valid array should look like: [0, 1, 1, 1, ..., 1, 2, 0, 0, ...]

Explanation:
- index 0 always has frequency 0 because 0 is not allowed
- indices [1, n-2] must have frequency 1
- index (n-1) must have frequency 2
- all larger numbers must have frequency 0

>> To verify this:
1. Start from the end of the frequency array and find the first non-zero frequency.
   This corresponds to the maximum element.
2. This frequency must be 2. Otherwise return false.
3. Move left and check whether all remaining frequencies are exactly 1.
4. The traversal should stop at index 0. If it stops earlier, return false.

>> Complexity Analysis
Frequency counting: O(n)
Scanning frequency array of size 201: O(201) ~ O(1)
Overall Time Complexity: O(n)
Space Complexity: O(1), because the frequency array size is fixed (201).
*/
bool isGood1(vector<int>& nums) {
    vector<int> hashArr(201);       // 201 size is taken because we are storing a number 'n' freq. at index 'n' and not 'n-1'

    for (int x : nums) hashArr[x]++;
    
    int i = 200;
    
    while (i > 0 && hashArr[i] == 0)
        i--;
    
    if (hashArr[i] != 2) return false;
    
    i--;
    while (i > 0 && hashArr[i] == 1) i--;
    
    return i == 0;
}

// Approach 3 (Hash Map + Max. element): Time Compelxity : O(n) __ Space Complexity : O(n)
/*
>> Intuition
This approach uses a hash map (unordered_map) to store the frequency of each number 
while simultaneously finding the maximum element in the array.

For a good array:
- if the maximum element is mx, 
  then the array must be a permutation of: [1, 2, 3, ..., mx-1, mx, mx]

Therefore:
- numbers 1 to mx-1 must appear exactly once
- the maximum element mx must appear exactly twice
- the total size of the array must be mx + 1

Why mx + 1 ?
- numbers from 1 to mx-1 contribute (mx - 1) elements
- mx appears twice
Total elements: (mx - 1) + 2 = mx + 1

So, if nums.size() != mx + 1, the array cannot be good.

--------------------------------------------------
Step 1: Build the frequency map while finding the maximum element.
freq[x] stores how many times x appears.
--------------------------------------------------
Step 2: Check whether the size of the array is mx + 1.
If not, return false immediately.
--------------------------------------------------
Step 3: 
Validate frequencies:
- maximum element (mx) must have frequency 2
- every other element must have frequency 1
If any condition fails, return false.
Otherwise, return true.

>> Complexity Analysis
Time Complexity :-
Building frequency map: O(n)
Frequency validation: O(n)
Overall: O(n)

Space Complexity: Hash map stores frequencies of distinct elements:- O(n)
*/
bool isGood2(vector<int>& nums) {
    unordered_map<int, int> freq;
    int mx = 0;

    for (int x : nums) {
        freq[x]++;
        if (x > mx) mx = x;
    }

    if (nums.size() != mx + 1) return false;

    for (int x : nums) {
        if (x == mx) {
            if (freq[x] != 2)
                return false;
        }
        else if (freq[x] != 1)
            return false;

        // if ((x == mx && freq[x] != 2) || (x != mx && freq[x] != 1)) 
        //     return false;
    }

    return true;
}

/*
>> Frequency Validation Improvement
The overall idea remains exactly the same as the previous approach:
- use a hash map to store frequencies
- find the maximum element mx
- validate size and frequencies based on the properties of a good array

The difference is in how the frequencies are validated.

Instead of iterating over the original array and repeatedly checking the same frequencies multiple times, 
this approach directly verifies the required structure of a good array.

After confirming:
- nums.size() == mx + 1
- freq[mx] == 2

we only need to ensure that every number in the range [1, mx-1] appears exactly once.
So, we simply iterate from 1 to mx-1 and check: freq[i] == 1
This makes the validation cleaner, more direct, and avoids redundant frequency checks.
*/
bool isGood(vector<int>& nums) {
    unordered_map<int, int> freq;
    int mx = 0;
    // Step-1 : Build the hash array and keep track of max. element
    for (int x : nums) {
        freq[x]++;
        if (x > mx) mx = x;
    }

    // Validate array size: must be equal to mx + 1
    if (nums.size() != mx + 1) return false;
    
    // Freq. of max element must be 2
    if (freq[mx] != 2) return false;
    
    // For elements in range 1 to mx-1, the freq. must be 1
    for (int i = 1; i < mx; i++)
        if (freq[i] != 1)
            return false;

    return true;
}

int main() {
    vector<int> nums = {1, 3, 3, 2};
    cout << isGood2(nums);


    return 0;
}