/*
Leetcode - 1903. Largest Odd Number in String : Easy

You are given a string num, representing a large integer. Return the largest-valued odd integer (as a string) that is a non-empty 
substring of num, or an empty string "" if no odd integer exists.
A substring is a contiguous sequence of characters within a string.

Examples :-

Input: num = "52" __ Output: "5"
Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.

Input: num = "4206" __ Output: ""
Explanation: There are no odd numbers in "4206".

Input: num = "35427" __ Output: "35427"
Explanation: "35427" is already an odd number.
 
Constraints :- 1 <= num.length <= 10^5
num only consists of digits and does not contain any leading zeros.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
Observations :- 
- An odd number always ends with an odd digit. So, the last digits of an odd number can be 1, 3, 5, 7 or 9.
- Now, we know that every odd integer must end with an odd digit. So, the largest odd integer would be the one which has the 
  largest possible prefix and ends with a odd digit in the string.
- The prefix can start from the beginning of the string and then only the length of the prefix would be highest.
- So, we can start checking from the end of the string and find the first odd digit. The substring from the beginning of the 
  string to that odd digit would be our answer.
- Ex : Consider string "123456789012345680868". There are multiple odd numbers in the string like 123456789, 12345678901234567, 
    1234567890123456808687 etc.
    But the largest odd number would be the one that starts from the beginning of the string and ends at the last odd digit in the string.
    So, we simply need to find the last odd digit in the string and return the substring from the beginning of the string to that odd digit.
- If there is no odd digit in the string, then we return an empty string.
*/

string largestOddNumber(string num) {
    for (int i = num.length() - 1; i >= 0; i--) {
        int x = num[i] - '0';           // integer value at num[i]
        if (x % 2 == 1) {
            return num.substr(0, i+1);
        }  
    }
    return "";
}

int main() {

    return 0;
}