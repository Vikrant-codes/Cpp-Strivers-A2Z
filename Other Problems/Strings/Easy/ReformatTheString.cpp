/*
Leetcode - 1417. Reformat The String : Easy

You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
You have to find a permutation of the string where no letter is followed by another letter and 
no digit is followed by another digit. That is, no two adjacent characters have the same type.

Return the reformatted string or return an empty string if it is impossible to reformat the string.

Examples :- 

Input: s = "a0b1c2" __ Output: "0a1b2c"
Explanation: No two adjacent chars have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.

Input: s = "leetcode" __ Output: ""
Explanation: "leetcode" has only characters so we cannot separate them by digits.

Input: s = "1229857369" __ Output: ""
Explanation: "1229857369" has only digits so we cannot separate them by characters.
*/

#include <bits/stdc++.h>
using namespace std;

/*
✅ Intuition
We want to find a permutation where no two adjacent characters have the same type. 
i.e., we want a permutation having digits & alphabets in alternate fashion like adad...ad where a is alphabet & d is digit.

This arrangement in alternate fashion is possible only if the count of alphabets & digits is same or differ by 1.
i.e. when alphabet_count - digit_count is either 1 or 0 or -1.
If, the difference between alphabet_count & digit_count is not in [1, 0, -1], then such alternating arrangement is not possible
In that case we return empty string "".
So, we check the absolute value of difference of alphabet_count & digit_count and return empty str if the diff is greater than 1.

Possible Cases :-
>> Case 1 :- When alphabet_count - digit_count = 0, i.e., alphabet_count = digit_count
In this case we can arrange the alphabets and digits either in adad..ad (alphabet-first) fashion or dada..da(digit-first) fashion 

>> Case 2 :- When alphabet_count - digit_count = 1, i.e., alphabet_count = digit_count + 1
here, the answer permutation must be in format adad..ada (starting & ending with alphabet)

>> Case 3 :- When alphabet_count - digit_count = -1, i.e., alphabet_count = digit_count - 1
here, the answer permutation must be in format dadad..ad (starting & ending with digit)

🎯 Algorithm
1. Initialize two vectors 'letters' and 'digits' to segregate alphabets & digits from the alphanumeric string.
2. Traverse the string and segregate the alphabets & digits into respective vectors.
3. Initialize sizes of the two vectors, s1 = letters.size(), s2 = digits.size().
4. Check the absolute difference of the two sizes and if the difference is greater than 1, return empty str "".
    if (abs(s1 - s2) > 1) return "";
5. Initialize an empty ans string.
6. Arrange the alphabets and digits in "adad..ad" fashion until any of the vector runs out of character.
7. If s1 > s2, i.e. letters > digits, place a letter at the end of ans string to arrange in "adad..ada" fashion
8. If s1 < s2, i.e. digits > letters, place a digit at the start of ans string to arrange in "dada..da" fashion
9. Return ans string.
*/
string reformat(string s) {
    vector<char> letters; // vector to store all lowercase alphabets from string s 
    vector<char> digits;  // vector to store all digits from string s
    for (char c : s) {
        if (c >= 'a' && c <= 'z') letters.push_back(c);
        else digits.push_back(c);
    }
    int s1 = letters.size();
    int s2 = digits.size();
    if (abs(s1 - s2) > 1) return "";
    string ans = "";
    int n = min(s1, s2);
    for (int i=0; i<n; i++) {
        ans += letters[i];
        ans += digits[i];
    }
    // if letters are more than digits, then place a letter at the last and return ans
    if (s1 > s2) return ans + letters[n];
    // if digits are more then place a digit at the start and return ans
    if (s2 > s1) return digits[n] + ans;
    // if both digits & letters are equal
    return ans;
}

int main() {
    return 0;
}