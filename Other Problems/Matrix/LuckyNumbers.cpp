/*
Leetcode - 1380. Lucky Numbers in a Matrix : Easy

Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.

Examples :-

Input: matrix = [[3,7,8],[9,11,13],[15,16,17]] __ Output: [15]
Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.

Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]] __ Output: [12]
Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.

Input: matrix = [[7,8],[1,2]] __ Output: [7]
Explanation: 7 is the only lucky number since it is the minimum in its row and the maximum in its column.

Constraints :-
- m == mat.length
- n == mat[i].length
- 1 <= n, m <= 50
- 1 <= matrix[i][j] <= 105.
- All elements in the matrix are distinct.
*/

#include <bits/stdc++.h>
using namespace std;

// Using sets :- Time Complexity : O(m*n) + O(m*n) + O(m) __ Space Complexity : O(m + n)
/*
Observations :-
- A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
- All elements in the matrix are distinct.
So:
- We can collect all the minimum elements of each row & maximum of each column in some data-structure (vector/set)
- Then we can either traverse the whole matrix another time and check if a element is both the row_minimum & col_maximum
    If yes, add it to the answer vector.
    This works only because the matrix contains only distinct values.
- Or, we can also use sets to store the row_minimum & col_maximum and then iterate one of the two sets and 
    check for the presence of current element in another set. If yes, add it to ans vector.

Complexity Analysis :-
Let, m = no. of rows = no of elements in each column, n = no. of cols = no of elements in each row

>> Time Complexity :-
    → A entire matrix traversal to find minimum element in each row (1st loop) :- O(m*n)
    → Another entire matrix traversal to find maximum in each col (2nd loop) :- O(m*n)
    → Traversing set containing row_minimums - set will have total m elements (minimum of each row) :- O(m)
    → Total time complexity : O(m*n + m*n + m)
>> Space Complexity :-
    → Two sets to store the row minimums & col maximums :- O(m + n)
        - Since, there are total 'm' rows, so no of elements in row_minimum set = m :- O(m)
        - & Since, there are total 'n' col, so no of elements in col_maximum set = n :- O(n)
    → The ans vector is not considered as extra space
*/
vector<int> luckyNumbers(vector<vector<int>>& mat) {
    int m = mat.size();      // no of rows
    int n = mat[0].size();   // no of cols
    unordered_set<int> row_min(m);     // stores minimum of each row
    unordered_set<int> col_max(n);     // stores maximum of each col
    vector<int> ans;

    for (auto& row : mat) {
        int x = row[0];
        for (int& ele : row) x = min(x, ele);
        row_min.insert(x);
    }
    for (int i = 0; i < n; i++) {
        int x = mat[0][i];
        for (int j = 0; j < m; j++) x = max(x, mat[j][i]);
        col_max.insert(x);
    }

    for (const int& x : row_min) {          // why use 'const int& x' instead of 'int&' ??
        if (col_max.count(x)) ans.push_back(x);
    }
    /*
    Why we used "const int& x : row_min" to reference each element of the set ?
    Reason :
    row_min is an unordered_set<int>. Elements inside a set are:
    • immutable (read-only)
    • Stored to maintain hash integrity

    So this is illegal: for (int& x : row_min)   // ❌ error
    Because int& implies modifiable reference.
    Thus, we either use const reference or value copy to traverse these elements.
    for (const int& x : row_min)   // ✅ best
    for (int x : row_min)          // ✅ also fine
    */
    return ans;
} 

// Optimal Approach :- Time Complexity : O(m*n) + O(m*n) __ Space Complexity : O(m + n)
/*
Finding Row Minimums & Col Maximums in single traversal --
Core intuition (think element-centric, not loop-centric)
Instead of thinking:
    | “I need one loop for rows and another for columns”
think this:
    | “What information does a single matrix element belong to?”

Take any element :- mat[i][j]
It simultaneously belongs to:
• Row i → affects the minimum of row i
• Column j → affects the maximum of column j
So when you are already visiting mat[i][j], you can:
• update rowMin[i]
• update colMax[j]
There is no reason to wait for another traversal.

Why one traversal is sufficient
Mental model --> Imagine walking through the matrix cell by cell.
At each cell (i, j) you ask two simple questions:
1. “Is this smaller than the smallest thing I’ve seen in row i so far?”
2. “Is this larger than the largest thing I’ve seen in column j so far?”
That’s it. Each cell gives two pieces of information at once.
*/
vector<int> luckyNumbers(vector<vector<int>>& mat) {
    int m = mat.size();      // no of rows = no. of elements in each col
    int n = mat[0].size();   // no of cols = no. of elements in each row
    vector<int> rowMin(m, INT_MAX);
    vector<int> colMax(n, INT_MIN);
    vector<int> ans;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rowMin[i] = min(rowMin[i], mat[i][j]);
            colMax[j] = max(colMax[j], mat[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat[i][j] == rowMin[i] && mat[i][j] == colMax[j]) 
                ans.push_back(mat[i][j]);
    
    return ans;
}


int main() {
    return 0;
}