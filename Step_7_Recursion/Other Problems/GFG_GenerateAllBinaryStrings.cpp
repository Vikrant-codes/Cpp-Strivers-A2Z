/*
GFG - Generate all binary strings : Medium

Given an integer n. You need to generate all the binary strings of n characters representing bits.

Note: Return the strings in  ascending order.

Examples :-

Input: n = 2
Output: [00, 01, 10, 11]
Explanation: As each position can be either 0 or 1, the total possible combinations are 4.

Input: n = 3
Output: [000, 001, 010, 011, 100, 101, 110, 111]
Explanation: As each position can be either 0 or 1, the total possible combinations are 8.

Constraints :-
• 1 ≤ n ≤ 20
*/

#include<bits/stdc++.h>
using namespace std;

// Recursion/Backtracking Implementation: Time Complexity : O(n × 2^n) __ Space Complexity : O(n × 2^n)
/*
>> Intuition
To generate all possible binary strings of length n, think of constructing the string one position at a time.
At every position, there are only two choices:
• Pick 0
• Pick 1

So, for the first position, we make both choices. 
Then, for each choice, we again make both choices for the second position, 
and continue until all n positions have been decided.

For example, for n = 3:
                   ""
                 /    \
            0             1
          /  \           /  \
       00     01       10     11
      / \     / \     / \     / \
    000 001 010 011 100 101 110 111

Each path from the root to a leaf represents one complete binary string.
There are 2 choices at every position and n positions, so the total number of strings is: 2^n

>> Why is the order lexicographical?
The key is that at every decision point, we explore 0 before 1.

For example:
    0
    ├── 0
    │   ├── 0 → 000
    │   └── 1 → 001
    │
    └── 1
        ├── 0 → 010
        └── 1 → 011

We completely generate all strings beginning with 0 before moving to strings beginning with 1.
The same thing happens at every subsequent position. Therefore, the resulting order is:
000 → 001 → 010 → 011 → 100 → 101 → 110 → 111
which is exactly lexicographical/ascending order.

>> Where backtracking comes in
Once we finish generating all strings that result from one choice, 
we need to undo that choice so that the position can instead take the other value.

>> Conceptually:
Pick → explore all possibilities → undo the pick → make the other choice → explore again.

So the recursion represents the process of deciding the remaining positions, 
while backtracking allows us to return to an earlier decision point and try the other possibility.

>> Complexity
There are exactly: 2^n strings to generate.
But each string contains n characters, so producing/storing all of them requires: O(n ∙ 2^n)

Time complexity: O(n × 2^n)
Output space: O(n × 2^n) because we store 2^n strings, each of length n.
Auxiliary recursion space: O(n) because at most n positions are being decided along one recursion path.

>> So the important takeaway is:
Each position gives us a binary decision (0 or 1). 
Exploring both decisions recursively generates every possible string, 
and always exploring 0 before 1 naturally gives lexicographical order.
*/

void fun(string& s, int n, vector<string>& res) {
    if (n == 0) {
        res.push_back(s);
        return;
    }
    
    // '0' branch
    s.push_back('0');
    fun(s, n - 1, res);
    
    s.pop_back();
    
    // '1' branch
    s.push_back('1');
    fun(s, n - 1, res);
    
    s.pop_back();
}

vector<string> binstr(int n) {
    string s = "";
    s.reserve(n);
    
    vector<string> res;
    res.reserve(1 << n);
    
    fun(s, n, res);
    
    return res;
}

int main() {
    return 0;
}