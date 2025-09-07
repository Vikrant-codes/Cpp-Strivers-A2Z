/*
GFG - Median in a row-wise sorted Matrix -- Hard

Given a row-wise sorted matrix mat[][] of size n*m, where the number of rows and columns is always odd. Return the median of the matrix.

Examples :-

Input: mat[][] = [[1, 3, 5], 
                [2, 6, 9], 
                [3, 6, 9]]
Output: 5
Explanation: Sorting matrix elements gives us [1, 2, 3, 3, 5, 6, 6, 9, 9]. Hence, 5 is median.

Input: mat[][] = [[2, 4, 9],
                [3, 6, 7],
                [4, 7, 10]]
Output: 6
Explanation: Sorting matrix elements gives us [2, 3, 4, 4, 6, 7, 7, 9, 10]. Hence, 6 is median.

Input: mat = [[3], [4], [8]]
Output: 4
Explanation: Sorting matrix elements gives us [3, 4, 8]. Hence, 4 is median.

Constraints :- 1 ≤ n, m ≤ 400 __ 1 ≤ mat[i][j] ≤ 2000

Expected Complexities : - Time Complexity: O(n log m * log(maxVal – minVal)) __ Auxiliary Space: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n * m log (n * m)) __ Space Complexity : O(n * m)
/*
Approach :- 
1. Store all the elements of the matrix in a 1-D array. The array will have n * m elements.
2. Sort the array.
3. Return the middle element of the array. The middle element will be at index (n * m) / 2. {no need to consider even case as n & m are always odd}

Complexity Analysis :- 
1. Time Complexity :- O(n * m log (n * m))
>> O(n * m) to traverse the matrix and store all the elements in a 1-D array.
>> Sorting takes O(s log s) time, where s is the size of the array. Here, s = n * m. So, sorting takes O(n * m log (n * m)) time.

2. Space Complexity :- O(n * m) to store the elements of the matrix in a 1-D array.
*/
int findMedianBrute(vector<vector<int>> &mat) {
    int n = mat.size(),  m = mat[0].size();
    vector<int> arr;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            arr.push_back(mat[i][j]);
        }
    }
    sort(arr.begin(), arr.end());

    return arr[(n * m) / 2];
}

// Optimal Approach (Binary Search on Answers) :- Time Complexity : O(n log m * log(maxVal - minVal)) __ Space Complexity : O(1)
/*
Observations :-

Q1 > What is the search space where we will apply binary search?
If we carefully observe, our answer lies between the smallest and the largest number in the given matrix. 
So, the search space will be [min(matrix), max(matrix)].

Q2 > While applying binary search how to check if an element ‘x’ is a possible median?
If ‘x’ is the median, the number of elements smaller or equal to ‘x’ will be surely greater than (MXN) // 2 (integer division).
Consider, the sorted 1D array of all matrix elements is arr[] = {1, 2, 3, 3, 5, 6, 7, 9, 9, 10, 12, 12, 13, 13, 15}. Now the matrix has 15 elements
So, the median will have int(15/2) = 7 elements to its left & right. Since, elements are not necessarily distinct, we check for smaller or equal to x. 
The count of elements smaller or equal to x should be greater than int (m*n / 2) to make x a possible median. In the search space, 
the first element which satisfies this condition will be our answer. 

Q3 > How to check how many numbers are smaller or equal to an element ‘mid’?
One of the ways is to traverse the whole matrix and count the numbers. But in that case, the time complexity will be high. 
So, we have to find other ways. It is given that the matrix is row-wise sorted. So, we can apply the concept of upper bound.
For every particular row, we will find the upper bound of the current element ‘mid’. The index returned will be the number of smaller or equal 
elements in that row.
We will do it for each row and add them to get the total number for the whole matrix.
Mathematically, smaller_equal_in_row = upperBound(matrix[row], mid)
*/
/*
Que❓>> Follow-up Question
In the “Median in a Row-wise Sorted Matrix” problem, the solution uses binary search on the value space between the global minimum and maximum elements.
During the search, we pick mid values that may not even exist in the matrix.
👉 Why does this method always return an element from the matrix (and not some missing value in between)?

✅ Reasoning

1. Count function is monotonic
Define: f(x) = countSmallerEquals(x)
> This counts how many elements in the matrix are ≤ x.
> f(x) never decreases as x increases.
> f(x) only increases (jumps) when x passes over a value that exists in the matrix.
> For missing values in between, f(x) is flat (constant).

Example with flattened elements [1,2,3,3,7,...]: assume f(3) = 4 and f(7) = 6 i.e. count of elements ≤ 3 is 4, and count of elements ≤ 7 is 6.
Then for any x in (3,7) (like 4,5,6), f(x) = 4 (no new elements counted).
f(3) = 4, f(4) = 4, f(5) = 4, f(6) = 4, f(7) = 6 ...

2. Binary search invariant
We are searching for the smallest x such that : f(x) > req, where req = (n*m)/2 (the number of elements left of the median).
> If f(mid) <= req → median must be larger → move right.
> If f(mid) > req → median could be mid or smaller → move left.
This keeps shrinking the range [low, high].

3. Why it cannot stop at a missing value ? 
Suppose mid is not in the matrix (e.g., 4, 5, 6 in the example).
Then f(mid) = f(mid-1) → no new information. (as we saw in the example f(6) = f(5) = f(4) = f(3) = 4)
and since we are looking for the smallest x with f(x) > req, the missing values can never be the answer as they do not change f(x). 

Binary search will keep adjusting until it crosses the jump point, i.e., the next real matrix element.
The first point where f(x) exceeds req is guaranteed to be a matrix element (since jumps only happen there).

4. Boundaries are anchored
Initial low = global minimum (a matrix element).
Initial high = global maximum (a matrix element).
So when binary search converges, it can only stop at one of the actual element values.

🎯 Conclusion
Even though we test non-existent values (mid) during binary search, the algorithm always returns the median as a real matrix element because:
> The countSmallerEquals function is constant on gaps and jumps only at matrix values.
> The binary search looks for the first jump point, which must be an actual matrix element.
*/

vector<int> findLowHigh(vector<vector<int>> &mat, int m) {
    int mn = INT_MAX, mx = INT_MIN;
    for (auto &row : mat) {
        if (row[0] < mn) mn = row[0];
        if (row[m-1] > mx) mx = row[m-1];
    }
    return {mn, mx};
}
    
int upperBound(vector<int>& row, int m, int x) {
    int low = 0, high = m - 1;
        
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (row[mid] <= x) low = mid + 1;
        else high = mid - 1;
    }
        
    return low;
}
    
// count the no. of elements smaller than / equal to 'x' in the matrix
int countSmallerEquals(vector<vector<int>> &mat, int m, int x) {
    int cnt = 0;
    for (auto &row : mat) {
        cnt += upperBound(row, m, x);
    }
    return cnt;
}
    
int median(vector<vector<int>> &mat) {
    int n = mat.size(), m = mat[0].size();
        
    vector<int> lowHigh = findLowHigh(mat, m);
    int low = lowHigh[0], high = lowHigh[1];
        
    int req = (m * n) >> 1;  // expected count of elements to the left of median 
        
    while (low <= high) {
        int mid = (low + high) >> 1;
            
        int smallerEquals = countSmallerEquals(mat, m, mid);
            
        if (smallerEquals <= req) low = mid + 1;
        else high = mid - 1;
    }
        
    return low;
}


int main() {

    return 0;
}