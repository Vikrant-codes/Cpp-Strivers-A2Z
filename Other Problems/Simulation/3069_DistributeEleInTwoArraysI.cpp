/*
Leetcode - 3069. Distribute Elements Into Two Arrays I : Easy

You are given a 1-indexed array of distinct integers nums of length n.

You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. 
In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. 
Afterwards, in the ith operation:
- If the last element of arr1 is greater than the last element of arr2, append nums[i] to arr1. 
    Otherwise, append nums[i] to arr2.
- The array result is formed by concatenating the arrays arr1 and arr2. 
    For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].

Return the array result. 

Examples :-

Input: nums = [2,1,3] __ Output: [2,3,1]
Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
In the 3rd operation, as the last element of arr1 is greater than the last element of arr2 (2 > 1), append nums[3] to arr1.
After 3 operations, arr1 = [2,3] and arr2 = [1].
Hence, the array result formed by concatenation is [2,3,1].

Input: nums = [5,4,3,8] __ Output: [5,3,4,8]
Explanation: After the first 2 operations, arr1 = [5] and arr2 = [4].
In the 3rd operation, as the last element of arr1 is greater than the last element of arr2 (5 > 4), append nums[3] to arr1, hence arr1 becomes [5,3].
In the 4th operation, as the last element of arr2 is greater than the last element of arr1 (4 > 3), append nums[4] to arr2, hence arr2 becomes [4,8].
After 4 operations, arr1 = [5,3] and arr2 = [4,8].
Hence, the array result formed by concatenation is [5,3,4,8].

Constraints :-
• 3 <= n <= 50
• 1 <= nums[i] <= 100
• All elements in nums are distinct.
*/

#include<bits/stdc++.h>
using namespace std;

// Approach-1 (Two List Simulation) : Time Complexity : O(n) __ Space Complexity : O()
/*
>> Intuition
We can simulate the process described in the problem statement. 
Initialize two lists, arr1 and arr2​, and add nums[0] and nums[1] to them, respectively.

Then, starting from i=2, traverse the array nums and compare the last elements of arr1 & arr2:
If the last element of arr1 is greater than the last element of arr2, append nums[i] to arr1.
Otherwise, append nums[i] to arr2.

After traversing the array, concatenate arr2 to the end of arr1 and return the resulting array.

>> Complexity Analysis
Let n be the length of the array nums.

-> Time complexity: O(n).
We traverse the array once, with each comparison and insertion taking O(1) time. 
Concatenating the two lists also takes O(n) time.

-> Space complexity: O(n).
The two lists together contain all n elements of the array.
*/
vector<int> resultArraySimulation(vector<int>& nums) {
    int n = nums.size();

    vector<int> arr1, arr2;
    arr1.push_back(nums[0]);
    arr2.push_back(nums[1]);
    
    for (int i = 2; i < n; i++) {
        if (arr1.back() > arr2.back()) {
            arr1.push_back(nums[i]);
        } else {
            arr2.push_back(nums[i]);
        }
    }

    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    
    return arr1;
}

// Approach-2 (Single Array with Two Pointers) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
We can perform the allocation using only one array arr. 
Place nums[0] at the beginning of arr, corresponding to the first element of arr1, 
and place nums[1] at the end of arr, corresponding to the first element of arr2.

We use two pointers, idx and revIdx, to represent the positions of the last elements of arr1 and arr2, respectively.
We then iterate over the remaining elements of nums and compare arr[idx] with arr[revIdx]:
- If arr[idx] > arr[revIdx], place the current element at the next position of idx, 
    namely idx + 1, and then move idx one position to the right.
- Otherwise, place the current element at the previous position of revIdx, 
    namely revIdx−1, and then move revIdx one position to the left.

After the traversal, arr[0..idx] contains arr1, while arr[revIdx..n−1] contains arr2. 
Since the elements of arr2 are stored from right to left, their order is reversed. 
Therefore, we reverse arr[revIdx..n−1] to restore the correct order.

>> Complexity Analysis
Let n be the length of the array nums.

-> Time complexity: O(n).
We traverse the array in O(n) time and reverse part of the array in O(n) time. 
Therefore, the overall time complexity is O(n).

-> Space complexity: O(1).
Apart from the output array itself, we only use a constant number of additional variables, 
so the extra space complexity is O(1).
*/
vector<int> resultArray(vector<int>& nums) {
    int n = nums.size();

    vector<int> arr(n);
    arr[0] = nums[0];
    arr[n-1] = nums[1];

    int idx = 0, revIdx = n - 1;
    for (int i = 2; i < n; i++) {
        if (arr[idx] > arr[revIdx])
            arr[++idx] = nums[i];
        else
            arr[--revIdx] = nums[i];
    }

    reverse(arr.begin() + revIdx, arr.end());
        
    return arr;
}

int main(){
    return 0;
}