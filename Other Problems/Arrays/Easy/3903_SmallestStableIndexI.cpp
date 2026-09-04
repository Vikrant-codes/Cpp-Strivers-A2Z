/*
Leetcode - 3903. Smallest Stable Index I : Easy

You are given an integer array nums of length n and an integer k.
For each index i, define its instability score as max(nums[0..i]) - min(nums[i..n - 1]).

In other words:
• max(nums[0..i]) is the largest value among the elements from index 0 to index i.
• min(nums[i..n - 1]) is the smallest value among the elements from index i to index n - 1.

An index i is called stable if its instability score is less than or equal to k.

Return the smallest stable index. If no such index exists, return -1.

Examples :-

Input: nums = [5,0,1,4], k = 3
Output: 3
Explanation:
At index 0: The maximum in [5] is 5, and the minimum in [5, 0, 1, 4] is 0, so the instability score is 5 - 0 = 5.
At index 1: The maximum in [5, 0] is 5, and the minimum in [0, 1, 4] is 0, so the instability score is 5 - 0 = 5.
At index 2: The maximum in [5, 0, 1] is 5, and the minimum in [1, 4] is 1, so the instability score is 5 - 1 = 4.
At index 3: The maximum in [5, 0, 1, 4] is 5, and the minimum in [4] is 4, so the instability score is 5 - 4 = 1.
This is the first index with an instability score less than or equal to k = 3. Thus, the answer is 3.

Input: nums = [3,2,1], k = 1
Output: -1
Explanation:
At index 0, the instability score is 3 - 1 = 2.
At index 1, the instability score is 3 - 1 = 2.
At index 2, the instability score is 3 - 1 = 2.
None of these values is less than or equal to k = 1, so the answer is -1.

Input: nums = [0], k = 0
Output: 0
Explanation:
At index 0, the instability score is 0 - 0 = 0, which is less than or equal to k = 0. Therefore, the answer is 0.

Constraints :-
• 1 <= nums.length <= 100
• 0 <= nums[i] <= 10^9
• 0 <= k <= 10^9
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach
int getMax(vector<int>& nums, int s, int e) {
    int ans = -1;       // nums[i] is always +ve, so we can initialize max_ans with -1
    for (int i = s; i <= e; i++)
        if (nums[i] > ans)
            ans = nums[i];
    return ans;
}

int getMin(vector<int>& nums, int s, int e) {
    int ans = INT_MAX;
    for (int i = s; i <= e; i++) 
        if (nums[i] < ans)
            ans = nums[i];
    return ans;
}

int firstStableIndex1(vector<int>& nums, int k) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        int mx = getMax(nums, 0, i);
        int mn = getMin(nums, i, n-1);
        int score = mx - mn;
        if (score <= k)
            return i;
    }

    return -1;
}

// Better Approach (Running Max + find minimum)
int firstStableIndex2(vector<int>& nums, int k) {
    int n = nums.size();

    int mx = -1;
    
    for (int i = 0; i < n; i++) {
        if (mx < nums[i]) 
            mx = nums[i];
        int mn = getMin(nums, i, n-1);
        int score = mx - mn;
        if (score <= k)
            return i;
    }

    return -1;
}

// Optimal Approach (Running Max + SuffixMinArray)

int firstStableIndex3(vector<int>& nums, int k) {
    int n = nums.size();

    // use an array suffixMin where suffixMin[i] gives the min. element in range [i, n-1]
    vector<int> suffixMin(n);
    int mn = INT_MAX;
    for (int i = n-1; i >= 0; i--) {
        mn = min(mn, nums[i]);
        suffixMin[i] = mn;
    }

    int mx = -1;
    for (int i = 0; i < n; i++) {
        mx = max(mx, nums[i]);
        mn = suffixMin[i];
        int score = mx - mn;
        if (score <= k)
            return i;
    }
    return -1;
}


int firstStableIndex(vector<int>& nums, int k) {
    int n = nums.size();

    vector<int> suffixMin(n);
    
    int mn = nums[n-1];
    for (int i = n - 1; i >= 0; i--) {
        mn = min(nums[i], mn);
        suffixMin[i] = mn;
    }
    
    int mx = nums[0];

    for (int i = 0; i < n; i++) {
        mx = max(nums[i], mx);
        if (mx - suffixMin[i] <= k) 
            return i;
    }
    
    return -1;
}

int main() {
    return 0;
}