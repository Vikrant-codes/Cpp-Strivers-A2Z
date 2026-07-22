/*
Leetcode - 1260. Shift 2D Grid : Easy

Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.

In one shift operation:
• Element at grid[i][j] moves to grid[i][j + 1].
• Element at grid[i][n - 1] moves to grid[i + 1][0].
• Element at grid[m - 1][n - 1] moves to grid[0][0].

Return the 2D grid after applying shift operation k times.

Examples :-

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]

Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]

Constraints :-
• m == grid.length
• n == grid[i].length
• 1 <= m <= 50
• 1 <= n <= 50
• -1000 <= grid[i][j] <= 1000
• 0 <= k <= 100
*/

#include<bits/stdc++.h>
using namespace std;

// Pre-requisite : Right shift an array by k places

// Naive Approach : Time Complexity : O(k * m * n) __ Space Complexity : O(1)
/*
We need to shift the grid k times, so we can write logic to shift grid by 1 place and call it k times.

Assume, m = grid.size() = no. of rows
        n = grid[0].size() = no. of cols = no. of elements in row

For every shift, move every element one position to the right.
But we have to do this right rotation by 1 step in a 2D grid, 
so we must make sure that after shifting, the last element of one row becomes the first element of next row.
and the very last element (grid[m-1][n-1]) moves to the 1st position (grid[0][0]).

In a simple 1D array like [1, 2, 3, 4, 5], doing right shift by 1 place is quite simple.
We just need to make sure that curr index element replaces it value by the previous index value.
So, we can loop from end and do something like arr[i] = arr[i-1]
This way, for the array [1, 2, 3, 4, 5], if we iterate from i = 4 to 0
i = 4: curr value = 5, arr[i] = arr[i-1] => curr_val becomes 4
i = 3: curr value = 4, arr[i] = arr[i-1] => curr_val becomes 3
i = 2: curr value = 3, arr[i] = arr[i-1] => curr_val becomes 2
i = 1: curr value = 2, arr[i] = arr[i-1] => curr_val becomes 1
i = 0: curr value = 1, there is no arr[i-1], ideally 5 should come here, but its value has been re-written,
so we would need to store its value in some temp variable before the loop. Assume we stored it as temp = 5
so, when i = 0, we do arr[i] = temp
This way, the whole array is shifted by 1 place.
So, we just have to do the same but for a 2D array.

Normally, right shift means we need to do arr[i] = arr[i-1] for 1D array, and for 2D array : grid[i][j] = grid[i][j-1]
Just like how we need to handle i = 0 case for 1D array shifting, 
We need to handle cases for 2D array shifting as well, when grid[i][j] = grid[i][j-1] might have problems
(like when j = 0, there is no j - 1, so we need to move the value of the last index element of previous row)

In 2D grid, we traverse from the end using two pointers i & j, initialized i = m - 1, j = n - 1.
- if the current element is at the starting index of the current row (when j = 0), 
    then it must have the value of the last index element of the previous row
    i.e., if (j == 0) => grid[i][j] = grid[i-1][j-1]
- the above logic would work fine for all rows starting index, but for the starting index of row 0 (grid[0][0])
    grid[0] don't have any previous row, so grid[0][0] must have value of grid[m-1][n-1]
    We would need to store this grid[m-1][n-1] in a temp variable and use that value when assigning it to 1st element.
    So, if the current element is the 1st position element (when i = 0 and j = 0),
    then, it must have value of the last element of the grid which was stored in a temp variable
    i.e., if (i == 0 && j == 0) => grid[i][j] = temp        
- for other indices, we can simply do grid[i][j] = grid[i][j-1]

>> Time Complexity Analysis 
- We shift the grid by 1 position, k times to get the desired result.
- The method shiftRight shifts the grid by 1 position which takes O(m * n)
- This method is used k times, so total O(k * m * n)
*/

// helper method -- shifts the grid right by 1 position, takes O(m * n), where m = no. of rows, n = no. of cols
void shiftRight(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    int last = grid[m-1][n-1];
    
    for (int i = m-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            // 1st element (at grid[0][0]) must have the value of last one (grid[m-1][n-1]) after shift
            if (i == 0 && j == 0) 
                grid[i][j] = last;
    
            // 1st element of each row grid[i][0] must have previous row last column value i.e., grid[i-1][m-1] 
            else if (j == 0) 
                grid[i][j] = grid[i-1][n-1];
    
            // other elements (grid[i][j]) can simply have the value of their previous elements (grid[i][j-1])
            else 
                grid[i][j] = grid[i][j-1];
        }
    }
}

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    int size = m * n;

    k = k % size;
    if (k == 0) return grid;
    // shiftRight k times
    
    while (k--) 
        shiftRight(grid);
    
    return grid;
}

// Optimal Approach 1 (Index Mapping) : Time Complexity : O(m * n) __ Space Complexity : O(m * n)
/*
Instead of shifting the entire grid k times, we can observe that the grid is just a circular array.

For:
1 2 3
4 5 6
7 8 9

Flattened: [1, 2, 3, 4, 5, 6, 7, 8, 9]

A shift means moving the last element to the beginning.
For k = 2: 
[1, 2, 3, 4, 5, 6, 7, 8, 9]
After 2 shifts: [8, 9, 1, 2, 3, 4, 5, 6, 7]
We can directly calculate the new position of every element.
If an element is at flattened index i, after k shifts: newIndex = (i + k) % total
Ex- 5 which was at index '4' before shifting, moves to index (i + k) % total = (4 + 2) % 9 = 6 % 9 = 6.

In terms of grid position, this flattened index 6 (say 'x') corresponds to grid position
    row = x / n = 6 / 3 = 2
    col = x % n = 6 % 3 = 0
So, 5 moves to the grid position [2][0], i.e., 2nd row 0th col

So, we just need to firstly consider the grid as a flattened 1D array
2D array indices i and j (grid[i][j]) maps to 1D array index ind as:
    ind = i * n + j, where n = no. of cols = no. of elements in row

and, if we need to get the 2D grid indices for some 1D array index ind, then
    i = ind / n
    j = ind % n

Using this logic, we can consider grid as a flattened array, 
Get a 1D flattened array corresponding index from the 2D indices i & j, 
    (lets call this index currentIndex) :- currentIndex = i * n + j
find the index at which current value moves to after rotation  in the 1D array, 
    (lets call this index newIndex) :- newIndex = (currentIndex + k) % total, where total = total elements in grid = m * n
convert that index back to get corresponding new 2D grid positions. 
    (lets call these positions newRow, newCol) :- newRow = newIndex / n __ newCol = newIndex % n
Use a result grid and store the grid[i][j] value at the result[newRow][newCol]

return the result grid

>> Time Complexity Analysis :
- We just iterate the grid once and places the current value in the result grid at corresponding position after k shifts.
- So, total time = O(m * n)

>> Space Complexity Analysis :
- We are using a 2D array result to store the result. So, O(m * n)
Since we are using this extra space to store the result itself, we could consider it as O(1).
*/
vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    int total = m * n;
    k = k % total;
    
    if (k == 0) return grid;
    
    vector<vector<int>> result(m, vector<int>(n));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // current flattened index
            int currInd = i * n + j;
    
            // new flattened index after shifting
            int newInd = (currInd + k) % total;
    
            // grid position corresponding to the new flattened index
            int newRow = newInd / n;
            int newCol = newInd % n;

            result[newRow][newCol] = grid[i][j];
        }
    }

    return result;
}

// Optimal Approach 2 (Flatten + Rotate) : Time Complexity : O(m * n) __ Space Complexity : O(m * n)
/*
>> Approach : 
- We know how to right shift a 1D array by k places using reverse method
    - Reverse the entire array 
    - Then, reverse the first k elements (from index 0 to k-1)
    - reverse the remaining elements of the array (from index k to arr.size()-1)

Since, shifting a 1D array by k places is so easy, we can flatten the given 2D grid to get a 1D flattened array.
Then, we can shift its elements by k places using the reverse approach, and get the k-shifted 1D array.
After that, using the k-shifted 1D array, we can re-write the values in grid to get the desired k-shifted grid.

Ex-> Assume grid:
1 2 3
4 5 6
7 8 9

and k = 2.

Now, flattened array = [1, 2, 3, 4, 5, 6, 7, 8, 9]
we can shift this flattened array by k-places easily as:
    - Reverese the entire array: [9, 8, 7, 6, 5, 4, 3, 2, 1]
    - Reverse the first k elements (from index 0 to k-1) -> here k = 2, so index 0 to index 1: [8, 9, 7, 6, 5, 4, 3, 2, 1]
    - Reverse the remaining elements (from index k to arr.size()-1) -> from index 2 to 8: [8, 9, 1, 2, 3, 4, 5, 6, 7]

Now, we got this k-shifted array [8, 9, 1, 2, 3, 4, 5, 6, 7]
We need to fill the grid with the values from this shifted 1D array in the same order.

So, grid becomes
8 9 1
2 3 4
5 6 7

>> Time Complexity Analysis :-
- Flattening the grid requires traversing the grid once. So, O(m * n)
- The flattened array can be shifted by k-places in O(arr.size()) = O(m * n)        [since arr have m * n elements]
- Re-writing grid values requires another grid traversal, so O(m * n)
So, total : O(m*n)

>> Space Complexity Analysis :-
- We use an array of size (m * n) to store the flattened array and k-shift the elements. So, O(m * n)
*/
void reverse(vector<int>& arr, int start, int end) {
    int l = start, r = end;

    while (l <= r) {
        swap(arr[l], arr[r]);
        l++; r--;
    }
}

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    int size = m * n;

    k = k % size;
    
    if (k == 0) return grid;
    
    vector<int> arr;
    
    for (vector<int>& row : grid)
        for (int& x : row)
            arr.push_back(x);
    
    reverse(arr, 0, size-1);
    reverse(arr, 0, k-1);
    reverse(arr, k, size-1);
    
    int p = 0;
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++)
            // grid[i][j] = arr[i*n + j];
            grid[i][j] = arr[p++];
    
    return grid;
}

int main() {
    return 0;
}