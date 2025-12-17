/*
Leetcode - 1351. Count Negative Numbers in a Sorted Matrix : Easy

Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, 
return the number of negative numbers in grid.

Examples :-

Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]] __ Output: 8
Explanation: There are 8 negatives number in the matrix.

Input: grid = [[3,2],[1,0]] __ Output: 0

Constraints :-
-> m == grid.length
-> n == grid[i].length
-> 1 <= m, n <= 100
-> -100 <= grid[i][j] <= 100

Follow up: Could you find an O(n + m) solution?
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(m*n) __ Space Complexity : O(1)
// Traverse thorough the entire matrix and count the negative elements 
int countNegativesBrute(vector<vector<int>>& grid) {
    int cnt = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] < 0) cnt++;
        }
    }
    return cnt;
}

// Optimal Approach (Staircase Traversal) :- Time Complexity : O(m + n) __ Space Complexity : O(1)
/*
✅ Intuition
You’re given a matrix sorted in non-increasing order:
• Each row is sorted: left → right (big → small)
• Each column is sorted: top → bottom (big → small)

Example row: [4, 3, 2, -1] → Once you hit a negative number, everything to its right is also negative.

The key idea: 🎯 Start at the bottom-left corner → grid[m-1][0]
From this position :-
• If grid[i][j] < 0
    → You're at a negative number.
    Because the row is sorted decreasing, all values to the right are also negative.
    So you can add (n – j) negative numbers at once (count of all the elements to the right of current element).
    Then move up → negative numbers in this row are exhausted.
• Else (grid[i][j] >= 0)
    → This value is NOT negative.
    Since the row is sorted decreasing, you need to move right to find negatives.

This movement pattern ensures we count each negative only once without scanning the entire subrow/subcolumn.

📌 Why bottom-left?
• From bottom: many negatives likely are there
• From left: easiest to explore right side (continuous block of negatives)
• Movement becomes monotonic:
    • Only move up or right
    • Never revisit a cell
This is why the algorithm is O(m + n).

🧠 Algorithm
1. Let i = m - 1 (last row), j = 0 (first column)
2. While i >= 0 and j < n:
    • If grid[i][j] < 0:
        • Add (n - j) to count → All elements to the right are negative
        • Move up: i--
    • Else:
        • Move right: j++
3. Return the count.

⏱ Time Complexity : O(m + n) — Optimal
• You move at most m times upward
• And at most n times rightward
• Never revisit any cell

⏳ Space Complexity: O(1) → Only a few variables used.

✅ Summary
The approach uses a beautiful "grid walk" pattern:
• Start bottom-left
• Move up if negative (count all right-side cells)
• Move right if non-negative
• Count negatives in O(m+n)
*/
int countNegatives(vector<vector<int>>& grid) {
    int cnt = 0;
    int m = grid.size(), n = grid[0].size();
    int i = m-1, j = 0;
    while(i >= 0 && j < n) {
        // if current element is negative, then, all the elements to the right in the row are also -ve
        if (grid[i][j] < 0) {
            cnt += (n - j);
            i--;
        }
        else j++;
    }
    return cnt;
}

int main() {
    return 0;
}