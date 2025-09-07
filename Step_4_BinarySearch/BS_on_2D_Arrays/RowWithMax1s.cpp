/*
GFG - Row with max 1s

You are given a 2D binary array arr[][] consisting of only 1s and 0s. Each row of the array is sorted in non-decreasing order. 
Your task is to find and return the index of the first row that contains the maximum number of 1s. If no such row exists, return -1.

Note:-
> The array follows 0-based indexing.
> The number of rows and columns in the array are denoted by n and m respectively.

Examples:-

Input: arr[][] = [[0,1,1,1], [0,0,1,1], [1,1,1,1], [0,0,0,0]] __ Output: 2
Explanation: Row 2 contains the most number of 1s (4 1s). Hence, the output is 2.

Input: arr[][] = [[0,0], [1,1]] __ Output: 1
Explanation: Row 1 contains the most number of 1s (2 1s). Hence, the output is 1.

Input: arr[][] = [[0,0], [0,0]] __ Output: -1
Explanation: No row contains any 1s, so the output is -1.

Constraints:- 1 ≤ arr.size(), arr[i].size() ≤ 10^3 __ 0 ≤ arr[i][j] ≤ 1 
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * m) __ Space Complexity : O(1)
// Count 1s in each row and return the index of the first row with maximum 1s
int max1sNaive(vector<vector<int>> &arr) {
    int n = arr.size();
    int m = arr.size();
    int max1s = 0, maxRow = -1;

    for (int i=0; i<n; i++) {
        int cnt1s = 0;
        for (int j=0; j<m; j++) {
            if (arr[i][j] == 1) cnt1s++;
        }

        if (cnt1s > max1s) {
            max1s = cnt1s;
            maxRow = i;
        }
    }

    return maxRow;
}

// Binary Search Approach :- Time Complexity : O(n log m) __ Space Complexity : O(1)
/*
My code & approach :- To count the no. of 1s in each row we can use binary Search to find the first occurrence of 1 in that row
and then we can get count of 1s as rowSize - firstIndex. We can keep track of maxCount1s and maxRow and return maxRow afterwards.
*/
int rowMax1s(vector<vector<int>> &arr) {
    int n = arr.size();
    int m = arr[0].size();
    int max1s = 0, maxRow = -1;
        
    for (int i=0; i<n; i++) {
        int low = 0;
        int high = m-1;
            
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[i][mid] == 1) high = mid - 1;
            else low = mid + 1;
        }
            
        int count1s = m - low;      // gives count of 1s in the current row
        if (count1s > max1s) {
            max1s = count1s;
            maxRow = i;
        }
    }
    return maxRow;
}

// Striver's Approach
/*
We cannot optimize the row traversal but we can optimize the counting of 1’s for each row.
Instead of counting the number of 1’s, we can use the following formula to calculate the number of 1’s:
Number_of_ones = m(number of columns) - first occurrence of 1(0-based index).

As, each row is sorted, we can find the first occurrence of 1 in each row using any of the following approaches :-
> lowerBound(1)
> upperBound(0)
> firstOccurrence(1)
*/
int lowerBound(vector<int> arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = (low + high) / 2;
        // maybe an answer
        if (arr[mid] >= x) {
            ans = mid;
            //look for smaller index on the left
            high = mid - 1;
        }
        else {
            low = mid + 1; // look on the right
        }
    }
    return ans;
}

int rowMax1sStriver(vector<vector<int>> &matrix, int n, int m) {
    int cnt_max = 0;
    int index = -1;

    //traverse the rows:
    for (int i = 0; i < n; i++) {
        // get the number of 1's:
        int cnt_ones = m - lowerBound(matrix[i], m, 1);
        if (cnt_ones > cnt_max) {
            cnt_max = cnt_ones;
            index = i;
        }
    }
    return index;
}

// Most Optimal Approach (Staircase Method) :- Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
Approach :- Staircase traversal idea
We start at the top-right corner of the matrix : Position (row = 0, col = m-1).

Now we move as follows:
> If arr[row][col] == 1 → This row has at least (m - col) ones. Maybe it has even more if we move left. 
So we update the answer to this row and move left (col--).

> If arr[row][col] == 0 → This row has no 1 at this column (and hence none to the left either, since sorted).
So this row can't be our answer as it has less 1s than our current maxRow. So, we move down (row++) to check the next row.

Repeat until you either fall off the grid (row >= n or col < 0).

Complexity Analysis :- Each step moves either left or down. At most m left moves and n down moves. So O(n + m) steps.
*/
int rowWithMax1s(vector<vector<int>> &arr) {
    int n = arr.size();             // no of rows
    int m = arr[0].size();          // no of cols

    int i = 0, j = m-1, maxRow = -1;
    while (i < n && j >= 0) {
        if (arr[i][j] == 1) {
            maxRow = i;
            j--;
        }
        else i++;
    }
    return maxRow;
}

int main() {
    
    return 0;
}