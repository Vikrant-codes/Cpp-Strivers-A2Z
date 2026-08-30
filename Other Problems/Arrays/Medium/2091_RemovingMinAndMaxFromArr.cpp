/*
Leetcode - 2091. Removing Minimum and Maximum From Array : Medium

You are given a 0-indexed array of distinct integers nums.
There is an element in nums that has the lowest value and an element that has the highest value. 
We call them the minimum and maximum respectively. Your goal is to remove both these elements from the array.

A deletion is defined as either removing an element from the front of the array or 
removing an element from the back of the array.

Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.

Examples :-

Input: nums = [2,10,7,5,4,1,8,6] __ Output: 5
Explanation: 
The minimum element in the array is nums[5], which is 1.
The maximum element in the array is nums[1], which is 10.
We can remove both the minimum and maximum by removing 2 elements from the front and 3 elements from the back.
This results in 2 + 3 = 5 deletions, which is the minimum number possible.

Input: nums = [0,-4,19,1,8,-2,-3,5] __ Output: 3
Explanation: 
The minimum element in the array is nums[1], which is -4.
The maximum element in the array is nums[2], which is 19.
We can remove both the minimum and maximum by removing 3 elements from the front.
This results in only 3 deletions, which is the minimum number possible.

Input: nums = [101] __ Output: 1
Explanation:  
There is only one element in the array, which makes it both the minimum and maximum element.
We can remove it with 1 deletion.

Constraints :-
• 1 <= nums.length <= 10^5
• -10^5 <= nums[i] <= 10^5
• The integers in nums are distinct.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)

int minimumDeletions(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) return 1;
    
    int maxInd = 0, minInd = 0;
    
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[maxInd]) 
            maxInd = i;
        else if (nums[i] < nums[minInd]) 
            minInd = i;
    }

    int a = min(minInd, maxInd), b = max(minInd, maxInd);
    
    int bothSideRemoval = (a + 1) + (n - b);
    int leftSideRemoval = b + 1;
    int rightSideRemoval = n - a;
    
    return min(bothSideRemoval, min(leftSideRemoval, rightSideRemoval));
}


// My initial Solution
int minimumDeletionsFirstSolution(vector<int>& nums) {
    int n = nums.size();
    
    if (n == 1) return 1;
    
    int maxInd = 0, minInd = 0;
    
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[maxInd]) 
            maxInd = i;
        else if (nums[i] < nums[minInd]) 
            minInd = i;
    }

    // Case - 1 : min / max element is at the middle of an 'odd-sized' array
    int mid = n / 2;

    if (n % 2 == 1 && (minInd == mid || maxInd == mid))
        // we can remove all elements from the half which contains both min & max 
        return mid + 1;

    // Case - 2 : Both min & max lie in the same half

    // both lie in left half
    if (minInd < mid && maxInd < mid)
        // remove elements upto the max/min element from the left side
        return max(minInd + 1, maxInd + 1);
    
    // both lie in right half
    if (minInd >= mid && maxInd >= mid)
        // remove elements upto the max/min element from the right side
        return max(n - minInd, n - maxInd);

    // Case - 3 : Both lie in different halves

    // removal can be done in 3 ways:-
    // 1) Remove one element from left side (from index 0) and another one from right side (from index n-1)
    // Example case for this -> [2, 1, 3, 4, 5, 6, 8, 7], 4 removal needed (2 from both sides)
    // 2) Remove both elements from left side (from index 0)
    // Example case for this -> [2, 3, 1, 4, 8, 5, 6, 7], 5 removal needed (5 elements removed from left)
    // 3) Remove both elements from right side (from index n-1) 
    // Example case for this -> [2, 3, 4, 1, 5, 8, 6, 7], 5 removal needed (5 elements removed from right)
    
    int a = min(minInd, maxInd), b = max(minInd, maxInd);   
    // a denotes the left half element, b denotes the right half element
    
    int bothSideRemoval = a + 1 + n - b;
    int leftSideRemoval = b + 1;
    int rightSideRemoval = n - a;

    return min(bothSideRemoval, min(leftSideRemoval, rightSideRemoval));
}



int main() {
    return 0;
}