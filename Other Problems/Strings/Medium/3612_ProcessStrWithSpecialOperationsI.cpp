/*
Leetcode - 3612. Process String with Special Operations I : Medium

You are given a string s consisting of lowercase English letters and the special characters: *, #, and %.
Build a new string result by processing s according to the following rules from left to right:
- If the letter is a lowercase English letter append it to result.
- A '*' removes the last character from result, if it exists.
- A '#' duplicates the current result and appends it to itself.
- A '%' reverses the current result.
Return the final string result after processing all characters in s.

Examples :-

Input: s = "a#b%*" __ Output: "ba"
Explanation:
i	s[i]	Operation	Current result
0	'a'	Append 'a'	"a"
1	'#'	Duplicate result	"aa"
2	'b'	Append 'b'	"aab"
3	'%'	Reverse result	"baa"
4	'*'	Remove the last character	"ba"
Thus, the final result is "ba".

Input: s = "z*#" __ Output: ""
Explanation:
i	s[i]	Operation	Current result
0	'z'	Append 'z'	"z"
1	'*'	Remove the last character	""
2	'#'	Duplicate the string	""
Thus, the final result is "".

Constraints :-
- 1 <= s.length <= 20
- s consists of only lowercase English letters and special characters *, #, and %.
*/

#include <bits/stdc++.h>
using namespace std;

// Simulation Approach
/*
>> Complexity Analysis
Let:
• n = length of input string s
• m = maximum size of res during execution

Operation-wise Cost

1. Normal character :- res += ch;
-> Amortized: O(1)

2. * :- res.pop_back();
-> O(1)

3. % :- reverse(res);
-> The reverse function traverses the entire current string.
-> Cost: O(k) where k = res.size()

4. # :- res += res;
-> The entire current string is copied and appended.
-> Cost: O(k) where k = res.size()

>> Overall Time Complexity
The tricky part is #.
Consider: a####
Execution:
a      -> size 1
#      -> size 2
#      -> size 4
#      -> size 8
#      -> size 16
Work done: 1 + 2 + 4 + 8 = 15
In general, the total work is proportional to the total size of the generated string.
So: Time Complexity = O(L)
where L is the length of the final processed string (or more precisely, the total number of characters ever copied/reversed).

Since L can grow exponentially because of #, in terms of the input length n:
Worst-case Time Complexity = O(2ⁿ)
Example: a####################
The string doubles repeatedly.

>> Space Complexity 
We store the resulting string: string res;
So: Space Complexity = O(L)
where L is the final string length.
Again, in the worst case: Space Complexity = O(2ⁿ)

| Complexity                       | Value                            |
| -------------------------------- | -------------------------------- |
| Time                             | O(L) where L = final string size |
| Worst-case Time (in terms of n)  | O(2ⁿ)                            |
| Space                            | O(L)                             |
| Worst-case Space (in terms of n) | O(2ⁿ)                            |
*/

void reverse(string& str) {
    int l = 0, r = str.size()-1;
    while (l < r) {
        swap(str[l], str[r]);
        l++; r--;
    }
}

string processStr(string s) {
    string res = "";
    for (char ch : s) {
        if (ch == '*') {
            if (!res.empty()) {
                res.pop_back();
            }
        }
        else if (ch == '#') {
            res += res;
        }
        else if (ch == '%') {
            reverse(res);
        }
        else {
            res += ch;
        }
    }

    return res;
}

int main() {

    return 0;
}