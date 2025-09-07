/*
Leetcode - 73 : Set Matrix Zeroes : Medium
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's. You must do it in place.
*/

#include <bits/stdc++.h>
using namespace std; 

// Brute Force Approach :- Time Complexity : O(n * m) * O(n + m) + O(n * m) __ Space Complexity : O(1)
/*
Complexity Analysis ->
We iterate through the matrix and mark the row & col elements as -1 when a 0 is encountered. The iteration happens in O(n * m) and to mark the row 
& col we need n + m iteartions (n iteartions to mark col j elements and m iterations to mark row i elements). So this whole marking procedure takes
O(n*m) * O(n+m) iteartions since marking is done for everytime a 0 is encountered and in worst case all elements can be 0. 
Now after marking we again traverse the matrix to set -1 to 0 adding another n * m iterations and making the overall complexity to be 
O(n * m) * O(n + m) + O(n * m) :- O(n * m) * O(n + m) {for traversal & marking} __ O(n * m) {for second traversal}
*/
/*
We iterate through the matrix and if any 0 is encountered we mark all the elements of that row & col. The problem states to mark every element of the 
row & col as 0 when a 0 is encountered, but doing so while iterating will result in unexpected output. 
Ex-> consider matrix shown below 
0 1 1                   0 0 0
1 1 1           ->      0 1 1       (expected output)
1 1 1                   0 1 1 
but if we mark all row & col as 0 while iterating then it will only prove troublesome.
as here arr[0][0] is 0 so if we make all 1st row & col elements as 0 then matrix becomes [[0,0,0],[0,1,1],[0,1,1]]
now when we check for arr[0][1] it is also 0 (since it was marked 0 earlierly) so now if we will again mark its row & col as 0
matrix becomes [[0,0,0],[0,0,1],[0,0,1]] ... if we continue this process the whole matrix becomes 0 which is incorrect.
This is since we were trying to mark the elements while iterating through the array. So to do so while iterating the array we can try to mark non-zero
elements with something other than 0 like -1. So while iterating further there won't be any intereference due to the markings done.

Approach :- iterate through the matrix and mark the row & col non-zero elements as -1 if a 0 in encountered. When the whole matrix iteration ends 
then again iterate and set the -1 elements to 0 to get the output. 
*/

// markRow : function to mark the ith row (set all non-zero elements to -1) when a 0 is found in the ith row
// n & m are dimensions of matrix __ n = no of rows (no of elements in a column) __ m = no of columns (no of elements in a row)
void markRow(vector<vector<int>> &matrix, int n, int m, int i){
    // we just want to mark all non-zero elements of row i.. we can access all the ith row elements as arr[i][j] where j goes 0 to m
    for(int j=0; j<m; j++){
        if (matrix[i][j] != 0) {
            matrix[i][j] = -1;
        }
    }
}

// markCol : function to mark the jth col (set all non-zero elements to -1) when a 0 is found in the jth col
void markCol(vector<vector<int>> &matrix, int n, int m, int j){
    // we just want to mark all non-zero elements of col j.. we can access all the jth col elements as arr[i][j] where i goes 0 to n
    for(int i=0; i<n; i++){
        if (matrix[i][j] != 0) {
            matrix[i][j] = -1;
        }
    }
}

void setMatrixZerosBrute(vector<vector<int>> &matrix){
    int n = matrix.size();          // no of rows i.e. no of elements in a column
    int m = matrix[0].size();       // no of cols i.e. no of elements in a row

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (matrix[i][j] == 0) {
                markRow(matrix, n,  m, i);
                markCol(matrix, n,  m, j);
            }
        }
    }

    // set all the -1 elements to 0 to get the resultant matrix
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 0;
            }
        }
    }

}

// Better Approach :- Time Complexity : O(n*m) + O(n*m) = O(2*(n*m)) __ Space Complexity : O(n+m)
/*
We use two additional arrays of size n & m respectively .. row of size n is used to mark the rows which have 0 in them and col of size m is used 
to mark the columns having 0. Initially the two arrays have all elements as 0. row[i], col[j] denotes the presence of a 0 in the ith row and jth 
column of the matrix respectively. If row[i] == 1 (col[j] == 1) this means that the ith row (or jth col) of the matrix has a 0 so we will need to 
make all the elements of the ith row (or jth col) of the matrix as 0 to get the resultant matrix. 
Approach :- Traverse through the matrix and when a zero is encountered (i.e. mat[i][j] == 0) mark it by assigning row[i] = 1 and col[j] = 1... 
Again traverse the matrix for the second time and this time check for the value of row[i] & col[j] while traversing if either of them is marked as 1
this means that their is a 0 in that row (or col) so the current element need to become 0. 
*/
void setMatrixZerosBetter(vector<vector<int>> &matrix){
    int n = matrix.size();
    int m = matrix[0].size();
    // size of row is n because there are total n rows.. similarly col size is m
    int row[n] = {0};          // array to mark the rows containing 0 ... if row[i] == 1 that means the ith row of matrix has a 0 
    int col[m] = {0};          // array to mark the cols containing 0 ... if col[j] == 1 that means the jth col of matrix has a 0
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (matrix[i][j] == 0) {
                row[i] = 1;         // mark ith index of row wih 1
                col[j] = 1;         // mark jth index of col wih 1
            }
        }
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            // row[i] & col[j] can either be 0 or 1 ... if either of them is 1 this means that the ith row (or jth col) of the matrix has a 0
            if (row[i] || col[j]) {  // row[i] || col[j] will be true only when either of them is 1 
                matrix[i][j] = 0;   // set the current element to 0 if either of the ith row or jth col has a 0
            }
        }
    }
}

// Optimal Approach :- Time Complexity : O(n*m) + O(n*m) = O(2*(n*m)) __ Space Complexity : O(1)
/*
Approach :- The approach is quite similar to the better one but here we try to minimize the extra space used i.e. the row & col arrays used. 
Here we try to keep track of the row & col arrays in the matrix itself so we won't have to use any extra space. This is done by considering the 0th row
of matrix to be col array (keeps track of presence of any 0 in the respective columns) and the 0th col of matrix is considered as row array.
Here while iterating if matrix[i][j] is 0 then we mark the row & col by assigning the matrix[i][0] & matrix[0][j] as 0. But if j is 0 i.e. 
the element is in column 0 then we mark that column by assigning col0 as 0. 
After the marking we iterate and change the elements to 0 if the respective row or col is marked but since we are using the 0th row & 0th col to keep 
track of the marked rows & columns itself so we don't touch the elements of 0th row & col initially and change the rest of the elements. 
Only after changing the rest of elements we change the 0th row & col elements since if these elements were changed earlier they might make the whole 
matrix 0 due to false value checks afterwards. Now the 0th row elements are dependent on the matrix[0][0] element so we firstly check whether 
matrix[0][0] is 0 and if it is then we make all the elements of row 0 as 0. After that we check for the 0th col elements, just like how 0th row 
elements were dependent on matrix[0][0], the 0th col elements are dependent on col0 value.
*/
void setMatrixZerosOptimal(vector<vector<int>> &matrix){
    int n = matrix.size();
    int m = matrix[0].size();
    int col0 = 1;           // an extra variable is used to mark the presence of 0 in column 0 since row & col mark arrays collide at 0,0 in matrix
    // step 1: Traverse the matrix and mark 0th row & col accordingly:
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                if (j==0) col0 = 0;
                else matrix[0][j] = 0;
            }
        }
    }
    // Step 2: Mark with 0 from (1,1) to (n-1, m-1):
    for(int i=1; i<n; i++){
        for(int j=1; j<m; j++){
            if (matrix[i][0] == 0 || matrix[0][j] == 0) 
                matrix[i][j] = 0;
        }
    }
    //step 3: Finally mark the 0th col & then 0th row:
    // check for the 0th row entries first and these are changed to 0 only if the matrix[0][0] == 0 
    if (matrix[0][0] == 0) {
        for(int j=1; j<m; j++) matrix[0][j] = 0;
    }
    // check for the 0th col entries now and these are changed to 0 only if the col0 == 0
    if (col0 == 0) {
        for(int i=0; i<n; i++) matrix[i][0] = 0;
    }
}

int main() {
    vector<vector<int>> mat = {{1,1,1},{1,0,1},{1,1,1}};
    vector<vector<int>> mat2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    setMatrixZerosOptimal(mat);

    for(auto arr : mat) {
        for(int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}