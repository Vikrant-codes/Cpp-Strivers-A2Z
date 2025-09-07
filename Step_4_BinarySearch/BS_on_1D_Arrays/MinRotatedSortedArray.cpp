/*
Leetcode - 153. Find Minimum in Rotated Sorted Array -- Medium

Examples :-

Input: nums = [3,4,5,1,2] __ Output: 1
Input: nums = [4,5,6,7,0,1,2] __ Output: 0
Input: nums = [11,13,15,17] __ Output: 11

Constraints :- 1 <= n <= 5000 __ -5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach :- Time Complexity: O(log n) __ Space Complexity: O(1)
/*
Approach :- In a sorted array the minimum element is the first element. But here the array is rotated. 
We can use binary search to find the minimum element. Keep a minimum variable to store the minimum element found so far. 

The idea is to get mid element and check if left half is sorted or right half is sorted. 

If left half is sorted then we can surely say that the leftmost element of that half will be the minimum in that half. 
So we can update the minimum element with the first element of sorted left half i.e. nums[low].
Now that we have got the minimum of that half we can eliminate that half by updating the low pointer to mid + 1.

If right half is sorted then we can surely say that the mid element will be the minimum in that half. 
So we can update the minimum element with the first element of sorted right half i.e. mid element i.e. nums[mid].
Now we eliminate the right half by updating the high pointer to mid - 1.
*/

int findMin(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    int ans = 9999;
    while (low <= high) {
        int mid = (low + high) / 2;
        //if left part is sorted
        if (nums[low] <= nums[mid]) {
            ans = min(ans, nums[low]);       // keep the minimum
            low = mid + 1;                   // Eliminate left half
        }
        //if right part is sorted:
        else { 
            ans = min(ans, nums[mid]);       // keep the minimum
            high = mid - 1;                  // Eliminate right half
        }
    }
    return ans;
}

/*
The approach is similar to the above one but it's just a slight optimization.
Here we check that if the search space is already sorted. Like while updating the low and high pointers the search space becomes such that the whole 
search space is sorted i.e. when nums[low] <= nums[high]. In that case we know that the first element of that search space will be the minimum element 
and thus we won't need to do any further checks in the search space. So, we update the result with the nums[mid] and break the loop.
*/

int findMin2(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    int ans = 9999;
    while (low <= high) {
        int mid = (low + high) / 2;
        //search space is already sorted then nums[low] will always be the minimum in that search space:
        if (nums[low] <= nums[high]) {
            ans = min(ans, nums[low]);
            break;
        }
        //if left part is sorted
        if (nums[low] <= nums[mid]) {
            ans = min(ans, nums[low]);       // keep the minimum
            low = mid + 1;                   // Eliminate left half
        }
        //if right part is sorted:
        else {
            ans = min(ans, nums[mid]);       // keep the minimum
            high = mid - 1;                  // Eliminate right half
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int result = findMin(arr);
    cout << "Minimum element in the rotated sorted array is: " << result << endl;

    return 0;
}