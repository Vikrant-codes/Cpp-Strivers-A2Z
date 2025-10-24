/*
Leetcode - 8. String to Integer (atoi) : Medium

Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.

The algorithm for myAtoi(string s) is as follows:
- Whitespace: Ignore any leading whitespace (" ").
- Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
- Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string 
is reached. If no digits were read, then the result is 0.
- Rounding: If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], then round the integer to remain in 
the range. Specifically, integers less than -2^31 should be rounded to -2^31, 
and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.

Return the integer as the final result.

Examples :- 

Input: s = "42" __ Output: 42

Input: s = " -042" __ Output: -42 
Explanation : The leading whitespaces are not considered. - implies number is negative. 042 amounts to 42.

Input: s = "1337c0d3" __ Output: 1337
Explanation : The reading stops after encountering a non-digit character ('c' here), so only 1337 is returned.

Input: s = "0-1" __ Output: 0
Explanation : Firstly, 0 is read in and then comes '-' a non-digit character in between digits so reading stops & 0 is returned.

Input: s = "words and 987" __ Output: 0
Explanation : There are no leading whitespaces or '+'/'-' symbol. Reading stops after encountering the non-digit character 'w'.

Input: s = "2147483650" __ Output: 2147483647 
Explanation : '2147483650' is beyond integer range so we return the maximum positive integer value i.e. '2147483647'

Input: s = "-2147483648" __ Output: -2147483648

Constraints :-
0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
🧠 Intuition
The goal is to manually simulate how numbers are read from strings, similar to how the atoi() function works in C.
We parse the string carefully step-by-step to handle:
1. Leading spaces
2. Optional sign (+ or -)
3. Consecutive digits forming the number
4. Overflow / underflow beyond 32-bit integer range
5. Stop at first non-digit after digits start

⚙️ Algorithm

1. Initialize variables
-- i = 0: pointer to traverse the string
-- sign = 0: 0 → positive, 1 → negative
-- num = 0: accumulated number
-- mx_lim = INT_MAX / 10 = 214748364: helps detect overflow before it happens

2. Skip leading whitespaces : Keep incrementing i while s[i] == ' '.

3. Check sign : If s[i] == '+' keep sign = 0. If s[i] == '-' keep sign = 1. Increment i to read the next character.

4. Convert digits : We need to check for consecutive digits only so While s[i] is a digit: 
-- Convert to integer using digit = s[i] - '0'.
-- Before multiplying num by 10, check if adding another digit would cause overflow. 
   We check whether adding the current digit would cause overflow or not. We do so by checking certain conditions like -
   If num > mx_lim → overflow will definitely occur so return INT_MAX / INT_MIN according to sign.
   Else if num == mx_lim then adding new digit might cause overflow depending on the value of digit 
        For positive: last safe digit is 7 (since INT_MAX = 2147483647)
        For negative: last safe digit is 8 (since INT_MIN = -2147483648)
-- Update num = num * 10 + digit.
-- Move i forward.

5. Return result : Return num if positive, else -num.
*/

int myAtoi(string s) {
    int n = s.size();
    int i = 0;          // pointer to traverse the string
    int sign = 0;       // sign bit: 0 means no is +ve and 1 means -ve
    int mx_lim = INT_MAX / 10;      // to check for maximum limit 
    // ignore leading whitespaces
    while (i < n && s[i] == ' ') i++;
    
    // check sign bit (if present)
    if (s[i] == '-' || s[i] == '+') {
        sign = (s[i] == '+') ? 0 : 1;
        i++;
    }
    
    int num = 0;
    while ( isdigit(s[i]) ) {
        int digit = s[i] - '0';     // current digit
        // INT_MAX = 2,147,483,647 , INT_MIN = -2,147,483,648
        if (num >= mx_lim) {
            if (num > mx_lim) {
                return sign == 0 ? INT_MAX : INT_MIN;
            }
            // else condition when num == mx_lim = 214748364
            else {
                if (sign == 0 && digit > 6) return INT_MAX;
                if (sign == 1 && digit > 7) return INT_MIN;
            }
        }
        num = num * 10 + digit;
        i++;
    }
    return sign == 0 ? num : -1 * num;
}

int main() {

    return 0;
}