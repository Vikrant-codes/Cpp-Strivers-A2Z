/*
Leetcode - 628. Maximum Product of Three Numbers : Easy

Given an integer array nums, find three numbers whose product is maximum and return the maximum product.

Examples :-

Input: nums = [1,2,3] __ Output: 6

Input: nums = [1,2,3,4] __ Output: 24

Input: nums = [-1,-2,-3] __ Output: -6

Constraints :-
• 3 <= nums.length <= 10^4
• -1000 <= nums[i] <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Approach
In general if we want to maximize the product of three numbers, 
the best choice would be to select the three largest values possible.
For an array, this would mean to choose the three largest values present in the array.
Ex- arr = [2, 1, 3, 0, 4, 2, 2, 1]
For this array, if we want to get the maximum product, we must choose the three maximum values (which are 4, 3 and 2).
Maximum product = 4 * 3 * 2 = 24

So, choosing the three maximum would work fine to get the maximum product, but the array can also have negative values as well.
These negative values might affect how we choose the three numbers.
Since, we know that the product of two negatives become positive.
Ex- arr = [2, 1, 3, 4, 0, -1, 2, -3, -3]
Now, if we consider only the three largest values, these would be 4, 3 and 2. Their product will be 24.
But, the arr also contains negative numbers like -3, -1, -3.
We choose the second largest and third largest so that they could enhance the value of first largest during product.
The product of second and third largest was 3 * 2 = 6, which then multiplied by largest (4) gave 24.
But, for the current array, if we choose -3 and -3, their product will be 9, 
which is greater than the product of second & third largest.
So, instead of choosing 4, 3 & 2 (product = 24), the optimal numbers for this array would be 4, -3 & -3 (product = 36).
We need the largest value in both cases.

so, we just need to track the first & second minimum along with first, second & third largest.
Assume, min1 = firstMinimum, min2 = secondMinimum, max1 = firstMaximum, max2 = secondMaximum, max3 = thirdMaximum

Now, we need to consider the triplets {max1, max2, max3} and {max1, min1, min2}, and choose the one with the maximum product.
*/

// Using Sorting : Time Complexity : O(n log n) __ Space Complexity : O(1)
// Sort the array to easily get the firstMax, secondMax, thirdMax, firstMin and secondMin.
int maximumProduct(vector<int>& nums) {
    int n = nums.size();

    sort(nums.begin(), nums.end());
    
    int max1 = nums[n-1], max2 = nums[n-2], max3 = nums[n-3];
    int min1 = nums[0], min2 = nums[1];
    
    return max(max1 * max2 * max3, max1 * min1 * min2);
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
// Find the firstMax, secondMax, thirdMax, firstMin and secondMin in single traversal of array
int maximumProduct(vector<int>& nums) {
    int n = nums.size();

    int max1 = -9999, max2 = -9999, max3 = -9999;
    int min1 = 9999, min2 = 9999;
    
    for (int& x : nums) {
        if (x > max1) {
            max3 = max2;
            max2 = max1;
            max1 = x;
        }
        else if (x > max2) {
            max3 = max2;
            max2 = x;
        }
        else if (x > max3) {
            max3 = x;
        }
        if (x < min1) {
            min2 = min1;
            min1 = x;
        }
        else if (x < min2) {
            min2 = x;
        }
    }

    return max(max1 * max2 * max3, max1 * min1 * min2);
}

int main() {
    return 0;
}