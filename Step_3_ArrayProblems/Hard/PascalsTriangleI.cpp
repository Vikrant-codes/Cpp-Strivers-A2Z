/*
TUF - 161. Pascal's Triangle I

Given two integers r and c, return the value at the rth row and cth column (1-indexed) in a Pascal's Triangle.

In Pascal's triangle:
• The first row contains a single element 1.
• Each row has one more element than the previous row.
• Every row starts and ends with 1.
• For all interior elements (i.e., not at the ends), the value at position (r, c) 
  is computed as the sum of the two elements directly above it from the previous row:
    Pascal[r][c] = Pascal[r−1][c−1] + Pascal[r−1][c]
  where indexing is 1-based

Examples :-

Input: r = 4, c = 2 __ Output: 3
Explanation:
The Pascal's Triangle is as follows:
1
1 1
1 2 1
1 3 3 1
....
Thus, value at row 4 and column 2 = 3

Input: r = 5, c = 3 __ Output: 6
Explanation:
The Pascal's Triangle is as follows:
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
....
Thus, value at row 5 and column 3 = 6

Constraints :-
• 1 <= r, c <= 30
• c <= r
• All values will fit inside a 32-bit integer.
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Approach — Using the nCr formula

A straightforward brute-force approach would be to generate all the rows of Pascal's Triangle up to row r, 
and then return the element at position c in that row. (considering 1-based indexing)

However, we don't actually need to generate the entire triangle.

Pascal's Triangle is closely related to binomial coefficients. 
In fact, it can be viewed as a visual pattern formed by the coefficients in the 
expansions of different powers of a binomial.

For example:

- (a + b)² = a² + 2ab + b² → coefficients: 1 2 1
- (a + b)³ = a³ + 3a²b + 3ab² + b³ → coefficients: 1 3 3 1
These coefficients form the rows of Pascal's Triangle.

Now, the important observation is that each element in Pascal's Triangle is a binomial coefficient (nCr).
For a given row r and column c (1-indexed), the element is:
Element(r, c) = Combination(r-1, c-1)

We subtract 1 because the binomial coefficient formula uses 0-based indexing.

So, we can simply calculate the required binomial coefficient instead of generating the triangle.

>> Complexity Analysis

For findnCr(n, r):
- Time Complexity: O(min(r,n-r)) — We perform min(r, n-r) iterations.
- Auxiliary Space: O(1) — We use only a few variables.

For pascalTriangleI(r, c):
- Time Complexity: O(min(c-1,r-c)).
- Auxiliary Space: O(1).
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

int pascalTriangleI(int r, int c) {
    return findnCr(r-1, c-1);
}

int main() {
    return 0;
}