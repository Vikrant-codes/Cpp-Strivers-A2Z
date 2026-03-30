/*
Leetcode - 54. Spiral Matrix : Medium

Given an m x n matrix, return all elements of the matrix in spiral order.

Examples :-

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

Constraints :-
• m == matrix.length
• n == matrix[i].length
• 1 <= m, n <= 10
• -100 <= matrix[i][j] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(m * n) __ Space Complexity : O(1)
/*
Optimal Approach (Simulation with Boundaries)
Instead of marking visited or using extra space, maintain 4 boundaries:
    • top → starting row
    • bottom → ending row
    • left → starting column
    • right → ending column
Then traverse layer by layer.

Steps: 
Repeat while top <= bottom and left <= right:
1. Left → Right (top row)
    Traverse from left to right, then top++
2. Top → Bottom (right column)
    Traverse from top to bottom, then right--
3. Right → Left (bottom row)
    Traverse from right to left, then bottom--
    (only if top <= bottom)
4. Bottom → Top (left column)
    Traverse from bottom to top, then left++
    (only if left <= right)


Que> Why we use conditions like "if (top <= bottom), if (left <= right)" during bottom row traversal and left column traversal?

After traversing rows / columns we increment or decrement the corresponding row/column pointers (top/right/bottom/left)
Now, assume at some point top == bottom, this means both top & bottom row pointers point to same row 
and thus have same elements. 
So, instead of traversing both top & bottom, we must traverse them only once since they share the same element.
Now, assume spiral traversal starts, we traverse the top row and increment top.. so top becomes greater than bottom.
Then, we traverse the right column, now comes the time to traverse the bottom row.
But in this condition, if we are not using condition 'if (top <= bottom)' to check such case, then
bottom row would be traversed and its elements would be added again (earlier added during top row traversal).
To stop this duplicate addition of elements to the answer, we use this condition.
Similarly, we use 'if (left <= right)' to avoid duplicate traversals & additions of left column elements in similar conditions.
*/
vector<int> spiralOrder(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;
    
    vector<int> res;
    
    while (top <= bottom && left <= right) {
        // top row : left -> right
        for (int i = left; i <= right; i++)
            res.push_back(mat[top][i]);
        top++;
    
        // right column : top -> bottom
        for (int i = top; i <= bottom; i++)
            res.push_back(mat[i][right]);
        right--;
    
        // bottom row : right -> left
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                res.push_back(mat[bottom][i]);
            bottom--;
        }
    
        // left column : bottom -> top
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                res.push_back(mat[i][left]);
            left++;
        }
    }
    
    return res;
}

int main() {
    return 0;
}