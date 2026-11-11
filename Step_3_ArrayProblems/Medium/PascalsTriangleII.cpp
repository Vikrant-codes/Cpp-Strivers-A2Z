/*
Leetcode - 119. Pascal's Triangle II : Easy

Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
          1
        1  1
      1  2  1
    1  3   3  1
  1  4  6   4  1
1  5  10  10  5  1

Examples :-

Input: rowIndex = 3
Output: [1,3,3,1]

Input: rowIndex = 0
Output: [1]

Input: rowIndex = 1
Output: [1,1]

Constraints :-
• 0 <= rowIndex <= 33
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Time Complexity : O(rowIndex²) __ Space Complexity : O(1)
/*
>> Approach 1: Calculate each element using nCr

We know that every element at position (r, c) in 1-indexed Pascal's Triangle is: Combination(r-1, c-1)

Therefore, for a given rowIndex (0-indexed), each element can be calculated using:
    row[i] = Combination(rowIndex, i)

So, one straightforward approach is to iterate from i = 0 to rowIndex and 
calculate each binomial coefficient using the nCr function.

>> Complexity:
- Time: O(rowIndex²) — we calculate nCr for every column, and each calculation takes up to O(rowIndex).
- Auxiliary space: O(1), excluding the output vector.
*/
int findnCr(int n, int r) {
    if (r > n) return 0;
    
    long long ans = 1;
    int k = min(r, n - r);

    for (int i = 0; i < k; i++) {
        ans = ans * (n - i) / (i + 1);
    }
    
    return (int) ans;
}

vector<int> getRow(int rowIndex) {
    vector<int> ans;

    for(int c = 0; c <= rowIndex; c++) {
        ans.push_back(findnCr(rowIndex, c));
    }

    return ans;
}

// Optimal Approach: Time Complexity : O(rowIndex) __ Space Complexity : O(1)
/*
>> Optimal Approach: Generate each element from the previous one

Instead of calculating every element independently using nCr, 
we can use the relationship between two consecutive binomial coefficients:
Combination(n, r+1) = Combination(n, r) × (n - r) / (r + 1)

For example, consider rowIndex = 4:
- Start with ans = 1.
- Next element = 1 × 4 / 1 = 4
- Next element = 4 × 3 / 2 = 6
- Next element = 6 × 2 / 3 = 4
- Next element = 4 × 1 / 4 = 1
We get [1, 4, 6, 4, 1].

The key advantage is that we calculate each element in constant time rather than repeatedly calculating factorials or nCr.

>> Why does integer division work?
Each iteration produces the next binomial coefficient, which is always an integer. 
Therefore, after multiplying and dividing in this order, the division is exact.

>> Complexity:
- Time: O(rowIndex) — one iteration per element.
- Auxiliary space: O(1), excluding the output vector.
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

// GFG - Variant
/*
GFG - Pascal Triangle : Medium

Given a positive integer n, return the nth row of pascal's triangle.
Pascal's triangle is a triangular array of the binomial coefficients formed by summing up the elements of previous row.

Examples :-

Input: n = 4
Output: [1, 3, 3, 1]
Explanation: 4th row of pascal's triangle is [1, 3, 3, 1].

Input: n = 5
Output: [1, 4, 6, 4, 1]
Explanation: 5th row of pascal's triangle is [1, 4, 6, 4, 1].

Input: n = 1
Output: [1]
Explanation: 1st row of pascal's triangle is [1].

Constraints :-
• 1 ≤ n ≤ 30
*/

/*
The GFG Variant uses 1-based indexing of rows.
The logic remains exactly the same. We just need to adjust the indexing.

If Pascal's Triangle uses 1-based row numbering:
Row	Elements
1	[1]
2	[1, 1]
3	[1, 2, 1]
4	[1, 3, 3, 1]
5	[1, 4, 6, 4, 1]

The relationship becomes: row[c] = Combination(r-1, c-1)
where both r and c are 1-indexed.
*/
vector<int> nthRowOfPascalTriangle(int n) {
    vector<int> row;
    
    long long val = 1;
    row.push_back(1);
    
    for (int c = 1; c < n; c++) {
        val = val * (n - c) / c;
        row.push_back(val);
    }
    
    return row;
}

int main() {
    return 0;
}