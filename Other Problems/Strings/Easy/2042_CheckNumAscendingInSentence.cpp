/*
Leetcode - 2042. Check if Numbers Are Ascending in a Sentence : Easy

A sentence is a list of tokens separated by a single space with no leading or trailing spaces. 
Every token is either a positive number consisting of digits 0-9 with no leading zeros, 
or a word consisting of lowercase English letters.

For example, "a puppy has 2 eyes 4 legs" is a sentence with seven tokens: 
"2" and "4" are numbers and the other tokens such as "puppy" are words.

Given a string s representing a sentence, 
you need to check if all the numbers in s are strictly increasing from left to right 
(i.e., other than the last number, each number is strictly smaller than the number on its right in s).

Return true if so, or false otherwise.

Examples :-

Input: s = "1 box has 3 blue 4 red 6 green and 12 yellow marbles"
Output: true
Explanation: The numbers in s are: 1, 3, 4, 6, 12.
They are strictly increasing from left to right: 1 < 3 < 4 < 6 < 12.

Input: s = "hello world 5 x 5"
Output: false
Explanation: The numbers in s are: 5, 5. They are not strictly increasing.

Input: s = "sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"
Output: false
Explanation: The numbers in s are: 7, 51, 50, 60. They are not strictly increasing.
 
Constraints :-
- 3 <= s.length <= 200
- s consists of lowercase English letters, spaces, and digits from 0 to 9, inclusive.
- The number of tokens in s is between 2 and 100, inclusive.
- The tokens in s are separated by a single space.
- There are at least two numbers in s.
- Each number in s is a positive number less than 100, with no leading zeros.
- s contains no leading or trailing spaces.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n) __ Space Complexity : O(n) 
/*
Approach :-
- Extract all the numbers from the sentence.
- Store these numbers in an array (in the same order as they appear in sentence).
- Check if the array contains elements in a strictly increasing manner. Return true or false accordingly
*/
bool areNumbersAscendingNaive(string s) {
    stringstream ss(s);         // initialize stringstream with the sentence
    vector<int> numbers;
    string word = "";

    // extract words from the sentence
    while (ss >> word) {
        // if the extracted word is a number, we add this number to the array
        // to check if the extracted word is a number, we check if the word's first character is a digit
        if ( isdigit(word[0]) ) {
            // convert the word to integer :- using stringstream or manually converting digits to integer
            int x = 0;
            for (char c : word) 
                x = x * 10 + (c - '0');
            // Converting string to integer using istringstream
            // istringstream iss(word);
            // int x;
            // iss >> x;
            numbers.push_back(x);
        }
    }

    for (int i = 1; i < numbers.size(); i++)
        if (numbers[i] <= numbers[i-1])
            return false;
    
    return true;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Core Idea / Intuition

To check whether the numbers in the sentence are strictly ascending, 
every number that appears later must be greater than the number that appeared before it.

So the idea is:
1. Traverse the string character by character.
2. Whenever you encounter a digit, it means a number is starting.
3. Extract the complete number (because numbers can have multiple digits like 12, 45, etc.).
4. Compare this number with the previous number you saw.
5. If the current number is less than or equal to the previous number → return false.
6. Otherwise update prev and continue scanning the string.

So essentially the algorithm is:
- Keep track of the last number seen (prev).
- Parse numbers from the string as you encounter digits.
- Check if each new number > previous number.
- If this holds for the entire string → return true.

>> Why this works ?
The problem only cares about the relative order of numbers, not the words.
So we simply ignore non-digits and only process numbers when they appear.

Also, consider the string contains the numbers a, b, c, d & e (in this order).
Now, the numbers must be ascending means a < b < c < d < e.
We only compare the current number with the previous number because If every number is greater than the one just before it, 
then it will automatically be greater than all numbers that came earlier.

Example:
    Numbers in sentence:    2 5 9 15
    Checks we perform:
    - 5 > 2
    - 9 > 5
    - 15 > 9
    Since each number is greater than the previous one, we can be sure:
    - 9 > 2 (since 9 > 5 and 5 > 2, so we don't need to compare 9 & 2)
    - 15 > 5
    - 15 > 2
*/
bool areNumbersAscending1(string s) {
    int n = s.length();

    int prevNum = -1, num = 0;
    
    for (int i = 0; i < n; i++) {
        if ( isdigit(s[i]) ) {
            num = (s[i] - '0');
            i++;
            while (i < n && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }

            // now compare this number with the previous number
            if (num <= prevNum) 
                return false;
            prevNum = num;
            num = 0;
        }
    }
    
    return true;
}

// Same approach as above, better implementation
bool areNumbersAscending2(string s) {
    int n = s.length();
    int prev = -1;

    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) {
            int num = 0;
            while (i < n && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            
            if (num <= prev) return false;
            prev = num;
        }
    }

    return true;
}

// Using stringstream to extract integers from the string sentence
/*
Idea
1. Use stringstream to split the sentence into words.
2. For each extracted word:
    If the first character is a digit, the word represents a number.
3. Convert that word to an integer using istringstream.
4. Compare it with the previous number (prev).
5. If x <= prev, the numbers are not strictly ascending, so return false.
6. Otherwise update prev = x and continue.
*/
bool areNumbersAscending3(string s) {
    stringstream ss(s);         // initialize stringstream with the sentence
    string word = "";
    int prev = -1;

    // extract words from the sentence
    while (ss >> word) {
        // if the extracted word is a number, compare it with the previous number
        if ( isdigit(word[0]) ) {
            // convert the word to integer :- using stringstream or manually converting digits to integer
            istringstream iss(word);
            int x;
            iss >> x;
            if (x <= prev) return false;
            prev = x;
        }
    }

    return true;
}

int main() {
    return 0;
}