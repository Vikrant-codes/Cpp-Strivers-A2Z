/*
GFG - Generate Binary Strings : Easy

Given a string s containing characters '0', '1', and '?'. 
Generate all distinct binary strings that can be formed by replacing each '?' with either '0' or '1'. 
Return the strings in lexicographically increasing order.

Examples :-

Input: s = "1??0?101"
Output: ["10000101", "10001101", "10100101", "10101101", "11000101", "11001101", "11100101", "11101101"]
Explanation: There are 3 wildcard characters, so 23 = 8 binary strings can be formed.

Input: s = "10?"
Output: ["100", "101"]
Explanation: There is 1 wildcard character, so 2 binary strings can be formed.

Constraints :-
• 1 ≤ |s| ≤ 30
• 0 ≤ k ≤ 15, where k is the number of '?' characters
*/

#include<bits/stdc++.h>
using namespace std;

// Recursion/Backtracking Approach : Time Complexity : O(n × 2^k) __ Space Complexity : O(n × 2^k)
/*
>> Intuition

We can think of the string as being traversed one character at a time from left to right. 
At each position, we need to decide what character will appear in the final binary string.

If the current character is already 0 or 1, there is nothing to decide — that character is fixed, 
so we simply continue processing the next position.

The interesting case is when we encounter a ?. Since ? can be replaced by either 0 or 1, 
there are two possible choices for that position. We therefore create two recursive branches:
            ?
          /   \
         0     1
        /       \
  remaining   remaining
  choices      choices

Each branch then processes the rest of the string in exactly the same way. 
Whenever another ? is encountered, it again branches into 0 and 1. 
Once all characters have been processed, one complete binary string has been formed.

Thus, we only branch when we encounter a ?; fixed characters simply continue along the current recursive path. 
The recursion explores every possible combination of replacements for all the ? characters.

To obtain the strings in lexicographically increasing order, 
we always explore the 0 choice before the 1 choice whenever we encounter a ?. 
Since 0 comes before 1 lexicographically, 
all strings generated through the 0 branch will appear before the corresponding strings generated through the 1 branch. 
Therefore, the strings are produced in the required order naturally, without needing to sort them afterward.

>> Complexity
Let:
• n = length of the string
• k = number of ? characters

Each ? has two choices, so there are: 2^k possible binary strings.
Each resulting string has length n, so producing/storing all of them takes:

Time Complexity: O(n × 2^k)
Space Complexity:
• Recursion/backtracking space: O(n)
• Storing the result: O(n × 2^k)

Therefore, including the output: O(n × 2^k) space.
Since k ≤ 15, the maximum number of generated strings is 2^15 = 32768.
*/

// My Implementation
/*
We traverse the string character by character using recursion.
• If the current character is ?, we explore both possible choices: 0 first, then 1, 
  using backtracking to undo each choice after the recursive call.
• If it is already 0 or 1, there is no branching; we simply include that character and continue recursively.
• When we reach the end of the string, the constructed string is added to the result.
• Exploring the 0 branch before the 1 branch ensures the results are generated in lexicographical order 
  without requiring an additional sorting step.
*/
void fun(string& s, int ind, string& str, vector<string>& res) {
    if (ind == s.length()) {
        res.push_back(str);
        return;
    }
    
    if (s[ind] == '?') {
        str.push_back('0');
        fun(s, ind + 1, str, res);
        
        str.pop_back();
        
        str.push_back('1');
        fun(s, ind + 1, str, res);
        
        str.pop_back();
    } 
    else {
        str.push_back(s[ind]);
        
        fun(s, ind + 1, str, res);
        
        str.pop_back();
    }
    
}

vector<string> generateStrings(string& s) {
    vector<string> res;
    
    string str = "";
    str.reserve(s.length());
    
    fun(s, 0, str, res);
    
    return res;
}

// ChatGPT's solution
/*
• We directly modify the input string while recursively processing each character using the current index.
• When we encounter ?, we replace it with 0 and recursively explore that branch, then replace it with 1 and 
  explore the other branch.
• After both branches are explored, we restore ? so that the current position is back to its original state 
  during backtracking.
• For a fixed 0 or 1, there is no branching, so we simply move to the next index.
• Once we reach the end, the current string represents one valid binary string and is added to the result.
• Since the 0 branch is always explored before the 1 branch, the strings are generated directly in lexicographical order.
*/
void solve(string& s, int idx, vector<string>& ans) {
    // Base case: processed the entire string
    if (idx == s.size()) {
        ans.push_back(s);
        return;
    }

    // If current character is '?'
    if (s[idx] == '?') {
        // Try '0' first for lexicographical order
        s[idx] = '0';
        solve(s, idx + 1, ans);

        // Try '1'
        s[idx] = '1';
        solve(s, idx + 1, ans);
        
        // Restore so that when other branches run during backtracking, '?' will tell them to again decide for two choices
        s[idx] = '?';
    }
    else {
        // Fixed character, simply move ahead
        solve(s, idx + 1, ans);
    }
}

vector<string> generateBinaryStrings(string s) {
    vector<string> ans;
    solve(s, 0, ans);
    return ans;
}

int main() {
    string s = "1??0?101";

    vector<string> res = generateStrings(s);

    for (string s : res) {
        for (char ch : s) {
            cout << ch;
        }
        cout << "\n";
    }

    return 0;
}