/*
Leetcode - 118. Pascal's Triangle : Easy
Given an integer numRows, return the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
     1
    1 1
   1 2 1
  1 3 3 1
 1 4 6 4 1
1 5 10 10 5 1
Input: numRows = 5 __ Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
______________________________________________________________________________________________________________
Problem Statement: This problem has 3 variations. They are stated below:
Variation 1: Given row number r and column number c. Print the element at position (r, c) in Pascal’s triangle.
Variation 2: Given the row number n. Print the n-th row of Pascal’s triangle.
Variation 3: Given the number of rows n. Print the first n rows of Pascal’s triangle.

<-- Variation 1 : Given row number r and column number c. Print the element at position (r, c) in Pascal’s triangle. -->
Naive Approach :- One of the Naive approaches is to generate the entire Pascal triangle and then find the element at position (r,c). 
We will discuss in variation 3 how to generate Pascal’s triangle.

Optimal Approach :- We can find the value at (r,c) by finding r-1 combination c-1 i.e. Combination(r-1,c-1).

<-- Variation 2 : Given the row number n. Print the n-th row of Pascal’s triangle. -->
Naive Approach :- In this approach, for every column from 1 to n, we will calculate the element (n, c)(where n is the given row number and 
c is the column number that will vary from 1 to n) using the previous method. Thus, we can find the n-th row of Pascal’s triangle.

Optimal Approach :- We run a loop for n number of times and find the current elements as Current element = prevElement*(rowNumber-colIndex)/colIndex

<-- Variation 3 : Given the number of rows n. Print the first n rows of Pascal’s triangle. -->
Naive Approach :- The naive approach is basically a combination of variation 1 and variation 2. Here, for every row from 1 to n, we will try to 
generate all the row elements by simply using the naive approach of variation 2. So, we will use the same code as variation 2(naive approach), 
inside a loop (i.e. row runs from 1 to n).

OPtimal Approach :- Now, in the optimal approach of variation 2, we have learned how to generate a row in O(n) time complexity. So, in order to 
optimize the overall time complexity, we will be using that approach for every row. Thus the total time complexity will reduce.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Find nCr :- we know that n C r = n! / (r! * (n-r)!) but the n! can always be expressed as n * (n-1) * (n-2) *..* (n-r) * (n-r-1) * (n-r-2) *..* 2 * 1
but (n - r)! = (n-r) * (n-r-1) * (n-r-2) *..* 2 * 1 .. so this two term cancel out in numerator and denominator so we to calucluate n C r we just 
need to find n C r = n * (n-1) * (n-2) *..* (n-r+1) / (r * (r-1) * (r-2) *..* 2 * 1) = n/1 * (n-1)/2 * (n-2)/3 *..* (n-r+1)/r 
this can be further simplified by cancelling out the max term out of r! & (n-r)! .. after doing so we run a loop for the min(r, n-r) & calculating 
res = res * (n-i)/(i+1).

Complexity Analysis :- the loop runs for min(r, n-r) so time complexity is O(min(r, n-r))
*/
long long findnCr(int n, int r) {
    int mn = min(r, n-r);
    long long res = 1;
    for(int i=0; i<mn; i++) {
        res = res * (n-i);
        res = res / (i+1); 
    }
    return res;
}

// Variation 1 : Time Complexity : O(min (c-1, r-1 - c-1)) __ Space Complexity : O(1)
// Approach :- Given row no. r & col no. c, we can find the value at (r,c) by find r-1 combination c-1 i.e. Combination(r-1,c-1).
long long PascalV1(int r, int c) {
    return findnCr(r-1, c-1);
}

// Variation 2
// Brute Force Approach :- Time Complexity : O(n * r) {worst case} __ Space Complexity : O(1)
vector<long long> PascalV2Brute(int row) {
    vector<long long> ans;
    for(int i=0; i<row; i++) {
        long long element = findnCr(row-1, i);
        ans.push_back(element);
    }
    return ans;
}
// Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
vector<int> PascalV2Optimal(int row) {
    vector<int> ans;
    int res = 1;
    for(int i=0; i<row; i++) {
        if(i==0 || i==row-1) ans.push_back(1);
        else {
            res = res * (row - i) / i;
            ans.push_back(res);
        }
    }
    return ans;
}

// Variation 3
// Brute Force Approach :- Time Complexity : O(n * n * r) {worst case} __ Space Complexity : O(1)
vector<vector<int>> PascalV3Brute(int n) {
    vector<vector<int>> ans;

    //Store the entire pascal's triangle:
    for (int row = 1; row <= n; row++) {
        vector<int> tempLst; // temporary list
        for (int col = 1; col <= row; col++) {
            tempLst.push_back(findnCr(row - 1, col - 1));
        }
        ans.push_back(tempLst);
    }
    return ans;
}
// Optimal Approach :- Time Complexity : O(n * r) {worst case} __ Space Complexity : O(1)
vector<vector<int>> PascalV3Optimal(int n) {
    vector<vector<int>> ans;
    for(int i=1; i<=n; i++){
        vector<int> row = PascalV2Optimal(i);
        ans.push_back(row);
    }
    return ans;
}

// Leetcode - 118. Pascal's Triangle : Easy -> Generate Pascal's triangle -> Variation 3 problem
vector<int> generateRow(int row_no) {
    int res = 1;
    vector<int> row;
    for(int i=0; i<row_no; i++) {
        if(i==0 || i==row_no-1) row.push_back(1);
        else{
            res = res * (row_no-i) / (i);
            row.push_back(res); 
        }
    }
    return row;
}
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> PascalTriangle;
    for(int i=1; i<=numRows; i++) {
        vector<int> row = generateRow(i);
        PascalTriangle.push_back(row);
    }
    return PascalTriangle;
}

int main() {
    int row = 6;
    int col = 4;
    long long element = PascalV1(row, col);
    cout << "The element in row " << row << " and column " << col << " is : " << element << endl;

    vector<int> pascalRow = PascalV2Optimal(row);
    cout << "The " << row << "th row of Pascal Triangle is :- ";
    for(auto x : pascalRow) cout << x << " ";
    cout << endl;

    vector<vector<int>> pascalTriangle = PascalV3Optimal(row);
    cout << "Pascal Triangle" << endl;
    for(auto r : pascalTriangle) {
        for(auto x : r) cout << x << " ";
        cout << endl;
    }
    return 0;
}