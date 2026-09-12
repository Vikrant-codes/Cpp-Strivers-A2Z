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

int main() {
    return 0;
}