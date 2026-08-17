// Check if there exists a subsequence with sum K
/*
Problem Statement: 
Given an array nums and an integer k. 
Return true if there exist subsequences such that the sum of all elements in subsequences is equal to k else false.
*/

// GFG - Subsequence with Sum K
/*
GFG - Subsequence with Sum K : Medium

Given an array arr and target sum k, 
check whether there exists a subsequence such that the sum of all elements in the subsequence equals to k.

Examples :-

Input: arr = [10, 1, 2, 7, 6, 1, 5], k = 8.
Output: true
Explanation: Subsequences like [2, 6], [1, 7] sum upto 8

Input: arr = [2, 3, 5, 7, 9], k = 100. 
Output: false
Explanation: No subsequence can sum upto 100

Constraints :-
• 1 ≤ arr.length ≤ 2000
• 1 ≤ arr[i] ≤ 1000
• 1 ≤ target ≤ 2000
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach : Time Complexity : O(2^n) __ Space Complexity : O(n)
/*
The theoretical worst case time complexity is O(2^n) due to the pick/not-pick case for each element.
Although, the practical runtime complexity is lesser due to the early exit conditions that we used 
which generally do not traverse all possibilites thereby running in less than this exponential time.
But still, worst case complexity remains O(2^n).
An example of this worst case could be when the 'k' is greater than sum of whole array itself.
In that case no early exit condition will work, all subsequences will be fully traversed and no-one will return true.
*/

// recursive function to iterate all subsequences and return when a subsequence with sum k is found
bool fun(vector<int>& arr, int i, int sum, int k) {
    // Base Case: if all elements are processed, check if sum == k
    if (i == arr.size())
        return sum == k;
        
    // if sum has already become k, even if all elements are not processed, we can simply return true 
    // (considering that we don't pick any further elements)
    // this early exit works because we just want to check whether even a single subseq with sum k exists or not,
    // if we were supposed to count/find all those subsequences, then early exit can't be done
    // try considering arr = [1, 3, 2, 9, 0], k = 6 to understand why early exit won't work for all subsequences.
    if (sum == k) return true;

    // if sum exceeds k, we can return false, since sum won't be able to become k now (since array has only positives).
    // if the array had negatives as well, this early return won't work
    if (sum > k) return false;
    
    return fun(arr, i + 1, sum + arr[i], k) || fun(arr, i + 1, sum, k);

    // this one-line return statement will work same as below
    /*
    // pick the current element
    sum += arr[i];
    if (fun(arr, i+1, sum, k)) 
        return true;
    
    // not pick the current element
    sum -= arr[i];
    if (fun(arr, i+1, sum, k))
        return true;
        
    return false;
    */
}

bool checkSubsequenceSum(vector<int>& arr, int k) {
    return fun(arr, 0, 0, k);
}

// without using extra variable to maintain sum
/*
Instead of maintaining sum & k both, we can also directly manipulate k.
If current element is picked, we subtract arr[i] from k, for not pick case, we leave k as it is.
In this way, if k becomes 0, it means the current selection of elements add up to k (that is why subtracting them made k 0).
So, we can simply check for condition k == 0, instead of sum == k and no need to maintain sum.
Now, the early exit condition when the selected elements sum exceeded k, this condition changes to k < 0.
i.e., if k becomes negative, it means current selected elements have higher than k sum, so we return false
*/
bool fun2(vector<int>& arr, int i, int k) {
    if (i == arr.size())
        return k == 0;
        
    if (k == 0) return true;
    if (k < 0) return false;
    
    return fun2(arr, i + 1, k - arr[i]) || fun2(arr, i + 1, k);
}

bool checkSubsequenceSum2(vector<int>& arr, int k) {
    return fun2(arr, 0, k);
}

// What if array can have negative values as well ?
/*
The above code utilizes the constraints that the array only contains positive value, 
that is why we used the early exit condition where sum of current subsequnce exceeds k.
If array can have negative values as well, in that case this early exit condition won't work,
as even if sum > k, it can still reach k again by picking up some negative values.

The recursive implementation considering array may contain negative values as well, is:
*/
bool fun3(vector<int>& arr, int i, int k) {
    if (i == arr.size())
        return k == 0;
    
    if (k == 0) return true;
    // if (k < 0) return false;
    // this above condition won't work with negative elements

    return fun3(arr, i + 1, k - arr[i]) || fun3(arr, i + 1, k);
}

bool checkSubsequenceSum3(vector<int>& arr, int k) {
    return fun3(arr, 0, k);
}

// ⚠️ This solution is still not optimal/expected approach for the problem since it takes exponential time O(2^n)
// Due to this, the solution might give TLE on submission (may be submitted due to the early exit conditions)
// ✅ The expected approach for this problem uses DP (Dynamic Programming) concept

int main() {
    return 0;
}