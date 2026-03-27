/*
Leetcode - 2946. Matrix Similarity After Cyclic Shifts : Easy

You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.
The following proccess happens k times:
- Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
- Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.

Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

Examples :-

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
Output: false
Explanation:
In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).

Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2
Output: true

Input: mat = [[2,2],[2,2]], k = 3
Output: true
Explanation:
As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.

Constraints :-
- 1 <= mat.length <= 25
- 1 <= mat[i].length <= 25
- 1 <= mat[i][j] <= 25
- 1 <= k <= 50
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(m*n) __ Space Complexity : O(1)
/*
🔍 Idea of the Problem
we need to check: After shifting each row k times (even rows left, odd rows right), does the matrix remain the same?
Instead of actually shifting the matrix, you simulate the effect using indices.

⚙️ Why k = k % n ?
Each row has n elements.
Shifting a row n times → same row again (full cycle).
So: k = k % n removes unnecessary full rotations.
Example: n = 5, k = 12 → same as k = 2
👉 Optimization + avoids redundant work.

🧠 Core Logic
We are checking: “If I shift row i by k, will the row still look exactly the same?”
Instead of shifting and comparing, we ask:
“For every position j, is the value already equal to the value that would come here after shifting?”
The matrix will only be similar if the current value at position j is equal to the value that will come here after shifting.

🔁 Think in Reverse (this is the key)
Don’t think: “Where does this element go after shifting?”
Think: “Which element will come to position j after shifting?”
We use 'x' to get the element which will come at current position 'j' after shifting.

🔁 What the Code Does
1. For each cell (i, j):
   Compute x = index of element that should match after shifting
2. Compare:
    mat[i][j] == mat[i][x]
3. If any mismatch → return false

🔁 Left Shift (Even Indexed Rows)
• For even row index, we simulate left shift.
• We check: “Is the current value equal to the value that would come here after k left shifts?”
• After k left shifts: An element at index j moves to j - k
• This can become negative → so we fix it using cyclic behavior: Add n and take modulo
• 👉 Final index: (j - k + n) % n
• So we compare: mat[i][j] == mat[i][(j - k + n) % n]

🔁 Right Shift (Odd Indexed Rows)
• For odd row index, we simulate right shift.
• We check: “Is the current value equal to the value that would come here after k right shifts?”
• After k right shifts: An element at index j moves to j + k
• This might exceed bounds → so we wrap using modulo
• 👉 Final index: (j + k) % n
• So we compare: mat[i][j] == mat[i][(j + k) % n]
*/
bool areSimilar(vector<vector<int>>& mat, int k) {
    int m = mat.size();
    int n = mat[0].size();

    k = k % n;
    
    if (k == 0) return true;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x = 0;                      // index of the corresponding element after k shifts

            if (i % 2 == 0) 
                x = (j - k + n) % n;        // Left shift for even-indexed row
            else
                x = (j + k) % n;            // Right shift for odd-indexed row
            
            if (mat[i][j] != mat[i][x]) 
                return false;
        }
    }
    
    return true;
}

int main() {
    return 0;
}