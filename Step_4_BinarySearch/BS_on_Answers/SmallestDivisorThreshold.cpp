/*
Leetcode - 1283. Find the Smallest Divisor Given a Threshold -- Medium

Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, 
and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.
Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).
The test cases are generated so that there will be an answer.

Examples :- 

Input: nums = [1,2,5,9], threshold = 6 __ Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 

Input: nums = [44,22,33,11,1], threshold = 5 __ Output: 44

Constraints :- 1 <= nums.length <= 5 * 10^4 __ 1 <= nums[i] <= 10^6 __ nums.length <= threshold <= 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Binary Search
// Time Complexity: O(n * log(max(nums))) where n is the size of nums

int findMax(vector<int>& nums) {
    int mx = 0;
    for(int n : nums) mx = max(mx, n);
    return mx;
}

/*
divideArr function calculates the sum of the division results of each element in nums by x.
If an element is divisible by x, it divides evenly; otherwise, it rounds up to the next integer.
This is done using the formula (n % x == 0) ? (n / x) : (n / x + 1). Since if n is not totally divisible by x, we need to round up so we add 1.
*/
int divideArr(vector<int>& nums, int x) {
    int sum = 0;
    for(int n : nums) {
        int div = (n % x == 0) ? (n / x) : (n / x + 1);
        sum += div;
    }
    return sum;
}

/*
Approach :- 
Start search space with low = 1 and high = max(nums). Find mid and calculate the sum of the division results using divideArr function. 
If the sum is less than or equal to threshold, it means we can try a smaller divisor, so we move high to mid - 1.
If the sum is greater than threshold, we need a larger divisor, so we move low to mid + 1.
If low exceeds high, the searching ends and the smallest divisor is found at low.
*/
int smallestDivisor(vector<int>& nums, int threshold) {
    // it's given that there is always a solution but if that was not the case then the condition to check for impossible would have been
    // if (nums.size() > threshold) return -1;
    // this condition is because the max sum after dividing by the max(arr) would have been nums.size() and if that's > threshold, no solution exist

    int low = 1;
    int high = findMax(nums);
    while(low <= high) {
        int mid = low + (high - low) / 2;
        int res = divideArr(nums, mid);
        if(res <= threshold) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;
    int smd = smallestDivisor(nums, threshold);
    cout << "Smallest Divisor: " << smd << endl;

    return 0;
}