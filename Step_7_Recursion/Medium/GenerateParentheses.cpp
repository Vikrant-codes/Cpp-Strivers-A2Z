/*
Leetcode - 22. Generate Parentheses : Medium

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Examples :-

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Input: n = 1
Output: ["()"]

Constraints :-
• 1 <= n <= 8
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(2n · 2^(2n) ) = O(2n · 4^n)__ Space Complexity : O(2n)
/*
>> Intuition
We want to generate well-formed paretheses containing `n` pairs.
The generated sequences can only have the characters '(' or ')'.
With `n` pairs, the generated sequences must be of length 2*n and must be well formed parentheses.

So, the naive approach is to generate all possible sequences of length 2n and 
add only the well formed parentheses sequences to result.

There are 2n positions in every answer, and at each position we have exactly two choices:
• place '('
• place ')'
So we can use recursion to generate all possible strings of length 2n.

For example, n = 1:
    ""
    ├── "("
    |    ├── "(("
    |    └── "()"
    |
    └── ")"
         ├── ")("
         └── "))"
More simply, the recursion explores a binary tree where every level chooses either '(' or ')'.
Once the string reaches length 2n, it contains exactly the right number of positions for n pairs.

The generated sequences of length 2n are [ "((", "()", ")(", "))" ]
But, only one of these is a well formed parentheses "()".
So, we can validate the generated sequences to check if the sequence is a well formed parentheses or not,
and add the valid sequences to the result.

>> How do we check validity?
A generated sequence will be well-formed if no closing comes before opening, i.e., 
at any point, count of closing must remain <= count of opening braces.
And the total count of opening and closing braces must be same.

To check so, instead of keeping separate counters for opening and closing, 
we can maintain a single counter variable -
• '(' increases the balance by 1.
• ')' decreases the balance by 1.

A parentheses string is valid if:
1. The balance never becomes negative while scanning.
    - Otherwise, we have a closing parenthesis without a corresponding opening one.
2. The final balance is 0.
    - This means every opening parenthesis has been closed.

For example:
    ( ) ( )
    1 0 1 0   → valid

whereas:
    ) ( ( )
    -1 ...     → invalid immediately

>> Complexity analysis :-

There are 2^(2n) = 4^n possible strings of length 2n.
For each generated string, isValid() scans all 2n characters, taking O(2n) time.

Therefore:
-> Time: O(2n · 4^n)
There are O(4^n) strings generated, and validating each takes O(2n).

-> Space
The recursion depth is 2n, so:
Auxiliary recursion stack: O(2n)

However, the result contains Cₙ valid parentheses strings, 
where Cₙ is the nth Catalan number: Cₙ = 1/(n+1) * Combination(2n, n)
and asymptotically: Cₙ = Θ(4^n / n^(3/2))

Each result string has length 2n, so the output space is: O(2n · Cₙ)
*/
bool isValid(string s) {
    int cnt = 0;
    for (char ch : s) {
        if (ch == '(') cnt++;
        else cnt--;
        if(cnt < 0) return false;
    }
    return cnt == 0;
}

void generateAll(int n, string curr, vector<string>& res) {
    if (curr.size() == 2*n) {
        if (isValid(curr))
            res.push_back(curr);
        return;
    }
    generateAll(n, curr + '(', res);
    generateAll(n, curr + ')', res);
}

vector<string> generateParenthesisNaive(int n) {
    vector<string> res;
    generateAll(n, "", res);
    return res;
}

// Optimal Approach : Time Complexity : O(2n · Cₙ) __ Space Complexity : O(2n)
/*
• Start with an empty string curr = "".
• Initialize counters: open = 0, close = 0.
• If open < n, add '(' and recurse.
• If close < open, add ')' and recurse.
• If curr.length == 2 * n, or, close == open == n, add it to the result.
*/
/*
>> Intuition

We build the parentheses string one character at a time.
At any point, keep track of:
• open = number of '(' used so far
• close = number of ')' used so far

There are only two possible choices.
1. Add '('
- We can add an opening parenthesis as long as we haven't used all n:
    if (open < n)
- So we add '(' and continue recursively.

2. Add ')'
- We can add a closing parenthesis only if there is an unmatched '(' available.
That means: close < open

For example: ( ( )
Here: open  = 2, close = 1
so one '(' is still unmatched, and we are allowed to add ')'.
But: ( )
has: open = 1, close = 1
so adding another ')' would make the sequence invalid.
Therefore, we simply don't explore that branch.

>> Why this is better than the naive solution ?
The naive approach generates things like:
)(
))
())(
and only afterward discovers that they're invalid.
This solution never generates them in the first place.
For example, starting from:
""
we can only add '(': (
From there:
((
()
Notice that from "()", we cannot add ')', because: open == close
There is no unmatched opening parenthesis to close.
So the recursion tree contains only prefixes that can potentially lead to a valid answer.

Eventually, when: open == n && close == n
we have constructed a complete valid parentheses sequence, so we add it to res.

>> Why close < open guarantees validity
This is the most important idea in the solution.
At every point, we maintain: close <= open
That means we can never have more closing parentheses than opening parentheses in any prefix.
Therefore, while constructing the string, we can never create an invalid prefix such as: )( or: ())
And because we eventually use exactly n opening and n closing parentheses, the final string must be balanced.

So:
open < n controls how many opening brackets we can use, 
while close < open ensures that we never create an invalid parentheses prefix.

>> Complexity Analysis

Let Cₙ be the nth Catalan number, which is the number of valid parentheses combinations: Cₙ = 1/(n+1) * C(2n,n)
and: Cₙ = Θ(4ⁿ / n^(3/2))

The algorithm generates exactly the valid combinations, rather than all 4ⁿ possible strings.
Each valid combination has length 2n, so producing/copying the output takes: Time: O(2n · Cₙ)

-> Auxiliary space
The recursion depth is at most 2n, and comb itself has at most 2n characters:
Auxiliary Space: O(2n)
The returned res is not normally counted as auxiliary space. 
Including the output: Output Space: O(2n · Cₙ)
*/


// My Implementation
/*
Backtracking
The comb string is shared across recursive calls.
So after exploring a choice, we undo it:
    comb.push_back('(');
    fun(...);
    comb.pop_back();
This is the classic backtracking pattern:
    make choice
        ↓
    explore
        ↓
    undo choice
        ↓
    try next choice

For example:-
    comb = "("

        add '('
        → "(("
        → explore...
        → pop '('
        → "("

        add ')'
        → "()"
        → explore...
        → pop ')'
        → "("
This allows the same comb object to be reused throughout the recursion.
*/
void fun(int n, int open, int close, string& comb, vector<string>& res) {
    if (open == n && close == n) {
        res.push_back(comb);
        return;
    }

    if (open < n) {
        open++;
        comb.push_back('(');
        fun(n, open, close, comb, res);
        comb.pop_back();
        open--;
    }

    if (close < open) {
        close++;
        comb.push_back(')');
        fun(n, open, close, comb, res);
        comb.pop_back();
        close--;
    }
}

void fun2(int n, int open, int close, string& comb, vector<string>& res) {
    if (open == n && close == n) {
        res.push_back(comb);
        return;
    }

    if (open < n) {
        comb.push_back('(');
        fun2(n, open, close, comb, res);
        comb.pop_back();
    }

    if (close < open) {
        comb.push_back(')');
        fun2(n, open, close, comb, res);
        comb.pop_back();
    }
}

vector<string> generateParenthesisMySol(int n) {
    string comb = "";
    comb.reserve(2*n);      // reserve space beforehand so no re-allocation is required when adding characters
    vector<string> res;

    fun(n, 0, 0, comb, res);

    return res;
}

// Striver's Implementation
/*
This implementation looks much cleaner but essentially follows the same idea.
The main difference is how curr is managed.

Previous implementation uses `string& comb`
So, we passed the same string by reference through all recursive calls and manually modified it:
thus, we need to push_back() and pop_back() manually to explicitly explore the recursive branch and do backtracking/undo.

This implementation uses `string curr` which passes string as value.
So, instead of manually doing push_back() and pop_back(), 
we simply add the opening/closing braces in the recursive call itself, 
i.e., backtrack(n, open + 1, close, curr + '(', res);

So, with this, we don't have to manually delete the added character while backtracking/undo, 
since the current function string will remain as it is and a updated string (a new string) is passed to recursive call.

Each recursive call gets its own copy of curr, so there is nothing to undo when that call returns.

>> Trade-off
The two implementations have the same recursion/backtracking logic, but:
| Previous                   | This one                           |
| -------------------------- | ---------------------------------- |
| `string& comb`             | `string curr`                      |
| Mutates one shared string  | Creates a new string for each call |
| Needs `push_back/pop_back` | No explicit undo                   |
| Less string copying        | More string copying                |
| Generally more efficient   | Simpler/cleaner                    |
*/
void backtrack(int n, int open, int close, string curr, vector<string>& res) {
    if (curr.length() == 2*n) {
        res.push_back(curr);
        return;
    }

    if (open < n) backtrack(n, open + 1, close, curr + '(', res);
    if (close < open) backtrack(n, open, close + 1, curr + ')', res);
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    backtrack(n, 0, 0, "", res);
    return res;
}

int main() {
    return 0;
}