/*
Leetcode - 74. Search a 2D Matrix

You are given an m x n integer matrix matrix with the following two properties:
- Each row is sorted in non-decreasing order.
- The first integer of each row is greater than the last integer of the previous row.

Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

Examples :- 

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3 __ Output: true
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13 __ Output: false

Constraints :- m == matrix.length __ n == matrix[i].length __ 1 <= m, n <= 100 __ -10^4 <= matrix[i][j], target <= 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// Binary Search Approach : Time Complexity : O(log (m*n)) = O(log m + log n) __ Space Complexity : O(1)

/*
Approach 1 :- Use binary search to firstly identify the row where the target might lie, and then apply binary search on that row. 
Since the whole matrix is sorted in itself then it's easier to identify the particular row where target exists. 
We check for such a row whose first element is <= target & last element >= target.. i.e. target exists in that row. 
Then apply binary search on that row to find whether target exists or not.
*/ 
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();      // no of rows
    int m = matrix[0].size();   // no of cols
    // identify the row where target might lie
    int row = -1;
    int low = 0, high = n-1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (matrix[mid][0] <= target && target <= matrix[mid][m-1]) {
            row = mid;
            break;
        }
        else if (matrix[mid][0] > target) high = mid - 1;
        else low = mid + 1;
    }
    if (row == -1) return false;

    // apply binary search in the row to find the target element
    low = 0, high = m-1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (matrix[row][mid] == target) return true;
        else if (matrix[row][mid] > target) high = mid - 1;
        else low = mid + 1;
    }

    return false;
}

// this below code is logically same as above one but here we use a binarySeach function to check whether target exists in that particular row or not
bool binarySearch(vector<int> row, int target) {
    int low = 0, high = row.size()-1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (row[mid] == target) return true;
        else if (row[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return false;
}

bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();      // no of rows
    int m = matrix[0].size();   // no of cols

    int low = 0, high = n-1;
    while (low <= high) {
        int mid = (low + high) / 2;

        if (matrix[mid][0] <= target && target <= matrix[mid][m-1]) {
            return binarySearch(matrix[mid], target);
        }
        else if (matrix[mid][0] > target) high = mid - 1;
        else low = mid + 1;
    }    
    return false;
}

/*
Approach :- 
We consider the 2D matrix as a 1D array, take low = 0 and high = n*m - 1. Find mid. The element at mid index of the 1D array can be found at 
row = mid / m & col = mid % m, where m = no of cols = no of elements in row. Check whether matrix[row][col] == target. If yes return true
Else reduce the search space accordingly. 
*/
bool searchMatrix3(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();      // no of rows
    int m = matrix[0].size();   // no of cols = no of elements in each row

    int low = 0, high = n * m - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int row = mid / m;
        int col = mid % m;
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] > target) high = mid - 1;
        else low = mid + 1;
    }
    return false;
}


int main() {

    return 0;
}