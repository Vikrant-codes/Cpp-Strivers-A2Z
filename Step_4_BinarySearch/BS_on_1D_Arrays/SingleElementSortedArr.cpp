/*
Leetcode - 540. Single Element in a Sorted Array -- Medium

You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
Return the single element that appears only once.
Your solution must run in O(log n) time and O(1) space.

Examples :- 

Input: nums = [1,1,2,3,3,4,4,8,8] __ Output: 2
Input: nums = [3,3,7,7,10,11,11] __ Output: 10

Constraints :- 1 <= nums.length <= 10^5 __ 0 <= nums[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) __ Space Complexity: O(1)

/*
My approach :- x denotes the first element and cnt denotes its count. While traversing if the current element is equal to x increase the count. 
If it's not equal then check if the count of x is equal to 1 if yes then it's the single element. If its count was not equal to two that means it's 
not single appearing so we update x to the new element and check for its count. 

Striver's approach :- For each element we check its adjacent elements. The element which is not equal to both of the adjacent right & left elements is 
the single element so return it.

XOR approach :- We can do XOR of all the elements in the array and the result will be the single appearing element.
*/
int singleElement(vector<int>& nums) {
    int x = nums[0];
    int cnt = 1;
    for(int i=1; i<nums.size(); i++) {
        if (nums[i] == x) cnt++;
        else {
            if (cnt == 1) return x; // if count is 1 then return the single element
            x = nums[i]; // update x to the new element
            cnt = 1; // reset count for the new element
        }
    }
    return x; // if the last element is the single one, return it
}

int singleElementStriver(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0]; // if only one element is present, return it

    for(int i=0; i<n; i++) {
        // If element is at first index, then check for only the right element to it since there is no previous element
        if (i == 0) {
            if (nums[i] != nums[i + 1]) return nums[i];
        }
        // If element is at last index, then check for only the left element to it since there is no next element
        else if (i == n - 1) {
            if (nums[i] != nums[i - 1]) return nums[i];
        }
        else {
            // if current element is not equal to both adjacent elements, return it
            if (nums[i] != nums[i - 1] && nums[i] != nums[i + 1]) return nums[i]; 
        }
    }
    return -1; // this line should never be reached if input is valid
}

int singleElementXOR(vector<int>& nums) {
    int result = 0;
    for(int num : nums) {
        result ^= num; // XOR all elements
    }
    return result; // the result will be the single appearing element
}

// Optimal Approach 
/*
Approach :- 
We know that the array is sorted and we can use binary search methodology but how do we apply it here ?

Since every element appears exactly twice except for one we can get an idea of index parity. 
The index parity of first & second appearance of an element must be like 0-1, 2-3, 4-5, ... but due to single element this pattern breaks.
This index parity is in pattern of odd - even indices so first duplicate is at even index and the second duplicate is at odd index. 
But when the single appearing element comes this even - odd pattern breaks to odd - even. 
Find the mid element and check for its index parity. Now there can be two cases :- 
1. The mid element itself is single appearing element then return it.
2. The mid element is not single appearing element then we check for its duplicate index.

For this we have two cases :- 
a) If the mid element forms even - odd index pair with its duplicate then we can certainly say that the single appearing element is on the right 
side of the mid element and thus we can ignore the left side (or we decrease the size of search space by doing low = mid + 1).
b) If the mid element forms odd - even index pair with its duplicate this means that the single appearing element is on the left side of the mid 
element so this time we will reduce the search space from the right side (i.e. by doing high = mid - 1). 

Now the problem is how do we check for the index parity of mid element. Its quite simple, we check if mid is even or odd. 
1. If mid is even :- 
1. a) If nums[mid] == nums[mid + 1] then it's even - odd index pair so we ignore the left side i.e. do low = mid + 1.
1. b) If nums[mid] == nums[mid - 1] then it's odd - even index pair so we ignore the right side i.e. do high = mid - 1.

2. If mid is odd :- 
2. a) If nums[mid] == nums[mid + 1] then it's odd - even index pair so we ignore the right side i.e. do high = mid - 1.  
2. b) If nums[mid] == nums[mid - 1] then it's even - odd index pair so we ignore the left side i.e. do low = mid + 1.
 
*/
int singleNonDuplicate(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int evenodd = 0, oddeven = 0;  // flags to check index parity: evenodd denotes even-odd, oddeven denotes odd-even
        // if mid is the first element then check its parity only with the right element
        if (mid == 0) {
            if (nums[mid] == nums[mid] + 1) evenodd = 1;
        }
        // if mid is the last element then check its parity only with the left element
        else if (mid == nums.size() - 1) {
            if (nums[mid] == nums[mid] - 1) oddeven = 1;
        }
        else {
            // conditions for even-odd index pair 
            if ((mid % 2 == 0 && nums[mid] == nums[mid + 1]) || (mid % 2 != 0 && nums[mid] == nums[mid - 1])) {
                evenodd = 1; // even-odd index pair
                low = mid + 1;  // ignore left side
            }
            // conditions for odd-even index pair
            else {
                oddeven = 1; // odd-even index pair
                high = mid - 1;  // ignore right side
            }
        }
        if (evenodd == 0 && oddeven == 0) {
            return nums[mid]; // found the single element
        }
    }
    return -1; // this line should never be reached if input is valid
}

/*
Striver's Approach :- His approach and basic idea is same as mine but his code is more organised and readable than mine. Checking the duplicates 
for the first element (nums[0]) and last element (nums[n-1]) was problematic and needed conditionals in my code but here these are checked beforehand. 
During the mid calculation and in the while loop these first and last elements were problematic due to edge cases so we check for them outside of loop 
and start our search space with index 1 to index (n-2) i.e. low = 1 and high = n - 2. This is done since we have checked for last and first element 
before the loop itself. Also since edge cases are handled before the loop, we can directly check for mid element's parity without worrying about the 
first and last elements. Also there is no need to use oddeven or evenodd flags since we can directly check the mid element's parity and consider cases 
for skipping the left or right side of the search space.
*/
int singleNonDuplicateStriver(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    if (nums[0] != nums[1]) return nums[0];
    if (nums[n-1] != nums[n-2]) return nums[n-1];

    int low = 1, high = n-2;
    while (low <= high) {
        int mid = (low + high) / 2;
        
        //if nums[mid] is the single element
        if (nums[mid] != nums[mid + 1] && nums[mid] != nums[mid - 1]) {
            return nums[mid];
        }

        if ((mid % 2 == 0 && nums[mid] == nums[mid+1]) || (mid % 2 == 1 && nums[mid] == nums[mid-1])) {
            low = mid + 1;              //eliminate the left half
        }
        else {
            high = mid - 1;             //eliminate the right half
        }
    }
    return -1;                  // won't execute if input is valid
}

int main() {
    vector<int> nums = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 8, 8, 9, 10, 10};
    cout << "Single element in the sorted array: " << singleNonDuplicate(nums) << endl;

    return 0;
}