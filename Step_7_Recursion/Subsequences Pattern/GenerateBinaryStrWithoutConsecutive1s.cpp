/*
Generate all binary strings without consecutive 1's

Given an integer n, return all binary strings of length n that do not contain consecutive 1s. 
Return the result in lexicographically increasing order.

A binary string is a string consisting only of characters '0' and '1'.

Examples :-

Input: n = 3  
Output: ["000", "001", "010", "100", "101"]  
Explanation: All binary strings of length 3 that do not contain consecutive 1s.

Input: n = 2  
Output: ["00", "01", "10"]  
Explanation: All binary strings of length 2 that do not contain consecutive 1s.

Constraints :-
• 1 <= n <= 20

* Interesting Fact : The count of n length strings with no consecutive 1s is equal to (n+2)-th Fibonacci Number.
Ex- for n = 3, the count of strings are 5. 
Also, the (3+2)th fibonacci number is also 5. (fibonacci sequence = 1 1 2 3 5)
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Implementation (Backtracking) : Time Complexity : O(n ∙ 2^n) __ Space Complexity : O(n)
/*
We know how to generate 'n' length binary strings, to do so, we need to consider the '0' / '1' possibilities for each index.
Here also, we try to do the same and place '0' and '1'.
But we need to make sure that no two consecutive ones are placed together, so in order to do so, 
we only place a '1' if the previous character is '0'.

Or conversely we can also try to place '10' together insetad of simple '1' so consecutive 1's can be avoided.
What this means is that suppose curr generated string is "0100",
now at the 5th position, we can either place a '0' and recurse with string "01000" 
or we can place a '1' and recurse with "01001". 
But if we simply place '1', then giving the same two placing choices (0 or 1) would give us consecutive 1s ("010011").
So, we either try to explicitly check that the previous element should not be a '1', before picking the '1' choice.
Or, we can simply place a "10" in the string as we know that after a 1 is placed, it can only be followed by a 0. 
So, the next choice must be given to i+2 index.
(GFG approach uses this concept).

>> Complexity Analysis:-

-> Time Complexity 
There are total 2^n binary strings for 'n' sized strings, but some of them also have consecutive 1's.
So, not all branches are traversed, but still we consider the worst case to be O(2^n).
Now, for each branch, after we get the string at leaf node, adding it to result is again O(n).
So, total time is O(n ∙ 2^n)

* Please note that this is an upper bound. An exact bound would be O(n ∙ F(n+2)) where F(n+2) is (n+2)th Fibonacci Number.
Knowing that the count of strings without consecutive 1's is F(n+2), 
we can also consider O(n ∙ F(n+2)) as the time complexity.

-> Space Complexity 
O(n) due to recusive call stack
So, auxiliary space without considering result vector : O(n)

If we consider the result vector as well, it will have O(F + 2) strings of size 'n' each in it.
So, the auxiliary space including result vector is O(n ∙ F(n+2))
Again, we can consider the upper bound which is O(n ∙ 2^n) as the space complexity.
*/

// My solution: Before placing a '1', we check that the previously placed character must not be a '1' (must be a '0')
// I used 'i' to denote the current index for placing the character and last character is placed at index `i-1`

// Helper method -- generate binary string without consecutive 1s recursively
void fun(int n, string& s, int i, vector<string>& res) {
    if (i == n) {
        res.push_back(s);
        return;
    }

    // add '0'
    s.push_back('0');
    fun(n, s, i+1, res);
    s.pop_back();

    // add '1' only if the last string character is not '1'
    if (i == 0 || s[i-1] == '0') {
        s.push_back('1');
        fun(n, s, i+1, res);

        s.pop_back();
    }
}

vector<string> generateBinaryStrings(int n) {
    vector<string> res;
    string str = "";
    str.reserve(n);

    fun(n, str, 0, res);

    return res;
}

// Striver's solution: Same idea as above, we can use the string.back() method to check the last added character
void generate(int n, string curr, vector<string>& result) {
    // Base case: if length is n, add to result
    if (curr.length() == n) {
        result.push_back(curr);
        return;
    }

    // Always try adding '0'
    generate(n, curr + "0", result);

    // Add '1' only if previous char is not '1'
    if (curr.empty() || curr.back() != '1') {
        generate(n, curr + "1", result);
    }
}

vector<string> generateBinaryStringsStriver(int n) {
    vector<string> res;
    string str = "";

    generate(n, str, res);
    
    return res;
}

// GFG Solution
/*
Approach:
The idea is to generate all binary strings of length n without consecutive 1's using a recursive backtracking approach 
that explores all valid configurations. 
We start with a string of all '0's and then recursively consider two options for each position: 
either keep it as '0' or change it to '1'. 
When we place a '1' at any position, we skip the next position in our recursive exploration to ensure 
we don't create consecutive 1's.

Step by step approach:
• Initialize a string of length n with all zeros.
• For each position, explore two possibilities: keeping '0' or placing '1'.
    • When placing '1' at a position, skip the next position in recursion to avoid consecutive 1's.
• On reaching the end of the string, add the string to the resultant array.
• Use backtracking to restore the state and explore all possible paths.
*/

// Recursive helper function to generate binary strings
void stringRecur(int i, string &s, vector<string> &ans) {
    // Base case: If we've filled all positions, add the string to results
    if (i >= s.length()) {
        ans.push_back(s);
        return;
    }
    
    // Case 1: Keep the current position as '0' and move to next position
    stringRecur(i+1, s, ans);
    
    // Case 2: Try placing '1' at current position. Skip the next position when we place a '1' to avoid consecutive 1's
    s[i] = '1';
    
    // Skip next position to avoid consecutive 1's
    stringRecur(i+2, s, ans);  
    
    // Backtrack: Restore the current position back to '0'
    s[i] = '0';
}

vector<string> generateBinaryStringsGFG(int n) {
    // Initialize a string of n zeros as our starting point
    string s(n, '0');
    vector<string> ans;

    stringRecur(0, s, ans);
    
    return ans;
}

int main() {
    return 0;
}