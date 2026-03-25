/*
Leetcode - 1572. Matrix Diagonal Sum : Easy

Given a square matrix mat, return the sum of the matrix diagonals.
Only include the sum of all the elements on the primary diagonal and all the elements on the secondary diagonal 
that are not part of the primary diagonal.

Examples :-

Input: mat = [[1,2,3],
              [4,5,6],
              [7,8,9]]
Output: 25
Explanation: Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
Notice that element mat[1][1] = 5 is counted only once.

Input: mat = [[1,1,1,1],
              [1,1,1,1],
              [1,1,1,1],
              [1,1,1,1]]
Output: 8

Input: mat = [[5]]
Output: 5

Constraints :-
- n == mat.length == mat[i].length
- 1 <= n <= 100
- 1 <= mat[i][j] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
Approach :
• We need to sum both primary diagonal (mat[i][i]) and secondary diagonal (mat[i][n-1-i]).
• Problem (common element issue):
    In odd-sized matrices, the center element lies on both diagonals, so it can get counted twice.
• Solution using 2 pointers:
    • Use two pointers per row:
        • i → tracks primary diagonal column (starts at 0, moves right)
        • j → tracks secondary diagonal column (starts at n-1, moves left)
    • For each row k:
        • Add mat[k][i]
        • Add mat[k][j] only if i != j (avoids double counting the middle element)
    • Move pointers:
        • i++ (→) : Move right to get the next primary diagonal element for the next row
        • j-- (←) : Move left to get the next secondary diagonal element for the next row

This way, both diagonals are covered in one pass, and the overlapping middle element is handled safely.
*/
int diagonalSum1(vector<vector<int>>& mat) {
    int n = mat.size();
    int sum = 0;

    int i = 0, j = n-1;     // diagonal element pointers for current row
    
    // k denotes the current row
    for (int k = 0; k < n; k++) {
        sum += mat[k][i];
        if (i != j) sum += mat[k][j];
        i++; j--;
    }
    
    return sum;
}

/*
Instead of checking for the common element at each step, we can add the primary and secondary diagonal elements directly 
and later check if the matrix has common primary & secondary diagonal element and subtract it once.
The matrix would have a common middle element in the primary and seconday diagonal only when the no. of rows is odd.
This common middle element will be present at the position: mat[n/2][n/2]

So, we simply add the primary & secondary diagonal elements during the loop and after loop ends, we check if n is odd.
If yes, we subtract mat[n/2][n/2] from sum as this is the common middle element which had been counted twice.
*/
int diagonalSum2(vector<vector<int>>& mat) {
    int n = mat.size();
    int sum = 0;

    int i = 0, j = n-1;     // diagonal element pointers for current row
    
    // k denotes the current row
    for (int k = 0; k < n; k++) {
        sum += mat[k][i];
        sum += mat[k][j];
        i++; j--;
    }
    
    // if n is odd, then there will be a common element in the two diagonals which has been added two times
    if (n % 2 != 0) 
        sum = sum - mat[n/2][n/2];          // this common element is present at mat[n/2][n/2]
    
    return sum;
}

/*
We don't actually need the two pointers to track the primary and secondary diagonal elements in the row.
For any row 'i', the primary diagonal element is at col 'i' and secondary diagonal element is the ith element from right end.
Thus, 
    primary diagonal element = mat[i][i]        (ith element from row start i.e. left end)
    secondary diagonal element = mat[i][n-i-1]        (ith element from right end)
*/
int diagonalSum3(vector<vector<int>>& mat) {
    int n = mat.size();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += mat[i][i];
        sum += mat[i][n-i-1];
    }

    // if n is odd, then there will be a common element in the two diagonals which has been added two times
    // remove this double-counted middle element by subtracting it from sum once
    if (n % 2 == 1) 
        sum -= mat[n/2][n/2];          // this common element is present at mat[n/2][n/2]
    
    return sum;
}

int main() {
    return 0;
}