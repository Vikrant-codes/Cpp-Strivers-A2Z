/*
Leetcode - 704. Binary Search

Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. 
If target exists, then return its index. Otherwise, return -1.

Example 1: Input: nums = [-1,0,3,5,9,12], target = 9 __ Output: 4
Example 2: Input: nums = [-1,0,3,5,9,12], target = 2 __ Output: -1 

Constraints: 
1 <= nums.length <= 10 ^ 4 __ -10 ^ 4 < nums[i], target < 10 ^ 4
All the integers in nums are unique __ nums is sorted in ascending order
*/

#include <bits/stdc++.h>
using namespace std;

// Iterative Approach : Time Complexity : O(ceil(log n)) __ Space Complexity : O(1)
/*
To find an element in array using binary search the no of comparisons required could range between 1 to log (n).
1 when we get the desried element in the first comparison. 
But there can be cases when the required no of comparisons would be log n + 1. Consider the below example -
Ex - arr = [0,1,2,3,4,5,6,7] and x = 7 
Now, len = 8 so log 8 = 3, but to search 7 we would need 4 comparisons. 
mid = 3 and 3 < 7 (1st comparison)
mid = 5 and 5 < 7 (2nd comparison)
mid = 6 and 6 < 7 (3rd comparison)
mid = 7 and 7 = 7 (4th comparison)
The same situation could have arise for any x such that x was greater than 7 in this case 

" If n is a power of 2, the worst case (max comparisons) happens when the target is in the last position OR 
is not present but would be after the last element. "
This happens becuase -- 
- When n is a power of 2, binary search keeps splitting exactly in half until only 1 element remains.
- If the target happens to be the last element (largest), the search will always go to the right half until it lands on 
  the very last index.
- That path requires log2(n) "go-right" steps plus one final comparison to confirm the last element.
- So total comparisons = log2(n) + 1

Worst Case Complexity : O(ceil(log n) + 1)
*/
int binarySearch(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n-1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

// Recursive Approach : Time Complexity : O(log n) __ Space Complexity : O(log n) due to recursion stack
int binarySearchRec(vector<int> nums, int low, int high, int target) {
    if (low > high) return -1; // Base case : target not found

    int mid = low + (high - low) / 2;

    if (nums[mid] == target) 
        return mid;
    else if (nums[mid] > target) 
        return binarySearchRec(nums, low, mid-1, target);
    else 
        return binarySearchRec(nums, mid+1, high, target);
}

int main() {
    vector<int> arr = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    int ind = binarySearchRec(arr, 0, arr.size()-1, target);
    if (ind != -1) cout << "Element found at index : " << ind << endl;
    else cout << "Element not found" << endl;

    return 0;
}