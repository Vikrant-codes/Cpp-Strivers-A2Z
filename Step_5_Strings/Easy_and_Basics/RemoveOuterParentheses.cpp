/*
Leetcode - 1021. Remove Outermost Parentheses : Easy

A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents
string concatenation.
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B,
with A and B nonempty valid parentheses strings.
Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.

Examples :-

Input: s = "(()())(())" __ Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Input: s = "(()())(())(()(()))" __ Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Input: s = "()()" __ Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".

Constraints :- 1 <= s.length <= 10^5 __ s[i] is either '(' or ')' __ s is a valid parentheses string.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔑 Intuition

The outermost parentheses of each primitive substring do not contribute to the final string, so we should skip them.
-- Use a counter to track the current "depth" of parentheses.
-- The first '(' that makes depth = 1 is the outermost opening → skip it.
-- The last ')' that brings depth back to 0 is the outermost closing → skip it.
-- Keep everything else, since those are inner parentheses.

📝 Algorithm
1. Initialize cnt = 0 and an empty result string str.
2. Traverse each character ch in the string:
> If ch == '(':
>> Increment cnt.
>> If cnt > 1, append '(' to result.
> Else (ch == ')'):
>> Decrement cnt.
>> If cnt > 0, append ')' to result.
3. After the loop, return str.
*/
string removeOuterParentheses(string s)
{
    int cnt = 0;
    string str = "";
    str.reserve(s.size());          // reserve space to avoid multiple allocations while appending to str
    for (char ch : s)
    {
        if (ch == '(')
        {
            cnt++;
            if (cnt != 1)
                str += ch;
        }
        else
        {
            cnt--;
            if (cnt != 0)
                str += ch;
        }
    }
    return str;
}

int main()
{
    string s = "(()())(())(()(()))";
    cout << removeOuterParentheses(s) << endl;
    return 0;
}