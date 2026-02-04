/*
Leetcode - 2965. Find Missing and Repeated Values : Easy

You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n^2]. 
Each integer appears exactly once except a which appears twice and b which is missing. 
The task is to find the repeating and missing numbers a and b.

Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.

Examples :-

Input: grid = [[1,3],[2,2]] __ Output: [2,4]
Explanation: Number 2 is repeated and number 4 is missing so the answer is [2,4].

Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: Number 9 is repeated and number 5 is missing so the answer is [9,5].

Constraints :-
- 2 <= n == grid.length == grid[i].length <= 50
- 1 <= grid[i][j] <= n * n
- For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid members.
- For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of the grid members.
- For all x that 1 <= x <= n * n except two of them there is exactly one pair of i, j that 0 <= i, j <= n - 1 and grid[i][j] == x.

" This problem is similar to Leetcode - '645. Set Mismatch' and same logic is used to solve both problems. "
*/

#include <bits/stdc++.h>
using namespace std;

// HashArray Approach : Time Complexity : O(m) __ Space Complexity : O(m) , where m = n*n = grid_size 
vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<int> hashArr(n * n);
    vector<int> ans(2);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            hashArr[grid[i][j] - 1]++;

    for (int i = 0; i < hashArr.size(); i++) {
        // missing number
        if (hashArr[i] == 0)
            ans[1] = i+1;
        else if (hashArr[i] == 2)
            ans[0] = i+1;
    }

    return ans;
}

// Optimal Approach : Time Complexity : O(m) __ Space Complexity : O(1)
// See Leetcode - '645. Set Mismatch' for the explanation
vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    int n = grid.size();
    int s = n * n;              // Total no. of elements in the grid

    int sum = 0;
    long long sqSum = 0;
    for (auto& row: grid) {
        for (int& x: row) {
            sum += x;
            sqSum += x*x;
        }
    }

    int exp_sum = ( s * (s + 1) ) / 2;
    long long exp_sqSum = (1LL * s * (s + 1) * (2*s + 1) ) / 6;

    int p = sum - exp_sum;                // Repeated - Missing
    long long q = sqSum - exp_sqSum;      // Repeated ^ 2 - Missing ^ 2
    int r = q / p;                        // Repeated + Missing

    int x = (p + r) / 2;                  // repeated
    int y = x - p;                        // missing

    return {x, y};
}

int main() {

    return 0;
}