/*
Leetcode - 2154. Keep Multiplying Found Values by Two : Easy

You are given an array of integers nums. 
You are also given an integer original which is the first number that needs to be searched for in nums.

You then do the following steps:
1. If original is found in nums, multiply it by two (i.e., set original = 2 * original).
2. Otherwise, stop the process.
3. Repeat this process with the new number as long as you keep finding the number.

Return the final value of original.

Examples :-

Input: nums = [5,3,6,1,12], original = 3 __ Output: 24
Explanation: 
- 3 is found in nums. 3 is multiplied by 2 to obtain 6.
- 6 is found in nums. 6 is multiplied by 2 to obtain 12.
- 12 is found in nums. 12 is multiplied by 2 to obtain 24.
- 24 is not found in nums. Thus, 24 is returned.

Input: nums = [2,7,9], original = 4 __ Output: 4
Explanation:
- 4 is not found in nums. Thus, 4 is returned.

Constraints :-
- 1 <= nums.length <= 1000
- 1 <= nums[i], original <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n ^ 2) __ Space Complexity : O(1)
int findFinalValueBrute(vector<int>& nums, int original) {
    bool found = false;
    
    while (true) {
        // find original in the nums array
        for (int& x : nums) {
            if (x == original) {
                found = true;
                break;
            }
        }
        // if original is found in the array, double it and reset the 'found' variable
        if (found) {
            original *= 2;
            found = false;
        }
        else 
            break;
    }
    
    return original;
}

// Sorting + Binary Search : Time Complexity : O(n * log n) __ Space Complexity : O(1)
bool binarySearch(vector<int>& nums, int target) {
    int low = 0, high = nums.size()-1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (nums[mid] == target) return true;
        else if (nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return false;
}

int findFinalValue1(vector<int>& nums, int original) {
    sort(nums.begin(), nums.end());

    while (binarySearch(nums, original))
        original *= 2;

    return original;
}

// HashSet Approach : Time Complexity : O(n) __ Space Complexity : O(n)
int findFinalValue2(vector<int>& nums, int original) {
    unordered_set<int> s;
    for (int& x : nums)
        s.insert(x);

    while (s.count(original))
        original *= 2;
    
    return original;
}

// HashArray Approach : Time Complexity : O(n) __ Space Complexity : O(1)
// Approach: Since elements are in range [1,1000], 
// we can use a fixed 1000 sized array to hash the array elements for easier existence check.
int findFinalValue(vector<int>& nums, int original) {
    vector<int> hashArr(1000);
    for (int& x : nums)
        hashArr[x-1]++;
    // we check original <= 1000 because for larger values ( >1000 ) we will get error since array has at most index 999. 
    while (original <= 1000 && hashArr[original-1])
        original *= 2;
    
    return original;
}

int main() {
    return 0;
}