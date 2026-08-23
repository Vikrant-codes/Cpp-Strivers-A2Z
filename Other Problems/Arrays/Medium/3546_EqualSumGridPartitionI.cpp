/*
Leetcode - 3546. Equal Sum Grid Partition I : Medium

You are given an m x n matrix grid of positive integers. 
Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
- Each of the two resulting sections formed by the cut is non-empty.
- The sum of the elements in both sections is equal.

Return true if such a partition exists; otherwise return false.

Examples :-

Input: grid = [[1,4],[2,3]] __ Output: true
Explanation:
A horizontal cut between row 0 and row 1 results in two non-empty sections, 
each with a sum of 5. Thus, the answer is true.

Input: grid = [[1,3],[2,4]] __ Output: false
Explanation:
No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is false. 

Constraints :-
• 1 <= m == grid.length <= 10^5
• 1 <= n == grid[i].length <= 10^5
• 2 <= m * n <= 10^5
• 1 <= grid[i][j] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach : Time Complexity : O(3mn) __ Space Complexity : O(1)
/*
>> Intuition
We want to check if it is possible to make a horizontal / vertical cut such that the resulting sections are of same sum.
Suppose the grid has `m` rows and `n` columns.

Now, If we make a horizontal cut between rows 'r' & 'r+1', then it would divide the grid into two grid sub-sections:
sections of rows: [0 ... r] and [r+1 ... m-1].
We need to check if it possible to make a horizontal cut such that the resulting sections are of same sum.
We can try to check this for all possible horizontal cuts.
To do so efficiently, we can firstly calculate the sum of the whole grid. Lets store it in some variable `totalSum`.
Now, we maintain a sum variable which will store the sum of rows while traversing, 
and we traverse each row add it elements to sum and check if we can make the horizontal cut after this row?
At the ith row, we know the sum of section of rows [0 ... i], which is stored in our sum variable.
The sum of the second section (which is rows [i+1 ... m-1]) can be calculated as totalSum - sum.
Now, if these two sums are equal, it means we can make a horizontal cut after this ith row, so we can simply return true.

Similarly, we can also check for vertical cut, by traversing column by column
adding elements of entire column to the sum, and checking if the current sum = totalSum - sum.
*/
bool canPartitionGrid(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    long long totalSum = 0;
    for (vector<int>& row: grid)
        for (int& ele: row)
            totalSum += ele;
    
    // check for horizontal cut
    // traverse the grid row-wise, calculate sum and check if sum of two sections is equal
    long long sum = 0;
    for (vector<int>& row: grid) {
        for (int& ele: row) 
            sum += ele;

        if (sum == totalSum - sum) 
            return true;
    }
    
    // check for vertical cut
    // traverse the grid column-wise, calculate sum and check if sum of two sections is equal
    sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) 
            sum += grid[j][i];

        if (sum == totalSum - sum) 
            return true;  
    }

    return false;
}

int main() {
    return 0;
}