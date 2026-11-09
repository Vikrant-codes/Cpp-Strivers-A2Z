/*
Leetcode - 73. Set Matrix Zeroes : Medium

Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
You must do it in place.

Examples :- 

Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 
Constraints :-
• m == matrix.length
• n == matrix[0].length
• 1 <= m, n <= 200
• -2^31 <= matrix[i][j] <= 2^31 - 1

Follow up:
• A straightforward solution using O(mn) space is probably a bad idea.
• A simple improvement uses O(m + n) space, but still not the best solution.
• Could you devise a constant space solution?
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach (Using temporary matrix): Time Complexity : O(mn × (m + n)) __ Space Complexity : O(mn)
/*
>> Intuition

The first thing to understand is why we need a temporary matrix.

If we directly modify the original matrix by placing zeroes while traversing it, 
it becomes difficult to distinguish between original zeroes and zeroes that we have newly introduced.
This is a problem because only the rows and columns containing zeroes in the original matrix should be modified. 

Newly introduced zeroes should not trigger further modifications.
To avoid this, we create a temporary matrix having the same dimensions and 
initially containing the same values as the original matrix.

Now, we traverse the original matrix. Whenever we encounter a cell containing 0, 
we make all the elements in its corresponding row and column zero in the temporary matrix.

Notice that we always check the original matrix for zeroes and make modifications only in the temporary matrix.
Once the traversal is complete, we simply copy the temporary matrix back into the original matrix.

>> Complexity Analysis
Let, m = number of rows and n = number of columns.

-> Time: O(mn × (m + n))
  - Traversing the matrix takes O(mn).
  - For every zero encountered, we update its entire row and column, taking O(m + n).
  - Copying the temporary matrix takes O(mn).

-> Space: O(mn) — We create a temporary matrix of the same dimensions as the original matrix.
*/
void setZeroesBrute(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // Create a copy of the original matrix
    vector<vector<int>> temp = matrix;

    // Traverse the original matrix
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

            if(matrix[i][j] == 0) {

                // Make the entire row zero in temp
                for(int col = 0; col < n; col++) {
                    temp[i][col] = 0;
                }

                // Make the entire column zero in temp
                for(int row = 0; row < m; row++) {
                    temp[row][j] = 0;
                }
            }
        }
    }

    // Copy temp back into the original matrix
    matrix = temp;
}

//? Can we optimize the extra space used by the temporary matrix?
/*
In the brute-force approach, we used a separate temp matrix because directly modifying the original matrix 
creates a problem: we cannot distinguish the original zeroes from the zeroes introduced by our algorithm.

One idea to avoid the extra matrix is to use a special marker, such as -1, in the original matrix:
1. Traverse the original matrix.
2. Whenever we encounter a 0, mark all non-zero elements in its row and column with -1.
3. After the traversal, make a second pass and convert all -1 values into 0.

This way, newly marked elements won't be mistaken for original zeroes during the first traversal.

But there's a problem: The matrix can contain any integer value, including -1. 
Therefore, we cannot safely reserve -1 as a marker because it might already be a valid input value.

So, this idea is not a valid general solution for the problem.
*/

// Better Approach: Time Complexity : O(2mn) __ Space Complexity : O(m + n)
/*
>> Intuition

We don't actually need to store a modified copy of the matrix. 
We only need to remember which rows and columns must eventually become zero.

Instead of creating an entire temporary matrix, 
we can optimize the extra space by maintaining two separate vectors:
- rows of size m to track which rows contain an original zero.
- cols of size n to track which columns contain an original zero.

1. Initialize rows and cols with all zeroes.
2. Traverse the original matrix. Whenever we find a zero at (i, j):
   - Mark rows[i] = 1.
   - Mark cols[j] = 1.
    This `1` will mean that there is a zero in the respective row or column index.
3. Once this traversal is complete, traverse the matrix again.
4. For every cell (i, j), check whether rows[i] == 1 or cols[j] == 1.
   - If either condition is true, update matrix[i][j] = 0.

>> Complexity Analysis
- Time Complexity: O(2mn) — Two complete traversals of the matrix takes O(2mn)
- Auxiliary Space: O(m + n) — two vectors are used — rows takes O(m), cols takes O(n).
*/
void setZeroesBetter(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> rows(m, 0);
    vector<int> cols(n, 0);

    // First traversal: mark rows and columns containing original zeroes
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 0) {
                rows[i] = 1;
                cols[j] = 1;
            }
        }
    }

    // Second traversal: update cells based on the markers
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(rows[i] == 1 || cols[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }
}

// Optimal Approach: Time Complexity : O(mn) __ Space Complexity : O(1)
/*
>> Optimal approach — Using the first row and first column as markers

In the previous approach, we used two separate vectors of sizes m and n, requiring O(m + n) auxiliary space.

Can we eliminate these extra vectors?
Yes! We can use the matrix's own first row and first column to store the markers.

The idea is exactly the same as the previous approach, 
but instead of maintaining separate rows and cols vectors, we use:
- matrix[i][0] to indicate whether row i should become zero.
- matrix[0][j] to indicate whether column j should become zero.

i.e., we can mark the presence of zeroes in a particular row/col using the first element position of that row/col.

But there's one complication: matrix[0][0] belongs to both the first row and the first column. 
We need to track these independently.
So, we use one extra variable, col0, to track whether the first column originally contained a zero. 
We use matrix[0][0] to track whether the first row contained a zero.

>> Algorithm

1. First traversal — Mark rows and columns
Whenever we encounter a zero at (i, j):
- If j == 0, mark col0 = 0.
- Otherwise, mark:
  - matrix[i][0] = 0 (row marker).
  - matrix[0][j] = 0 (column marker).

2. Second traversal — Update the inner matrix
Traverse from i = 1 and j = 1.
If either matrix[i][0] == 0 or matrix[0][j] == 0, make matrix[i][j] = 0.

3. Handle the first row and first column
- If matrix[0][0] == 0, make the entire first row zero.
- If col0 == 0, make the entire first column zero.

We handle them at the end so that updating them doesn't interfere with the markers.

>> Complexity Analysis
- Time Complexity: O(mn) — We make a constant number of traversals of the matrix.
- Auxiliary Space: O(1) — We use only one extra variable, col0.
*/
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    int col0 = 1;

    // Step 1: Mark the first row and first column
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;

                if (j == 0)
                    col0 = 0;
                else
                    matrix[0][j] = 0;
            }
        }
    }

    // Step 2: Update the inner matrix
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }

    // Step 3: Update the first row
    if (matrix[0][0] == 0) {
        for (int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }

    // Step 4: Update the first column
    if (col0 == 0) {
        for (int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}

int main() {
    return 0;
}