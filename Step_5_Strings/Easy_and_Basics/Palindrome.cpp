/*
Leetcode - 125. Valid Palindrome : Easy

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, 
it reads the same forward and backward. Alphanumeric characters include letters and numbers.
Given a string s, return true if it is a palindrome, or false otherwise.

Examples :

Input: s = "A man, a plan, a canal: Panama" __ Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Input: s = "race a car" __ Output: false
Explanation: "raceacar" is not a palindrome.

Input: s = " " __ Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
 
Constraints :- 1 <= s.length <= 2 * 10^5
s consists only of printable ASCII characters.

--> The problem states to check for palindrome after removing non-alphanumeric characters and ignoring cases.
So while solving we also need to consider the digits along with characters. like "abc4dcba" is not a palindrome but "a1c4c1a" is a palindrome.
*/

#include <bits/stdc++.h>
using namespace std;

// Two Pointer Approach : Time Complexity : O(n) & Space Complexity : O(1)
/*
🔑 Intuition
A palindrome reads the same forward and backward, but here we only consider letters and digits, ignoring spaces, punctuation, and case.
So the task is essentially:
-- Compare the "filtered" string (only alphanumeric, all lowercase) with its reverse.
-- But instead of building a new string (which costs extra space), we can use two pointers to directly check characters from both ends.

🔑 Approach : We can use two pointers to check and compare the equality of characters at both ends
1. Initialize two pointers: i = 0 (start of string) __ j = s.size() - 1 (end of string)
2. while i & j doesn't cross each other
    a. Move i forward until it points to an alphanumeric character or crosses j
    b. Move j backward until it points to an alphanumeric character or crosses i
    c. If characters at i and j (after converting to lowercase) are not equal, return false
    d. Move both pointers inward (i++, j--)
3. If we complete the loop without mismatches, return true 

We move i forward & j backward until they point to alphanumeric characters, ensuring we only compare relevant characters.
To do this we use while condition while (i < j && !isalnum(s[i])) i++; while (i < j && !isalnum(s[j])) j--;
*/
bool isPalindrome(string s) {
    int i = 0, j = s.size()-1;
    while (i < j) {
        while (i < j && !isalnum(s[i])) i++;
        while (i < j && !isalnum(s[j])) j--;

        // check the characters at both ends
        if (tolower(s[i]) != tolower(s[j])) return false;
        i++; j--;
    }
    return true;
}

int main() {
    string s = "A man, a plan, a canal: Panama";
    cout << (isPalindrome(s) ? "true" : "false") << endl;
    return 0;
}