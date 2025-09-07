/*
Leetcode - 493. Reverse Pairs

Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where:
-> 0 <= i < j < nums.length and
-> nums[i] > 2 * nums[j].

Example 1:
Input: nums = [1,3,2,3,1] __ Output: 2
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

Example 2:
Input: nums = [2,4,3,5,1] __ Output: 3
Explanation: The reverse pairs are:
(1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
(2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
(3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1

Constraints : 1 <= nums.length <= 5 * 104 __ -231 <= nums[i] <= 231 - 1
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
int reversePairsBrute(vector<int> nums) {
    int count = 0;
    int n = nums.size();
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if (nums[i] > 2 * nums[j])
                count++;
        }
    }
    return count;
}

// Optimal Approach : Time Complexity : O(2 * n * logn) __ Space Complexity : O(n)
/*
Time Complexity: O(2N*logN), where N = size of the given array.
Reason: Inside the mergeSort() we call merge() and countPairs() except mergeSort() itself. Now, inside the function countPairs(), 
though we are running a nested loop, we are actually iterating the left half once and the right half once in total. 
That is why, the time complexity is O(N). And the merge() function also takes O(N). The mergeSort() takes O(logN) time complexity. 
Therefore, the overall time complexity will be O(logN * (N+N)) = O(2N*logN).
*/
/*
Using the same approach as count Inversions .. But here we use a different function to count Reverse Pairs because consider the two sorted halves 
[3,5,6,7], [1,2] now here in count Inversions we would count the pairs (3,1), (5,1), (6,1), (7,1) and (3,2), (5,2), (6,2), (7,2) but in case of 
reverse pairs if we consider (3,2) it won't be a reverse pair and if we use this in merge function logic it would then consider that 2 doesn't form 
pair with the other elements of left part as well but this is not true since (5,2), (6,2), (7,2) are reverse pairs. So we make a different function 
to count the pairs and do the merging in another function. 
*/ 
void merge(vector<int> &nums, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid+1;
    while (left <= mid && right <= high) {
        if (nums[left] <= nums[right]) {
            temp.push_back(nums[left]);
            left++;
        }
        else {
            temp.push_back(nums[right]);
            right++;
        }
    }
    while (left <= mid) {
        temp.push_back(nums[left]);
        left++;
    }
    while (right <= high) {
        temp.push_back(nums[right]);
        right++;
    }
    for(int i=low; i<=high; i++) {
        nums[i] = temp[i-low];
    }
}
int countPairs(vector<int> &nums, int low, int mid, int high) {
    int cnt = 0, right = mid + 1;
    for(int i=low; i<=mid; i++) {
        // this long long is used to avoid overflow in case of large numbers
        while (right <= high && (long long) nums[i] > 2 * (long long) nums[right]) right++;
        cnt += right - (mid+1);
    }
    return cnt;
}
int mergeSort(vector<int> &nums, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt;
    int mid = low + (high - low) / 2;
    cnt += mergeSort(nums, low, mid);
    cnt += mergeSort(nums, mid+1, high);
    cnt += countPairs(nums, low, mid, high);
    merge(nums, low, mid, high);
    return cnt;
}
int reversePairs(vector<int>& nums) {
    return mergeSort(nums, 0, nums.size()-1);
}

int main() {
    vector<int> nums = {2,4,3,5,1};
    int reverse_pairs = reversePairs(nums);
    cout << "Number of reverse pairs : " << reverse_pairs << endl;
    for(int x : nums) cout << x << " ";

    return 0;
}