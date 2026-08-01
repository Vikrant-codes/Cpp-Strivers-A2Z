// Recursive implementation of atoi() function

// Leetcode - 8. String to Integer (atoi) : Medium
/*
Leetcode - 8. String to Integer (atoi) : Medium

Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.

The algorithm for myAtoi(string s) is as follows:

1. Whitespace: 
    Ignore any leading whitespace (" ").
2. Signedness: 
    Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
3. Conversion: 
    Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. 
    If no digits were read, then the result is 0.
4. Rounding: 
    If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], 
    then round the integer to remain in the range. 
    Specifically, integers less than -2^31 should be rounded to -2^31, 
    and integers greater than 2^31 - 1 should be rounded to 2^31 - 1.

Return the integer as the final result.

>> Examples :-

-> Input: s = "42" __ Output: 42
Explanation:
The underlined characters are what is read in and the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^

-> Input: s = " -042" __ Output: -42
Explanation:
Step 1: "   -042" (leading whitespace is read and ignored)
            ^
Step 2: "   -042" ('-' is read, so the result should be negative)
             ^
Step 3: "   -042" ("042" is read in, leading zeros ignored in the result)
               ^

-> Input: s = "1337c0d3" __ Output: 1337
Explanation:
Step 1: "1337c0d3" (no characters read because there is no leading whitespace)
         ^
Step 2: "1337c0d3" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "1337c0d3" ("1337" is read in; reading stops because the next character is a non-digit)
             ^

-> Input: s = "0-1" __ Output: 0
Explanation:
Step 1: "0-1" (no characters read because there is no leading whitespace)
         ^
Step 2: "0-1" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "0-1" ("0" is read in; reading stops because the next character is a non-digit)
          ^

-> Input: s = "words and 987" __ Output: 0
Explanation:
Reading stops at the first non-digit character 'w'.

>> Constraints :-
• 0 <= s.length <= 200
• s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.
*/

#include <bits/stdc++.h>
using namespace std;

/*
>> Algorithm to implement the atoi() function recursively:

• Define a helper function that takes the string s, current index i, current result num, and sign.
• Recursively skip leading whitespaces until a non-whitespace character is found.
• Handle the sign if present (positive or negative).
• Recursively process each digit:
    • Continue until the end of the string or a non-digit character is encountered.
    • For each digit, update the result.
• Clamp the result to INT_MIN or INT_MAX to handle overflow conditions.

>> Time Complexity: O(n) since each character is processed once.
>> Space Complexity: O(n) since the recursion stack grows up to n calls.
*/

// helper method to recursively process the digits in the string and convert it to an integer.

// Using long long to store the current number to avoid overflow during the calculation.
int helperLongLong(string& s, int i, int n, bool isPositive, long long num) {
    if (i == n || ! isdigit(s[i]) ) {
        return (int) (isPositive ? num : -num);
    }

    int dig = s[i] - '0';
    num = num * 10 + dig;
    
    if (num > INT_MAX) 
        return isPositive ? INT_MAX : INT_MIN;
    
    if (isPositive && num == INT_MAX) return INT_MAX;

    return helper(s, i+1, n, isPositive, num);
}

// Using only int variables to store the number and check for overflow before it happens.
int helper(string& s, int i, int n, bool isPositive, int num) {
    if (i == n || ! isdigit(s[i]) ) {
        return isPositive ? num : -num;
    }

    int dig = s[i] - '0';

    // check for integer limits

    // if num > INT_MAX / 10, then adding any digit will cause overflow, so return INT_MAX or INT_MIN based on the sign.
    if (num > INT_MAX / 10) 
        return isPositive ? INT_MAX : INT_MIN;

    // if num == INT_MAX / 10, 
    // then adding a digit greater than 7 will cause overflow for positive numbers, 
    // and greater than 8 for negative numbers.
    if (num == INT_MAX / 10) {
        // if sign is +ve, then we return INT_MAX if the digit is >= 7, else we can safely add the digit.
        if (isPositive) {
            if (dig >= 7) return INT_MAX;    
        }
        // if sign is -ve, then we return INT_MIN if the digit is > 7, else we can safely add the digit.
        else {
            if (dig > 7) return INT_MIN; 
        }
    }

    num = num * 10 + dig;

    return helper(s, i+1, n, isPositive, num);
}

int myAtoi(string s) {
    int n = s.size();

    int i = 0;
    
    // Ignore leading whitespaces
    while (i < n && s[i] == ' ') i++;
    
    if (i == n) return 0;
    
    // Check for sign
    bool isPositive = true;
    if (s[i] == '-' || s[i] == '+') {
        if (s[i] == '-') isPositive = false;
        i++;
    }

    // long long num = 0;
    // return helperLongLong(s, i, n, isPositive, num);

    // Using only int variables to store the number and check for overflow before it happens.
    int num = 0;
    return helper(s, i, n, isPositive, num);
}

int main() {
    return 0;
}