/*
Leetcode - 1252. Cells with Odd Values in a Matrix : Easy

There is an m x n matrix that is initialized to all 0's. There is also a 2D array indices 
where each indices[i] = [ri, ci] represents a 0-indexed location to perform some increment operations on the matrix.

For each location indices[i], do both of the following:
• Increment all the cells on row ri.
• Increment all the cells on column ci.

Given m, n, and indices, 
return the number of odd-valued cells in the matrix after applying the increment to all locations in indices.

Examples :-

Input: m = 2, n = 3, indices = [[0,1],[1,1]] __ Output: 6
Explanation: Initial matrix = [[0,0,0],[0,0,0]].
After applying first increment it becomes [[1,2,1],[0,1,0]].
The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.

Input: m = 2, n = 2, indices = [[1,1],[0,0]] __ Output: 0
Explanation: Final matrix = [[2,2],[2,2]]. There are no odd numbers in the final matrix.

Constraints :-
• 1 <= m, n <= 50
• 1 <= indices.length <= 100
• 0 <= ri < m
• 0 <= ci < n

<-- Follow up: Could you solve this in O(n + m + indices.length) time with only O(n + m) extra space? -->
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(n + m + indices.length) __ Space Complexity : O(n + m)
/*
Initially the matrix contains all 0s and the final value of the cell would depend on how many times it was incremented.
For each [ri, ci] in indices we increment the row ri & col ci. 
This affects values of the cells of those rows & cols. 
So, we can check the final value of a cell by seeing how many times its row & col is incremented.
Also, we only want odd values, the final value would be odd when the total increment of a cell (row + col increment) is odd.
Now, we know sum of two values is odd if one of them is even and other one is odd.

Core observation
You never need the actual matrix.
Why?
Because a cell value depends only on how many times its row and column were incremented.
For any cell (i, j):
value = rowIncrementCount[i] + colIncrementCount[j]
We only care if this sum is odd or even.

When is a cell odd?
A number is odd iff:
• odd + even = odd
• even + odd = odd
So a cell (i, j) is odd if:
• row i is odd AND column j is even
• row i is even AND column j is odd
That’s it. No other case works.

What the code does conceptually

Step 1: Count increments
rows[i] = how many times row i was incremented
cols[j] = how many times column j was incremented

Step 2: Count odd rows & columns
cntOddRow = number of rows with odd increments
cntOddCol = number of columns with odd increments

Step 3: Count odd cells (this is the key insight)

Case 1: Odd row + Even column... 
    | Odd rows = cntOddRow, Even columns = n - cntOddCol
There can be multiple pairs of odd rows, even cols.. We can get all these pairs by doing Odd Rows * Even Cols
    | Cells formed: total Odd rows * total Even cols = cntOddRow * (n - cntOddCol)

Case 2: Even row + Odd column... 
    | Even rows = m - cntOddRow, Odd columns = cntOddCol
There can be multiple pairs of even rows, odd cols.. We can get all these pairs by doing Even Rows * Odd Cols
    | Cells formed: total Even rows * total Odd cols = (m - cntOddRow) * cntOddCol

Step 4: Add them
ans = cntOddRow * (n - cntOddCol) + cntOddCol * (m - cntOddRow);
*/
int oddCells(int m, int n, vector<vector<int>>& indices) {
    vector<int> rows(m), cols(n);

    for (auto& p : indices) {
        rows[p[0]]++;
        cols[p[1]]++;
    }

    int cntOddRow = 0, cntOddCol = 0;
    for (int& x : rows) 
        if (x % 2 != 0) 
            cntOddRow++;
    for (int& x : cols)
        if (x % 2 != 0)
            cntOddCol++;
        
    int ans = 0;
    ans += cntOddRow * (n - cntOddCol);
    ans += cntOddCol * (m - cntOddRow);

    return ans;
}

int main() {
    return 0;
}