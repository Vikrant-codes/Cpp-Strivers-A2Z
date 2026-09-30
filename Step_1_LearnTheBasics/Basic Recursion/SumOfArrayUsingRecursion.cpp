/*
TUF - 897. Sum of Array Elements II

Given an array nums, find the sum of elements of array using recursion.

Examples :-

Input : nums = [1, 2, 3] __ Output : 6
Explanation : The sum of elements of array is 1 + 2 + 3 => 6.

Input : nums = [5, 8, 1] __ Output : 14
Explanation : The sum of elements of array is 5 + 8 + 1 => 14.

Constraints :-
• 1 <= n <= 100
• 0 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Helper method : returns the sum of array from index ind to end -- [Using parameterized recursion]
int getSum(vector<int>& nums, int ind, int sum) {
    if (ind == nums.size()) {
        return sum;
    }

    return getSum(nums, ind + 1, sum + nums[ind]);
}

// Helper method : returns the sum of array from index ind to end -- [Using functional recursion]
int getSum(vector<int>& nums, int ind) {
    if (ind == nums.size()) {
        return 0;
    }
    
    return nums[ind] + getSum(nums, ind + 1);
}

int arraySum(vector<int>& nums){
	// return getSum(nums, 0, 0);
    return getSum(nums, 0);
}

int main() {
    return 0;
}