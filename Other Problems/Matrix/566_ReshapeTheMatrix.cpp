/*
Leetcode - 566. Reshape the Matrix : Easy

In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one 
with a different size r x c keeping its original data.

You are given an m x n matrix mat and two integers r and c 
representing the number of rows and the number of columns of the wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; 
Otherwise, output the original matrix.

Examples :-

Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]

Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]

Constraints :-
- m == mat.length
- n == mat[i].length
- 1 <= m, n <= 100
- -1000 <= mat[i][j] <= 1000
- 1 <= r, c <= 300
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(m*n) __ Space Complexity : O(m*n) 
/*
Approach:-
- Flatten the given m*n sized matrix into a 1D Matrix (Flatten matrix → 1D array)
- Rebuild new matrix (of size r x c) from this flattened array

🧠 1. How 2D Arrays are Stored (Row-Major Order)
In languages like C/C++, a 2D array is stored row by row in memory.
Example
Matrix (m = 3, n = 4):
1  2  3  4
5  6  7  8
9 10 11 12
Memory (Row-Major) : [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
👉 First row stored, then second, then third.

🔢 2. Mapping 2D → 1D (Flattening)
If we are at position (i, j) in a matrix with n columns:
✅ Formula: index = i * n + j
Why this works:
- Each row has n elements
- Before row i, there are i * n elements
- Then move j steps in current row

Example :- Find index of mat[2][1] (value = 10): index = 2 * 4 + 1 = 9
✔ Correct → 10 is at index 9 in flattened array

🔁 3. Mapping 1D → 2D (Rebuilding)
Now suppose we have a flattened index idx, and want position in a matrix with c columns (i.e. no. of elements in row = c).
✅ Formula:
    row = idx / c
    col = idx % c
Why this works:
- Every row has c elements
- idx / c → which row
- idx % c → position inside row

🔄 4. Full Flow of The Approach

Step 1: Flatten
    mat[i][j] → array[i * n + j]

Step 2: Rebuild
    array[idx] → ans[idx / c][idx % c]

## What is the condition when reshaping is not possible ?
Assume original matrix is of size m*n and we want to reshape it into new matrix of size r*c.
Now, if the size of both matrices is unequal then this reshaping becomes impossible 
i.e. if m*n != r*c → reshaping is not possible → return original matrix.
*/
vector<vector<int>> matrixReshapeNaive(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size();         // count of rows in original matrix
    int n = mat[0].size();      // count of columns in original matrix
    int s = m * n;              // no. of elements in matrix = size of matrix = row_size * col_size 
    // if s != r * c (size of reshaped matrix), return original matrix
    if (s != r * c) return mat;
    
    vector<int> array(s);       // flattened array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int idx = i * n + j;        // index of element mat[i][j] in flattened array = i * n + j
            array[idx] = mat[i][j];
        }
    }
    vector<vector<int>> ans(r, vector<int>(c));     // initialize ans matrix of size r*c

    for (int i = 0; i < s; i++) {
        // array[i] → ans[i/c][i%c], where c = no. of columns = no. of elements in each row
        int row = i / c;
        int col = i % c;
        ans[row][col] = array[i];
    }
    
    return ans;
}

// Simulation Approach : Time Complexity : O(m*n) __ Space Complexity : O(1)
/*
🔑 Core Idea
We simulate how elements would be filled row-wise into the new matrix without explicitly flattening.

We can traverse the elements of the original matrix and simulate the process of filling into new array.

To do so, we use two pointers a & b.
⚙️ Pointers Used
    - a → current row index in reshaped matrix
    - b → current column index in reshaped matrix
    Initially: a = 0, b = 0

🔁 Working Mechanism
Step 1: Traverse original matrix
We iterate through every element of the original matrix in row-major order.

Step 2: Place element in new matrix
    ans[a][b] = mat[i][j];
👉 This ensures elements are filled in the same order.

Step 3: Move column pointer
    b++;
👉 Move to next position in current row.

Step 4: Handle row completion
if (b == c) {
    a++;      // move to next row
    b = 0;    // reset column pointer
}
👉 When a row gets completely filled:
    - Move to next row
    - Start from first column again
🔥 Key Insight: 
Each row in the new matrix can hold exactly c elements.
Once c elements are filled → shift to next row.
*/
vector<vector<int>> matrixReshape1(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size(); 
    int n = mat[0].size();  
    int s = m * n;

    if (s != r * c) return mat;
    
    vector<vector<int>> ans(r, vector<int>(c));
    int a = 0;          // row pointer for ans matrix
    int b = 0;          // col pointer for ans matrix
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ans[a][b] = mat[i][j];
            b++;
            if (b == c) {
                a++;            // move row pointer to the next row
                b = 0;          // set col pointer to the first element of this row
            }
        }
    }

    return ans;
}

// Optimal Approach : Time Complexity : O(m*n) __ Space Complexity : O(1)
/*
🚀 Optimal Approach (Row-wise flattening simulation)
Instead of actually flattening and rebuilding (extra space), we can map indices directly.

mat[i][j] → array[i * n + j] → ans[idx / c][idx % c],       idx = i * n + j

🔁 Mapping Trick
Treat matrix like a 1D array:
    Original index → i * n + j
New index: (index of element in res/ans matrix)
    Row = (i * n + j) / c
    Col = (i * n + j) % c
*/
vector<vector<int>> matrixReshape2(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size();
    int n = mat[0].size();

    if (m * n != r * c) return mat;
    
    vector<vector<int>> res(r, vector<int>(c));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int idx = i * n + j;
            res[idx / c][idx % c] = mat[i][j];
        }
    }

    return res;
}

// Optimal Approach : Time Complexity : O(m*n) __ Space Complexity : O(1)
/*
Instead of traversing the matrix elements using two for loops, 
we use a single loop treating both matrices as 1D arrays in row-major order.

size of this 1D array = m*n = r*c
We use for (int i = 0; i < s; i++), where s = m*n
Now, the ith element of this row-major order maps to mat[i/n][i%n] in original matrix and ans[i/c][i%c] in answer matrix.
We just use this to fill elements in the new matrix.
*/
vector<vector<int>> matrixReshape3(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size();
    int n = mat[0].size();
    int s = m * n;

    if (s != r * c) return mat;

    vector<vector<int>> ans(r, vector<int>(c));
    
    // in row-major form the ith element belongs to the [i / row_size]th row & [i % row_size]th col 
    for (int i = 0; i < s; i++) 
        ans[i/c][i%c] = mat[i/n][i%n];
    
    return ans;
}

int main() {
    return 0;
}