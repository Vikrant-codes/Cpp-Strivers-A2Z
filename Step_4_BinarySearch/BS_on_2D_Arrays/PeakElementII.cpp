/*

*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Binary Search) :- Time Complexity : O(n log m) or O(m log n) __ Space Complexity : O(1)
/*
Approach :-

We want to find a peak element in a 2D grid: An element is a peak if it is strictly greater than its immediate neighbors (left/right/up/down).
Now, searching the whole matrix would be O(n*m), too slow. The trick is: binary search over columns / rows.

Step 1: Pick the middle column
Let mid = (low + high) / 2.
We look at the entire mid column and find the maximum element in it (max_el).

Que > Why maximum?
If there exists a peak in this column, the maximum probability of it would be at the row with the max element.
If not, the direction of larger neighbor tells us where the peak must lie. (Because if a neighbor is larger, we can move in that direction to find peak.)

Step 2: Compare with neighbors (left/right)
Let’s call the maximum element in column mid → mat[rowIdx][mid].
Check its neighbors: Left neighbor: mat[rowIdx][mid-1] (if exists) __ Right neighbor: mat[rowIdx][mid+1] (if exists)

Step 3: Decide where to move
If mat[rowIdx][mid] is greater than both left and right → we found a peak ✅. (don't need to check up/down because it's already maximum in its column)
If the left neighbor is bigger → the peak must lie in the left half (high = mid - 1).
If the right neighbor is bigger → the peak must lie in the right half (low = mid + 1).

Que > Why this works (the core idea):
Think of it like 1D peak finding, but applied to a column “slice”:
In 1D, if a neighbor is larger, we move toward it because a peak must exist in that direction.
In 2D, by picking the column maximum, we ensure we’re always moving toward a higher slope, and we won’t “miss” the peak since the grid is finite 
and every path of larger neighbors eventually ends at a peak.

So each iteration halves the search space → O(log m) iterations.
Finding the column max costs O(n) each time.
Total: O(n log m).

We can also do the same by picking rows instead of columns leading to O(m log n) time. 
*/

// function to find the row-index of the max element of coulmn indexed 'mid' 
int findMaxCol(vector<vector<int>>& mat, int n, int mid) {
    int mx = -1, ind = -1;
    // for each row check the 'mid' column element and update max accordingly 
    for (int i=0; i<n; i++) {
        if (mat[i][mid] > mx) {
            mx = mat[i][mid];
            ind = i;
        }
    }
    return ind;
}

vector<int> doNlogM(vector<vector<int>>& mat, int n, int m) {
    int low = 0, high = m - 1;

    while (low <= high) {
        int mid = (low + high) >> 1;
        int max_el = findMaxCol(mat, n, mid);

        int left = (mid - 1 >= 0) ? mat[max_el][mid-1] : -1;
        int right = (mid + 1 < m) ? mat[max_el][mid+1] : -1;

        if (mat[max_el][mid] > left && mat[max_el][mid] > right) return {max_el, mid};
        else if (mat[max_el][mid] < left) high = mid - 1;
        else low = mid + 1;
    }

    return {-1, -1};
}

// function to find the col-index of the max element of row indexed 'mid'
int findMaxRow(vector<int>& row, int m) {
    int mx = -1, ind = -1;
    for (int i=0; i<m; i++) {
        if (row[i] > mx) {
            mx = row[i];
            ind = i;
        }
    }
    return ind;
}

vector<int> doMlogN(vector<vector<int>>& mat, int n, int m) {
    int low = 0, high = n-1; 

    while (low <= high) {
        int mid = (low + high) >> 1;
        int max_el = findMaxRow(mat[mid], m);

        int top = (mid - 1 >= 0) ? mat[mid-1][max_el] : -1;
        int bottom = (mid + 1 < n) ? mat[mid+1][max_el] : -1;

        if (mat[mid][max_el] > top && mat[mid][max_el] > bottom) return {mid, max_el};
        else if (mat[mid][max_el] < top) high = mid - 1;
        else low = mid + 1;
    }

    return {-1, -1};
}

vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    if (n <= m) return doNlogM(mat, n, m);
    else return doMlogN(mat, n, m);
}

int main() {

    return 0;
}