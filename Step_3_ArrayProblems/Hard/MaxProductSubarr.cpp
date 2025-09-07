/*
Leetcode - 152. Maximum Product Subarray

Given an integer array nums, find a subarray that has the largest product, and return the product.
The test cases are generated so that the answer will fit in a 32-bit integer.

Example 1:- Input: nums = [2,3,-2,4] __ Output: 6
Example 2:- Input: nums = [-2,0,-1] __ Output: 0
Example 3:- Input: nums = [-2,3,-1,4,0,1,2,3,-5,0,-1,-2,-4,-5] __ Output: 40

Constraints:
-> 1 <= nums.length <= 2 * 104
-> -10 <= nums[i] <= 10
-> The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(n * 2) __ Space Complexity : O(1)
int maxProdductBrute(vector<int> arr) {
    int maxProd = INT_MIN;
    int n = arr.size();
    for(int i=0; i<n; i++) {
        int pro = 1;
        for(int j=i; j<n; j++) {
            pro *= arr[j];
            maxProd = max(maxProd, pro);
        }
    }
    return maxProd;
}

// Optimal Approach 1 (observation based approach) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Observations :- 
<1> If there are no negative numbers or even number of negative numbers, then the max. product is the product of all numbers.
<2> If there are odd number of negative numbers, then the max. product is determined by excluding one of the negative numbers so that the 
product remains positive. No matter which negative number we exclude, the answer will either be the product of all numbers 
to the right of excluded negative number (prefix of the excluded negative number) or the product of all numbers
to the left of excluded negative number (suffix of the excluded negative number).
Example : [-2,3,-1,4,2,-3,5] Here there are 3 -ve numbers and any of them can be excluded. 
If -2 is excluded we get prefix = [], suffix = [3,-1,4,2,-3,5] __ product_prefix = _ , product_suffix = 360
If -1 is excluded we get prefix = [-2,3], suffix = [4,2,-3,5] __ product_prefix = -6, product_suffix = 120
If -3 is excluded we get prefix = [-2,3,-1,4,2], suffix = [5] __ product_prefix = 48, product_suffix = 5
So the answer is max(360, -6, 120, 48, 5) = 360. 
Thus we observe that we can calculate the product of all numbers in the array one from start and one from end and then keep track of the maximum product.
<3> If there are zeros in the array, we know that the product will become zero if included in the answer subarr so we simply treat the whole array as
different arrays separated by zeros and calculate the max product for each of them. This is done by resetting the prefix and suffix products to 1 
whenever a 0 is encountered. 
Example : [-2,3,-1,4,0,1,2,3,-5,0,-1,-2,-4,-5] __ the arrays considered are [-2,3,-1,4], [1,2,3,-5], [-1,-2,-4,-5] and 
we calculate the max product by keeping track of the prefix and suffix products as we traverse the array and reset them to 1 whenever a 0 is encountered.

Approach : 
Initialize two variables pre and suf to 1. Traverse the array from start and end simultaneously, multiplying the elements to pre and suf respectively.
Update the maximum product found so far with the maximum of pre and suf at each step. If a zero is encountered such that pre or suf becomes zero, reset 
that to 1 to consider a different subarray. Finally return the maximum product found. 
*/
int maxProdduct1(vector<int> nums) {
    int n = nums.size();
    int pre = 1;
    int suf = 1;
    int ans = INT_MIN;
    for(int i=0; i<n; i++) {
        pre *= nums[i];
        suf *= nums[n-i-1];
        ans = max(ans, max(pre, suf));
        if (pre == 0) pre = 1;      // Reset pre to 1 if it becomes zero
        if (suf == 0) suf = 1;      // Reset suf to 1 if it becomes zero
    }
    return ans;
}

// Optimal Approach 2 (Using Modified Kadane's Algorithm) : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :-
For maximum sum subarray, Kadane’s Algorithm works by tracking the max sum at each point. But with products, we face 3 special challenges:
1. Negative numbers: Multiplying by a negative can flip a large positive to negative, or a large negative to a positive.
2. Zero: A zero resets the product, so you may need to start over from the next index.
3. Alternating signs: Two negatives can make a big positive. But to know that, you must remember the smallest (most negative) product so far.

💡 Key Insight:-
At every index, we must keep track of two values:
> maxProd: the maximum product ending at this index
> minProd: the minimum product ending at this index

Why both?
> If nums[i] is positive: maxProd becomes even bigger. minProd stays small or resets.
> If nums[i] is negative: The maximum might come from multiplying this negative with a previous minimum. So we swap maxProd and minProd before updating.
> If nums[i] is zero: Both maxProd and minProd reset to zero. 

This reseting to zero is done as :- If current element is zero then maxProd = max (0, maxProd * 0) = 0 and minProd = min (0, minProd * 0) = 0. 
Now when next element is encountered the maxProd and minProd are refreshed accordingly. 
*/

int maxProdduct2(vector<int> arr) {
    int n = arr.size();
    int maxProd = arr[0];
    int minProd = arr[0];
    int ans = arr[0];
    for(int i=1; i<n; i++) {
        if (arr[i] < 0) {
            swap(maxProd, minProd);
        }
        maxProd = max(arr[i], maxProd * arr[i]);
        minProd = min(arr[i], minProd * arr[i]);
        ans = max(ans, maxProd);
    }
    return ans;
}

int main() {
    vector<int> arr = {-2,3,-1,4,0,1,2,3,-5,0,-1,-2,-4,-5};
    int res = maxProdduct2(arr);
    cout << res;
}