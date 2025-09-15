/*
Leetcode - 2396. Strictly Palindromic Number

An integer n is strictly palindromic if, for every base b between 2 and n - 2 (inclusive), the string representation of the integer n in base b 
is palindromic.
Given an integer n, return true if n is strictly palindromic and false otherwise.
A string is palindromic if it reads the same forward and backward.

Examples :-

Input: n = 9 __ Output: false
Explanation: In base 2: 9 = 1001 (base 2), which is palindromic.
In base 3: 9 = 100 (base 3), which is not palindromic.
Therefore, 9 is not strictly palindromic so we return false.
Note that in bases 4, 5, 6, and 7, n = 9 is also not palindromic.

Input: n = 4 __ Output: false
Explanation: We only consider base 2: 4 = 100 (base 2), which is not palindromic.
Therefore, we return false.

Constraints : 4 <= n <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

/*
Observations :- 
For a integer n, We need to check for the string representation of the integer n for every base 2 to (n-2). 
We observe that for every integer n > 4 .. the representation of n in base (n-2) is '12' which is not palindrome
This is because for base n-2, n can be represented as n = (n-2) * 1 + 2 .. which gives representation '12' . 
This is true for every integer n > 4 .. i.e. for every integer n (>4) the representation in base (n-2) is always '12' which is not palindrome
In case of n = 4 :- base = n - 2 = 4 - 2 = 2.. the binary representation of 4 is 100 which is also not palindrome. 

We observe that for every integer n in range (4, 10^5) :- the representation in base (n-2) is always non-palindrome so we return false as the 
number can thus not be a strictly palindrome number. 
*/

bool isStrictlyPalindromic(int n) {
    return false;
}

int main() {

    return 0;
}