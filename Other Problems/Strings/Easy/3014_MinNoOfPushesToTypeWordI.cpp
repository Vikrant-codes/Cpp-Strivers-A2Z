/*
Leetcode - 3014. Minimum Number of Pushes to Type Word I : Easy

You are given a string word containing distinct lowercase English letters.

Telephone keypads have keys mapped with distinct collections of lowercase English letters, 
which can be used to form words by pushing them. 
For example, the key 2 is mapped with ["a","b","c"], we need to push the key one time to type "a", 
two times to type "b", and three times to type "c" .

It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters. 
The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key. 
You need to find the minimum number of times the keys will be pushed to type the string word.

Return the minimum number of pushes needed to type word after remapping the keys.

An example mapping of letters to keys on a telephone keypad is given below. 
Note that 1, *, #, and 0 do not map to any letters.

Examples :-

Input: word = "abcde"
Output: 5
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
Total cost is 1 + 1 + 1 + 1 + 1 = 5.
It can be shown that no other mapping can provide a lower cost.

Input: word = "xycdefghij"
Output: 12
Explanation: The remapped keypad given in the image provides the minimum cost.
"x" -> one push on key 2
"y" -> two pushes on key 2
"c" -> one push on key 3
"d" -> two pushes on key 3
"e" -> one push on key 4
"f" -> one push on key 5
"g" -> one push on key 6
"h" -> one push on key 7
"i" -> one push on key 8
"j" -> one push on key 9
Total cost is 1 + 2 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 = 12.
It can be shown that no other mapping can provide a lower cost.

Constraints :-
• 1 <= word.length <= 26
• word consists of lowercase English letters.
• All letters in word are distinct.
*/

#include <bits/stdc++.h>
using namespace std;

/*
# Greedy Idea

The key observation is that we are free to remap the letters however you want.

There are 8 available keys (2–9).

>> Idea
• The first letter assigned to a key requires 1 push.
• The second letter on the same key requires 2 pushes.
• The third letter requires 3 pushes, and so on.
Since every character in word is distinct, each letter is typed exactly once.

So to minimize pushes:
• Put the first 8 letters as the first character on each key → 1 push each
• The next 8 letters become the second character on each key → 2 pushes each
• The next 8 letters → 3 pushes each
• And so on.

Example: word = "abcdefghij"
There are 10 distinct letters.

Assign:
    Key2 : a
    Key3 : b
    Key4 : c
    Key5 : d
    Key6 : e
    Key7 : f
    Key8 : g
    Key9 : h
All these need 1 push.

Remaining:
    Key2 : a i
    Key3 : b j

Now:
    a,b,c,d,e,f,g,h -> 1 push each = 8
    i,j             -> 2 pushes each = 4

Answer = 12

>> Why does this greedy approach work?
Suppose you have 10 letters.
If one letter is placed in the second position (2 pushes) while another is in the first position (1 push), 
swapping them doesn't change the total because every letter appears exactly once.
Therefore, only the number of letters assigned to each push level matters, not which specific letters are assigned.
To minimize the total:
• Fill all 8 first-position slots first (cost = 1),
• then all 8 second-position slots (cost = 2),
• then third-position slots, and so on.
*/

// Approach-1 : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Algorithm
• Loop through the letters.
• For every letter at index i:
    cost = (i / 8) + 1

    because

    i = 0..7   -> 1 push
    i = 8..15  -> 2 pushes
    i = 16..23 -> 3 pushes
    ...
• Add all costs.
*/

int minimumPushes1(string word) {
    int n = word.length();
    int pushes = 0;

    for (int i = 0; i < n; i++) {
        // if (i < 8) pushes += 1;
        // else if (i < 16) pushes += 2;
        // else if (i < 24) pushes += 3;
        // else pushes += 4;

        // Insted of using the above 4 conditions, we can simply use pushes += (i / 8) + 1, as it works same as above 
        pushes += (i / 8) + 1;
    }

    return pushes;
}

// Approach-2 : Time Complexity : O(1) __ Space Complexity : O(1)
/*
Instead of iterating over every character, we can also directly compute the answer using the length of the string.

- Case 1: n <= 8
    Every letter occupies the first position on a key. Each letter requires only 1 push.
    | Answer = n × 1 = n

- Case 2: 9 <= n <= 16
    The first 8 letters require 1 push each. So, 8 pushes for the first 8 characters
    The remaining (n - 8) letters require 2 pushes each.
    | Answer = 8 + 2 × (n - 8)

- Case 3: 17 <= n <= 24
    First 8   (1 push each) -> 8 × 1 = 8
    Next 8    (2 push each) -> 8 × 2 = 16
    Remaining (3 push each) -> 3 × (n - 16)
    So,
    | Answer = 8 + 16 + 3 × (n - 16)

- Case 4: 25 <= n <= 26
    First 8   (1 push each) -> 8
    Next 8    (2 push each) -> 16
    Next 8    (3 push each) -> 24
    Remaining (4 push each) -> 4 × (n - 24)
*/

int minimumPushes2(string word) {
    int n = word.length();
    int ans = 0;

    if (n <= 8) ans = n;
    else if (n <= 16) ans = 8 + 2 * (n - 8);
    else if (n <= 24) ans = 8 + 16 + 3 * (n - 16);
    else ans = 8 + 16 + 24 + 4 * (n - 24);

    return ans;
}

int main() {
    return 0;
}