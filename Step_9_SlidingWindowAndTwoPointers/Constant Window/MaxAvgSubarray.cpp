/*
Leetcode - 643. Maximum Average Subarray I : Easy

You are given an integer array nums consisting of n elements, and an integer k.
Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. 
Any answer with a calculation error less than 10-5 will be accepted.

Examples :-

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

Input: nums = [5], k = 1
Output: 5.00000

Constraints :-
• n == nums.length
• 1 <= k <= n <= 10^5
• -10^4 <= nums[i] <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Key Observation
Since k is fixed and we want to maximize the average, 
we can simply try to find the subarray with the maximum sum and 
then divide that maximum sum by k to obtain the maximum average.

This is because all candidate subarrays have the same length (k), 
so maximizing their sum is equivalent to maximizing their average.
*/

// Brute Force Approach: Time Complexity : O(n x k) __ Space Complexity : O(1)
/*
>> Intuition 
We can consider every possible subarray of size k and calculate its sum. 
For each starting index, iterate through the next k elements and calculate their sum. 
Maintain the maximum sum encountered across all possible windows.
Finally, divide the maximum sum by k to obtain the maximum average.

>> Complexity Analysis
- Time Complexity: O(n x k) — For every possible starting index, we calculate the sum of k elements.
- Space Complexity: O(1) — Only a constant number of variables are used.
*/
double findMaxAverageBrute(vector<int>& nums, int k) {
    int n = nums.size();
    int maxi = INT_MIN;

    for(int i = 0; i <= n - k; i++) {
        int sum = 0;

        for(int j = i; j < i + k; j++) {
            sum += nums[j];
        }

        maxi = max(maxi, sum);
    }

    return (double)maxi / k;
}

// Optimal (Fixed-Size Sliding Window _ Two Pointers): Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Intuition
We can maintain a fixed-sized window of k elements and calculate its sum. 
Since we want the maximum average, we maintain the maximum window sum (maxi) encountered so far.

Instead of recalculating the sum whenever the window moves, 
we can efficiently obtain the current window's sum by considering the elements entering and leaving the window. 
When we slide the window one position to the right, we add the newly included element (nums[r]) 
and subtract the element that is no longer part of the window (nums[l]). 
We then update maxi with the current window sum and continue sliding until all possible windows have been considered.

Finally, divide the maximum sum by k to get the maximum average.

>> Complexity Analysis:
- Time Complexity: O(n) — Both pointers traverse the array at most once.
- Space Complexity: O(1) — Only a constant number of variables are used.
*/

double findMaxAverage1(vector<int>& nums, int k) {
    int n = nums.size();

    int sum = 0;
    
    for (int i = 0; i < k; i++) 
        sum += nums[i];
    
    int maxSum = sum;
    int i = 0;

    for (int j = k; j < n; j++) {
        sum = sum - nums[i] + nums[j];
        i++;

        if (sum > maxSum)
            maxSum = sum;
    }

    return (double (maxSum) / k);
}

double findMaxAverage2(vector<int>& nums, int k) {
    int n = nums.size();

    int l = 0, r = 0;
    int sum = 0, maxi = INT_MIN;

    while(r < n) {
        sum += nums[r];

        if(r - l + 1 == k) {
            maxi = max(maxi, sum);

            sum -= nums[l];
            l++;
        }

        r++;
    }

    return (double)maxi / k;
}

double findMaxAverage3(vector<int>& nums, int k) {
    int n = nums.size();

    // Sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++)
        windowSum += nums[i];
    
    int maxSum = windowSum;     // Max window sum (max subarry sum of size k)

    for (int i = k; i < n; i++) {
        // Add the new element & remove the element leaving the window
        windowSum += nums[i] - nums[i-k];

        maxSum = max(maxSum, windowSum);
    }

    return (double (maxSum) / k);
}

int main() {
    return 0;
}