/*
Leetcode - 118. Pascal's Triangle : Easy

You are given an integer numRows.
Return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it 
and the first and last number on each row must be equal to 1, as shown below:
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1
1 5 10 10 5 1

Examples :-

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Input: numRows = 1
Output: [[1]]

Constraints :-
• 1 <= numRows <= 30
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(N³) __ Space Complexity : O(1)
/*
>> Naive Approach — Using nCr

We know that every element at position (row, col) in 1-based indexing can be calculated using:
Element(row, col) = Combination(row-1, col-1)

So, to generate the entire triangle:
- Iterate through every row from 1 to numRows.
- For each row, iterate through every column from 1 to row.
- Calculate each element using our findnCr() function.
- Add the generated row to the answer.

Essentially, we calculate every element independently.

>> Complexity Analysis
- Time: O(N³) — there are O(N²) elements in the triangle, 
  and calculating each element using nCr can take O(N) time in the worst case.

- Auxiliary space: O(1), excluding the output and temporary row.
*/
int findnCr(int n, int r) {
    if(r > n) return 0;

    long long ans = 1;
    int k = min(r, n-r);

    for(int i = 0; i < k; i++) {
        ans = ans * (n-i) / (i+1);
    }

    return (int)ans;
}

vector<vector<int>> generateNaive(int numRows) {
    vector<vector<int>> ans;

    for(int row = 1; row <= numRows; row++) {
        vector<int> temp;

        for(int col = 1; col <= row; col++) {
            temp.push_back(findnCr(row-1, col-1));
        }

        ans.push_back(temp);
    }

    return ans;
}

// Better Approach: Time Complexity : O(N²) __ Space Complexity : O(N)
/*
>> Intuition

We already know how to generate an entire row of Pascal's Triangle using our solution to LeetCode 119.

So, instead of calculating every element independently:
- Iterate from rowIndex = 0 to numRows - 1.
- Call our getRow(rowIndex) function to generate that particular row.
- Add the generated row to the answer.

This avoids repeatedly calculating nCr for every element.

>> Complexity Analysis
- Time: O(N²) — generating row i takes O(i), so total work is 1 + 2 + ... + N = O(N²).
- Auxiliary space: O(N) space for the temporary row, excluding the output.
*/
vector<int> getRow(int rowIndex) {
    vector<int> ans;
    long long val = 1;

    ans.push_back(1);

    for(int c = 1; c <= rowIndex; c++) {
        val = val * (rowIndex - c + 1) / c;
        ans.push_back(val);
    }

    return ans;
}

vector<vector<int>> generateBetter(int numRows) {
    vector<vector<int>> ans;

    for(int i = 0; i < numRows; i++) {
        ans.push_back(getRow(i));
    }

    return ans;
}

// Optimal Approach: Time Complexity : O(N²) __ Space Complexity : O(N)
/*
>> Optimal — Using the previous row

Instead of calculating elements using nCr, or generating each row independently, 
we can directly use the property of Pascal's Triangle:
Every element (except the boundary elements) is the sum of the two elements directly above it.

For example, consider generating the 4th row:
        1
       1 1
      1 2 1
     1 3 3 1

To generate the next row:
- The first and last elements are always 1.
- Every middle element is calculated as:
    current[j] = previous[j-1] + previous[j]
So, we simply use the previously generated row to construct the next one.

Complexity Analysis
- Time: O(N²) — we generate N rows containing a total of \(N(N+1)/2\) elements.
- Auxiliary space: O(N) for the temporary row, excluding the output matrix. 
*/

// Implementation 1 (My Implementation)
/*
>> Intuition
1. First, insert the 0th row [1] into the answer.
2. Start generating rows from ind = 1.
3. For every new row:
   - Insert 1 at the beginning.
   - Calculate the middle elements by adding adjacent elements from the previous row.
   - Insert 1 at the end.
4. Add the newly generated row to ans.
The important observation is: row[i] = ans[ind-1][i] + ans[ind-1][i+1]
*/
vector<vector<int>> generate1(int numRows) {
    vector<vector<int>> ans;

    ans.push_back({1});     // 0th row
    
    int ind = 1;
    
    while (ind < numRows) {
        vector<int> row;
    
        row.push_back(1);
    
        for (int i = 0; i < ind - 1; i++) {
            row.push_back(ans[ind-1][i] + ans[ind-1][i+1]);
        }
        
        row.push_back(1);
    
        ans.push_back(row);
        ind++;
    }

    return ans;
}

// Implementation 2
/*
1. Every row starts with 1.
2. Calculate the middle elements using the previous row.
3. Add the ending 1 (except for the first row, which already contains just one element).
4. Add the newly generated row to the answer.
*/
vector<vector<int>> generate2(int numRows) {
    vector<vector<int>> ans;

    for(int i = 0; i < numRows; i++) {
        vector<int> row;

        row.push_back(1);

        for(int j = 1; j < i; j++) {
            int val = ans[i-1][j-1] + ans[i-1][j];
            row.push_back(val);
        }

        if(i > 0)
            row.push_back(1);

        ans.push_back(row);
    }

    return ans;
}

// Implementation 3: Time Complexity : O(N²) __ Space Complexity : O(1)
vector<vector<int>> generate3(int numRows) {
    vector<vector<int>> ans(numRows);

    for(int i = 0; i < numRows; i++) {
        // resize the ith row inside ans vector to hold (i+1) elements, and fill with all 1s (to make first and last as 1)
        ans[i].resize(i+1, 1);
        
        // this loop will start running from 2nd row
        for(int j = 1; j < i; j++) {
            ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
        }
    }

    return ans;
}

int main() {
    return 0;
}