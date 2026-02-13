// Given an array containing only 0s, 1s and 2s. Sort the array.
/*
Leetcode - 75. Sort Colors : Medium

Given an array nums with n objects colored red, white, or blue, 
sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
You must solve this problem without using the library's sort function.

Examples :-

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Input: nums = [2,0,1]
Output: [0,1,2]

Constraints :-
- n == nums.length
- 1 <= n <= 300
- nums[i] is either 0, 1, or 2.

Follow up: Could you come up with a one-pass algorithm using only constant extra space?
*/
#include <iostream>
#include <vector>
using namespace std;

/*
Approach 1 : using a hash array of size 3 / 3 variables to store the counts of 0s, 1s and 2s. 
Run a loop and change the first count_0 elements to 0, next count_1 elements to 1 and the rest to 2.
Time Complexity : O(2n) __ Space Complexity : O(1)
*/ 
void sort012(vector<int>& arr) {
    int freq[3] = {0};
    for(int i=0; i<arr.size(); i++) freq[arr[i]]++;
    for(int i=0; i<arr.size(); i++){
        if(i < freq[0]) arr[i] = 0;
        else if(i < freq[0] + freq[1]) arr[i] = 1;
        else arr[i] = 2;
    }
}

// Optimal Approach : 'Dutch National Flag Algorithm' --> Time Complexity : O(n) __ Space Complexity : O(1) 
/*
0 0 0 0      1 1 1 1 1      0 1 2 0 2 1 1 0      2 2 2 2 2 2
|     |      |       |      |             |      |         |
0    low-1  low    mid-1   mid           high   high+1    end

3 Pointer Approach :- We consider that the array is such that 0 - low-1 are all 0s , low - mid-1 are all 1s, mid - high is unsorted part 
& high + 1 - end are all 2s .. so the only unsorted part is mid - high. So we traverse this part and if we encounter 0 we swap it with arr[low] 
and do low++, mid++ .. if we encounter 1 we simply increment mid but if we find 2 we swap it with arr[high] and do high-- (mid++ is not done
because the swapped arr[high] value might be 0 so we but check it also). When traversing and doing the opeartions the moment mid crosses high
the two zones mid-high and high+1 - end overlap so the whole array is sorted. 
*/
void sortColors(vector<int>& nums) {
    int n = nums.size();
    int low=0, mid=0, high=n-1;
    while (mid <= high){
        if (nums[mid] == 0){
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if(nums[mid] == 1) mid++;
        else {
            swap(nums[high], nums[mid]);
            high--;
        }
    }
}

int main() {
    vector<int> arr = {0,1,2,0,2,1,0,2,1,0,1,1,1,0,2,2,0};
    sort012(arr);
    for(int x : arr) cout << x << " ";
    return 0;
}