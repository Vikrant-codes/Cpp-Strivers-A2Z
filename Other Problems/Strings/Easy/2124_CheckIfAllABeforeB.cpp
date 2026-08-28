/*
Leetcode - 2124. Check if All A's Appears Before All B's : Easy

Given a string s consisting of only the characters 'a' and 'b', 
return true if every 'a' appears before every 'b' in the string. 
Otherwise, return false.

Examples :-

Input: s = "aaabbb" __ Output: true
Explanation:
The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
Hence, every 'a' appears before every 'b' and we return true.

Input: s = "abab" __ Output: false
Explanation:
There is an 'a' at index 2 and a 'b' at index 1.
Hence, not every 'a' appears before every 'b' and we return false.

Input: s = "bbb" __ Output: true
Explanation:
There are no 'a's, hence, every 'a' appears before every 'b' and we return true.

Constraints :-
• 1 <= s.length <= 100
• s[i] is either 'a' or 'b'.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) ___ Space Complexity : O(1)

/*
>> Approach - 1
We want to check that all A's come before all B's, 
so we can simply find the index position of the last 'a' in string s, 
and the index position of the first 'b' in s.

Now, we return true if the first B comes after the last A.

We used two variables lastAPos & lastBPos both initialized with the value `-1`, 
at the end we can simply check firstBPos > lastAPos.
But, this will give incorrect output for some edgecases:- When string contains only a's.
For this edgecase, firstBPos would remain -1 and hence comparing `firstBPos > lastAPos` would return false.
So, we can use this conditional check `firstBPos == -1` to handle such cases.
*/
bool checkString1(string s) {
    int n = s.length();
    int lastAPos = -1, firstBPos = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') 
            lastAPos = i;
        
        else if (firstBPos == -1) 
            firstBPos = i;
    }

    return (firstBPos == -1) || firstBPos > lastAPos;
}

/*
Approach - 2
We can check the string in a slightly different way. 
We iterate from the end using a pointer `i` and stop our pointer at the first 'a' encountered while iterating from back 
(this is actually the last 'a' in string s)
Now, we return true if string contains all a's from this position to the 0th index.
So, we can simply iterate from this position to 0th index and return true if no 'b' is encountered.
- We can move the pointer i until a 'b' is encountered. 
- Either the pointer i will fully traverse the string s and become -1 (this will happen if no b is encountered while searching)
- Or, the pointer will stop at the position where b is encountered.
- So, we can use the condition `i == -1` and return accordingly.
*/
bool checkString2(string s) {
    int i = s.size()-1;
    while (i >= 0 && s[i] == 'b') i--;
    // now i points at last 'a' of string s

    // we simply check that no 'b' should exist between 0 to `i`
    while (i >= 0 && s[i] == 'a') i--;
    
    // this while loop will end when either i becomes -1 (all a's remaining) or a 'b' is encountered
    return i == -1;
}

/*
Approach - 3
Another way to think about the "all A's before all B's" condition is that 
- no 'a' should be followed by a 'b', i.e., if index `i` has 'a' then `i-1` must not be a 'b'
or conversely
- no 'b' should follow 'a', i.e., if index `i` has 'b' then `i+1` must not be a 'a'

Or, we just have to check that string don't have any occurrence of the substring "ba".
*/
bool checkString3(string s) {
    int n = s.length();
    
    for (int i = 0; i < n-1; i++)
        if (s[i] == 'b' && s[i+1] == 'a')
            return false;

    return true;
}


int main() {
    return 0;
}