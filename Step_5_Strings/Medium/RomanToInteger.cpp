/*
Leetcode - 13. Roman to Integer : Easy

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. 
The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. 
Instead, the number four is written as IV. Because the one is before the five we subtract it making four. 
The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:
- I can be placed before V (5) and X (10) to make 4 and 9. 
- X can be placed before L (50) and C (100) to make 40 and 90. 
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

Examples :- 

Input: s = "III" __ Output: 3
Explanation: III = 3.

Input: s = "LVIII" __ Output: 58
Explanation: L = 50, V= 5, III = 3.

Input: s = "MCMXCIV" __ Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints :-
1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].
*/

#include <bits/stdc++.h>
using namespace std;

// For all approaches :- Time Complexity : O(n) __ Space Complexity : O(1)

/*
We traverse the string from start to end and for every character we add the corresponding value to the sum. Now in case
of subtractions like 'IV', 'IX', 'XL', 'XC', 'CD', 'CM' we keep a last variable to keep track of the last variable encountered.
Now if we encounter 'V' or 'X' we check if last was equal to 'I' in that case we subtract 2 * value of 'I' becuase 
'IV' corresponds to 4 and 'I' and 'V' individually corresponds to 6. 
We do similar for cases like 'XL', 'XC', 'CD', 'CM'.
*/
int romanToInt(string s) {
    char last = '_';
    int sum = 0;
    for (char c : s) {
        // we add the corrseponding value of each roman character to the total sum
        if (c == 'I') sum += 1;
        else if (c == 'V') sum += 5;
        else if (c == 'X') sum += 10;
        else if (c == 'L') sum += 50;
        else if (c == 'C') sum += 100;
        else if (c == 'D') sum += 500;
        else if (c == 'M') sum += 1000;
        //for numbers like 'IV' : we subtract 2 * earlier character becuase while iterating thorugh the characters 
        //we added 'I' + 'V' individually to get sum = 6 but the sum should have been '4' so we minus twice of earlier character
        if (last == 'I' && (c == 'V' || c == 'X')) sum -= 2;
        else if (last == 'X' && (c == 'L' || c == 'C')) sum -= 20;
        else if (last == 'C' && (c == 'D' || c == 'M')) sum -= 200;
        last = c;
    }
    return sum;
}

// Using Map (to map roman characters to integer values) :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
We use a hashmap to retrieve the corresponding values of a character. 
Move through the string from the end and add corresponding char values to the sum. 
In cases like 'IV', 'IX', 'XL', 'XC', 'CD', 'CM' : since we moving from rear end we check if last value was greater than current 
which is true for such cases, and if true we subtract the current value instead of adding. So 'XC' is processed like this
first 'C' comes so 100 is added then 'X' comes and we see that 'X' < 'C' so instead of adding it, we subtract its value
so sum becomes 100 - 10 = 90.
*/
int romanToIntHashMap(string s) {
    unordered_map<char, int> mpp { {'I',1}, {'V',5}, {'X',10},
    {'L',50}, {'C',100}, {'D',500}, {'M',1000} };
    int sum = 0, last = 0;
    
    for (int i = s.size()-1; i >= 0; i--) {
        if (last > mpp[s[i]]) sum -= mpp[s[i]];
        else sum += mpp[s[i]];
        last = mpp[s[i]];
    }
    return sum;
}

// Striver Sheet Approach :- Time Complexity : o(n) __ Space Complexity : O(1)
/*
Algorithm
1. Understand that Roman numerals are generally written in descending order of value, and their values are added.
2. However, when a smaller value appears before a larger one, it indicates subtraction instead of addition.
3. To handle this, scan the string from left to right and compare each character with the one after it.
4. If the current symbol is smaller than the next, treat it as a subtractive pair.
5. Otherwise, treat the symbol as a standalone value and add it normally.
6. The final character is always added since there's nothing after it to compare.
*/
int romanToInt(string s) {
    int res = 0;
    // Map of Roman numerals to their integer values
    unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };
    // Iterate through the string, except the last character
    for (int i = 0; i < s.size() - 1; i++) {
        // Subtract if current numeral is less than the next
        if (roman[s[i]] < roman[s[i + 1]]) res -= roman[s[i]];
        // Otherwise, add the current value
        else res += roman[s[i]];
    }
    // Add the value of the last character
    return res + roman[s.back()];
}

int main() {
    return 0;
}