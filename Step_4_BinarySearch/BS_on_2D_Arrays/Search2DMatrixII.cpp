/*
Leetcode - 240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
> Integers in each row are sorted in ascending from left to right.
> Integers in each column are sorted in ascending from top to bottom.
 
Examples :-

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5 __ Output: true
Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20 __ Output: false

1   4   7   11  15
2   5   8   12  19
3   6   9   16  22
10  13  14  17  24
18  21  23  26  30
 
Constraints :- 
> m == matrix.length __ n == matrix[i].length __ 1 <= n, m <= 300
> -10^9 <= matrix[i][j] <= 10^9 __ -10^9 <= target <= 10^9
> All the integers in each row are sorted in ascending order.
> All the integers in each column are sorted in ascending order.
*/

#include <bits/stdc++.h>
using namespace std;

// Binary Searcch Approach :- Time Complexity : O(n log m) __ Space Complexity : O(1)
bool binarySearch(vector<int>& arr, int x) {
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (arr[mid] == x) return true;
        else if (arr[mid] > x) high = mid - 1;
        else low = mid + 1;
    }
    return false;
}

bool searchMat(vector<vector<int>>& mat, int target) {
    int n = mat.size();
    int m = mat[0].size();

    for (int i = 0; i < n; i++) {
        if (binarySearch(mat[i], target)) return true;
    }
    return false;
}

// Optimal Approach (Staircase Method) :- Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
Let's take a look at the four corners: (0, 0), (0, m-1), (n-1, 0), and (n-1, m-1). 
By observing these corners, we can identify variations in how we traverse the matrix.

Assume the given ‘target’ = 14 and given matrix = 
1   4   7   11  15
2   5   8   12  19
3   6   9   16  22
10  13  14  17  24
18  21  23  26  30

Observations :-

> Cell (0, 0): Assume we are starting traversal from (0, 0) and we are searching for 14. Now, this row and column are both sorted in increasing order. 
So, we cannot determine, how to move i.e. row-wise or column-wise. That is why, we cannot start traversal from (0, 0).

> Cell (0, m-1): Assume we are starting traversal from (0, m-1) and we are searching for 14. Now, in this case, the row is in decreasing order and 
the column is in increasing order. Therefore, if we start traversal from (0, m-1), in the following way, we can easily determine how we should move.
>> If matrix[0][m-1] > target: We should move row-wise.
>> If matrix[0][m-1] < target: We need bigger elements and so we should move column-wise.

> Cell (n-1, m-1): Assume we are starting traversal from (n-1, m-1) and we are searching for 14. Now, this row and column are both sorted in 
decreasing order. So, we cannot determine, how to move i.e. row-wise or column-wise. That is why, we cannot start traversal from (n-1, m-1).

> Cell (n-1, 0): Assume we are starting traversal from (n-1, 0) and we are searching for 14. Now, in this case, the row is in increasing order and 
the column is in decreasing order. Therefore, if we start traversal from (n-1, 0), in the following way,  we can easily determine how we should move.
>> If matrix[n-1][0] < target: We should move row-wise.
>> If matrix[n-1][0] > target: We need smaller elements and so we should move column-wise.

So, from these observations we see that we can start traversal by either the top right end ( cell(0, m-1) ) or bottom left end ( cell(n-1, 0) ). 

Algorithm :- 
> We start traversal by either the top right end ( cell(0, m-1) ) or bottom left end ( cell(n-1, 0) ). So, row = 0, col = m-1.
> If current element i.e. mat[row][col] == target : return true
> If mat[row][col] > target : We can surely say that we won't find the target in column 'col' as columns are sorted increasingly so we do col-- .
> If mat[row][col] < target : The element will surely won't lie in the row 'row' as all elements of that row would be smaller so we do row++ .
> The loop ends when either of the two pointers row & col falls of the gird i.e. when row == n or col < 0. 
*/

bool searchMatrix(vector<vector<int>>& mat, int target) {
    int n = mat.size();         // no of rows
    int m = mat[0].size();      // no of columns
    int row = 0, col = m - 1;
    while (row < n && col >= 0) {
        if (mat[row][col] == target) return true;
        else if (mat[row][col] > target) col--;
        else row++;
    }

    return false;
}

int main() {
    vector<vector<int>> mat = { {1,4,7,11,15}, {2,5,8,12,19}, {3,6,9,16,22}, {10,13,14,17,24}, {18,21,23,26,30} };
    int target = 306;
    cout << searchMatrix(mat, target);

    return 0;
}