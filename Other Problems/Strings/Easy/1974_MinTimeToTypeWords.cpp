/*
Leetcode - 1974. Minimum Time to Type Word Using Special Typewriter : Easy

There is a special typewriter with lowercase English letters 'a' to 'z' arranged in a circle with a pointer. 
A character can only be typed if the pointer is pointing to that character. 
The pointer is initially pointing to the character 'a'.

Each second, you may perform one of the following operations:
- Move the pointer one character counterclockwise or clockwise.
- Type the character the pointer is currently on.

Given a string word, return the minimum number of seconds to type out the characters in word.

Examples :-

Input: word = "abc" __ Output: 5
Explanation: 
The characters are printed as follows:
- Type the character 'a' in 1 second since the pointer is initially on 'a'.
- Move the pointer clockwise to 'b' in 1 second.
- Type the character 'b' in 1 second.
- Move the pointer clockwise to 'c' in 1 second.
- Type the character 'c' in 1 second.

Input: word = "bza" __ Output: 7
Explanation:
The characters are printed as follows:
- Move the pointer clockwise to 'b' in 1 second.
- Type the character 'b' in 1 second.
- Move the pointer counterclockwise to 'z' in 2 seconds.
- Type the character 'z' in 1 second.
- Move the pointer clockwise to 'a' in 1 second.
- Type the character 'a' in 1 second.

Input: word = "zjpc" __ Output: 34
Explanation:
The characters are printed as follows:
- Move the pointer counterclockwise to 'z' in 1 second.
- Type the character 'z' in 1 second.
- Move the pointer clockwise to 'j' in 10 seconds.
- Type the character 'j' in 1 second.
- Move the pointer clockwise to 'p' in 6 seconds.
- Type the character 'p' in 1 second.
- Move the pointer counterclockwise to 'c' in 13 seconds.
- Type the character 'c' in 1 second.

Constraints:-
- 1 <= word.length <= 100
- word consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(1)
/*
The pointer can move to the desired character in two ways :- Suppose we want to move to 'p' and pointer is currently at 'a'
- By moving clockwise to reach the desired character (so pointer moves a ... b ... c ... d ... .... p) 
    this would take 'p' - 'a' moves = 15 moves 
- By moving in counter-clockwise direction (pointer moves a ... z ... y ... x ... .... p)
    this would take 26 - ('p' - 'a') moves = 11 moves

We should choose the direction which is faster to access the desired character.

For each character, we need to do -
- Find the time the pointer would need to reach the current character by moving in clockwise & counter-clockwise direction.
- Choose the minimum time out of the two ways.
- 1 sec would be required to print the character itself.
*/
int minTimeToType(string word) {
    int ans = 0;
    char last = 'a';

    for (char& ch : word) {
        int diff = abs(ch - last);       // the difference in position in current character & pointer's current pointed char
        int move = min(diff, 26 - diff);

        ans += move;
        ans++;              // 1 sec time to print the character
        last = ch;
    }

    return ans;
}

int main() {

    return 0;
}