/*
Leetcode - 944. Delete Columns to Make Sorted : Easy

You are given an array of n strings strs, all of the same length.
The strings can be arranged such that there is one on each line, making a grid.
For example, strs = ["abc", "bce", "cae"] can be arranged as follows:
abc
bce
cae
You want to delete the columns that are not sorted lexicographically. In the above example (0-indexed), 
columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted, while column 1 ('b', 'c', 'a') is not, 
so you would delete column 1.

Return the number of columns that you will delete.

Examples :-

Input: strs = ["cba","daf","ghi"] __ Output: 1
Explanation: The grid looks as follows:
  cba
  daf
  ghi
Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1 column.

Input: strs = ["a","b"] __ Output: 0
Explanation: The grid looks as follows:
  a
  b
Column 0 is the only column and is sorted, so you will not delete any columns.

Input: strs = ["zyx","wvu","tsr"] __ Output: 3
Explanation: The grid looks as follows:
  zyx
  wvu
  tsr
All 3 columns are not sorted, so you will delete all 3.
 

Constraints :-
n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 1000
strs[i] consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation / Direct Implementation Approach :- Time Complexity : O(n * s) __ Space Complexity : O(1)
/*
🧠 Intuition
Each column in the list of strings should be lexicographically sorted from top to bottom.
If any column is not sorted, that column must be deleted.
So the goal is simple —
→ Check each column independently,
→ Count how many of them are unsorted (i.e., have at least one character that breaks the increasing order).

⚙️ Algorithm
1. Let n = number of strings, s = length of each string.
2. Initialize cnt = 0 (number of columns to delete).
3. For each column index i from 0 to s - 1:
- Traverse the strings from 1 to n - 1.
- If any strs[j][i] < strs[j-1][i], this column is unsorted:
-> Increment cnt.
-> Break the loop for this column (no need to check further).
4. Return cnt.

⏱ Complexity Analysis

Time Complexity:
Outer loop runs for all columns → s times.
Inner loop checks each string in that column → up to n times.
✅ Total: O(n * s)

Space Complexity: Only a few variables (cnt, n, s) → O(1).
*/
int minDeletionSize(vector<string>& strs) {
    int n = strs.size();
    int s = strs[0].size();
    int cnt = 0;
        
    for (int i=0; i<s; i++) {
        for (int j=1; j<n; j++) {
            if (strs[j][i] < strs[j-1][i]) {
                cnt++; 
                break;
            }
        }
    }

    return cnt;
}

int main() {

    return 0;
}