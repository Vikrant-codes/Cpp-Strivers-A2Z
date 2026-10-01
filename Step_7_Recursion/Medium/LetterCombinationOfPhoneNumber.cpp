/*
Leetcode - 17. Letter Combinations of a Phone Number : Medium

Given a string containing digits from 2-9 inclusive, 
return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Examples :-

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Input: digits = "2"
Output: ["a","b","c"]

Constraints :-
• 1 <= digits.length <= 4
• digits[i] is a digit in the range ['2', '9'].
*/

#include<bits/stdc++.h>
using namespace std;

/*
>> Intuition

For each digit, there are a few possible letters it can represent. We build the combination one digit at a time.
At index ind:
• Get the letters mapped to digits[ind].
• Try each possible letter.
• Add that letter to curr.
• Recursively solve for the next digit.
• Remove the letter after returning, so curr is restored for the next choice.

When ind == digits.size(), one complete combination has been formed, so we add it to res.

For example, for "23":
    2 → a
        3 → d → "ad"
            e → "ae"
            f → "af"

    2 → b
        3 → d → "bd"
            e → "be"
            f → "bf"
    ...
So this is essentially a tree of choices, where each level corresponds to one digit.

>> Backtracking pattern
This solution uses the classic:
    for (... choices) {
        choose;
        recurse;
        backtrack;   // undo the choice
    }

The important idea is that curr is shared across all recursive calls.
Suppose: curr = "a"
We choose 'd': curr = "ad"
After the recursive call finishes, we do: curr.pop_back();
and return to: curr = "a"
Now we can try 'e': curr = "ae"
Without the pop_back(), the next branch would incorrectly start with "ad".

So the pattern is:
| Make a choice → explore everything under that choice → undo the choice → try the next choice.

This pattern is especially common when at every level we have multiple choices and need to explore all possibilities.

>> Complexity
Let n = digits.size().

Each digit has at most 4 possible letters (7 and 9 have 4), so there are at most: 4^n combinations.

-> Time: O(4^n × n)
The 4^n comes from generating all combinations, 
and the extra n comes from constructing/copying each completed string into res.

-> Space:
Recursion + curr: O(n)
Result storage: O(4^n × n)
So auxiliary space excluding the output is O(n), while including the returned result it is O(4^n × n).
*/

// Time Complexity : O(4^n x n) __ Space Complexity : O(n)

vector<string> mapping = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// map<char, string> mpp = {
//     {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, 
//     {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
// };

void solve(string& digits, int ind, string& curr, vector<string>& res) {
    if (ind == digits.size()) {
        res.push_back(curr);
        return;
    }

    string characters = mapping[digits[ind] - '2'];

    // string characters = mpp[digits[ind]];
    
    for (char ch : characters) {
        curr.push_back(ch);

        solve(digits, ind + 1, curr, res);
        
        curr.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> res;
    string curr = "";
    
    solve(digits, 0, curr, res);
    
    return res;
}

// GFG - Variant
/*
GFG - Possible Words From Phone Digits : Medium

Given an array arr[] containing digits, 
generate all possible words that can be formed by pressing these digits on a phone keypad, 
as shown in the figure. 
Digits 0 and 1 do not map to any letters, so they do not contribute to the generated combinations.

Note: Return the combinations in any order. The driver code will print them in sorted order.

Examples :-

Input: arr[] = [2, 3]
Output: [ad, ae, af, bd, be, bf, cd, ce, cf]
Explanation: When we press 2 and 3 total 3 x 3 = 9 possible words formed.

Input: arr[] = [2]
Output: [a, b, c]
Explanation: When we press 2 total 3 possible words formed.

Constraints :-
• 1 ≤ arr.size() ≤ 9
• 0 ≤ arr[i] ≤ 9
*/

/*
The problem is nearly same as leetcode but here we can have 0 & 1 in the passed digits as well.
Since 0 & 1 are not mapped to any letters, we have to skip these characters and move to the next digits for combinations.
*/
vector<string> letterMap = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  
void recurse(vector<int>& arr, int ind, string& curr, vector<string>& res) {
    if (ind == arr.size()) {
        res.push_back(curr);
        return;
    }
    
    string letters = letterMap[arr[ind]];
    
    if (letters == "")      
        recurse(arr, ind + 1, curr, res);
    // we could also use the condition : `if (arr[ind] == 0 || arr[ind] == 1)` for this skipping 
    
    for (char ch : letters) {
        curr.push_back(ch);
        recurse(arr, ind + 1, curr, res);
        curr.pop_back();
    }
}

vector<string> possibleWords(vector<int>& arr) {
    vector<string> res;
    string curr = "";
    
    recurse(arr, 0, curr, res);
    
    return res;
}

int main() {
    return 0;
}