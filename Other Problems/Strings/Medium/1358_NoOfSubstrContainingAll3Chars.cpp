/*
Leetcode - 1358. Number of Substrings Containing All Three Characters : Medium

Given a string s consisting only of characters a, b and c.
Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Examples :-

Input: s = "abcabc" __ Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are 
"abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Input: s = "aaacb" __ Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Input: s = "abc" __ Output: 1

Constraints :-
- 3 <= s.length <= 5 x 10^4
- s only consists of a, b or c characters.
*/

#include <bits/stdc++.h>
using namespace std;

// Sliding Window Approach (My solution) : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
>> Intuition

We need to count all substrings that contain at least one 'a', 'b', and 'c'. 
Checking every substring would take O(n²), which is too slow. 
Instead, we use a sliding window to process the string in linear time.

Think of the window as the current substring s[i...j].

Expand the window by moving j to the right until the window contains all three characters.
Once the window becomes valid (contains 'a', 'b', and 'c'), 
we know that any substring obtained by extending the right end further will also remain valid, 
because adding more characters can never remove an existing 'a', 'b', or 'c'.

Ex - consider string :- "aabcabc",
now at j = 3, substring becomes "aabc", which is valid, 
now if we extend the right boundary to j = 4, substring becomes "aabca", which is also valid, and so on.
So, once a substring becomes valid, all the further substring formed by extending the right boundary will also be valid.
So, we can count all the valid substrings that can be formed with the current starting position i and 
ending at j or any index after j, which is (n - j) substrings.
Ex - for i = 0, and j = 3 (when substring becomes valid), 
the possible valid substrings are "aabc", "aabca", "aabcab", "aabcabc" (4 substrings) 
Also, (n - j) = (7 - 3) = 4.

This count shows how many valid substrings are possible from the current starting position, 
but what if we shift the starting position ?
To find out, we need to shrink the window from the left as much as possible while still keeping it valid.
Ex - "aabc" was the first valid substring, but if we shrink it one character from left it becomes "abc" which is also valid.
for both of these substrings, the ending can be at j or any index after j (total (n-j) substring for each starting index).

Now, instead of considering each valid substring one by one, 
we determine how many different starting positions can produce a valid window for the current j.

To do this, we shrink the window from the left as much as possible:
- Keep removing characters from the left while the window still contains all three characters.
- The moment removing one more character makes the window invalid, we stop.
- Every left boundary we removed before reaching this point represents a valid starting position.
If we moved the left boundary from i to k, then there are: (k - i) valid starting positions.

For each of these starting positions, the substring can end at j or any index after j, 
since extending the right boundary cannot invalidate the substring.

The number of possible ending positions is: (n - j)

Therefore, the total number of valid substrings contributed at this step is: (k - i) × (n - j)

After counting them, we set i = k and continue expanding the window by moving j further to the right.

Since both pointers only move forward and never backward, 
each character is added to and removed from the window at most once, 
giving an O(n) time complexity.
(both pointers i & j can move at most O(n) steps, so total moves will be O(n + n) = O(2*n) ~ O(n) )

>> Core Idea
- Expand the window until it contains all three characters (a, b, and c).
- Once the window is valid, shrink it from the left as much as possible while keeping it valid.
- The number of left positions removed (k - i) gives the number of valid starting positions for the current j.
- Since extending the right end never makes a valid window invalid, 
  each valid start can pair with every ending position from j to n - 1.
- Add the contribution: (k−i)×(n−j)
- Continue expanding the window and repeat until the end of the string.
*/

// we are using 'const vector<int>& freq' instead of 'vector<int> freq' to avoid copying the vector on every call.
bool containsAll(const vector<int>& freq) {
    if (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) 
        return true;
    return false;
}

int numberOfSubstrings1(string s) {
    vector<int> freq(3);

    int ans = 0, n = s.size();
    int i = 0, j = 0;

    while (i <= n - 3 && j < n) {
        freq[s[j] - 'a']++;
        if (containsAll(freq)) {
            int k = i;
            while (containsAll(freq)) {
                freq[s[k] - 'a']--;
                k++;
            }

            ans += (k - i) * (n - j);
            i = k;
        }

        j++;
    }

    return ans;
}

// Standard Sliding-window approach : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
>> Intuition

Key Observation:
If the current window s[i...j] is valid, then every substring starting at i and ending at j or any index after j is also valid, 
because extending the right end cannot remove any character already present in the window.
So, for the current starting index i, the number of valid substrings is: n - j
We add this to the answer.

Next, we try to shrink the window from the left. If the window is still valid after removing s[i], 
then the new starting index also forms valid substrings ending at j or later, so we again add n - j.

We keep shrinking and counting until the window becomes invalid. Then, we expand the window again by moving j forward.
Since each character enters and leaves the window at most once, the overall time complexity is O(n).

>> Core Idea
- Expand the window until it contains all three characters.
- Once the window is valid, every substring starting at the current left pointer and ending at j or beyond is valid.
- Add n - j to the answer for the current left pointer.
- Keep shrinking the window while it remains valid, adding n - j after each successful shrink.
- Repeat until the entire string has been processed.
*/
// it uses the similar core idea but is more concise and readable than the first approach but has same performance.
int numberOfSubstrings2(string s) {
    vector<int> freq(3, 0);

    int n = s.size();
    int i = 0;
    int ans = 0;

    for (int j = 0; j < n; j++) {
        freq[s[j] - 'a']++;

        while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
            ans += (n - j);
            freq[s[i] - 'a']--;
            i++;
        }
    }

    return ans;
}

// Similarity & differences between the two approaches
/*
>> Similarity

Both approaches are based on the same sliding window observation:

- Expand the window until it contains 'a', 'b', and 'c'.
- Once the window is valid, every extension of the right end is also valid, contributing n - j substrings.
- Shrink the window from the left while it remains valid.
- Both pointers move only forward, so both run in O(n) time and O(1) space.

>> Difference

The only difference lies in how the valid starting positions are counted.

-> Standard Approach
Shrinks the window one step at a time.
After every successful shrink, it immediately counts the contribution: 
    ans += (n - j);
If the window can be shrunk m times, it performs: 
    (n - j) + (n - j) + ... + (n - j)   // m times

-> My Approach
First, shrinks the window using a temporary pointer k to determine how many valid starting positions exist.
Let that count be:
    m = k - i
Then, instead of adding (n - j) repeatedly, it adds the total contribution in one step:
    ans += (k - i) * (n - j);

So, my solution is essentially a batched version of the standard sliding window approach.
Instead of adding (n-j) for all valid starting positions one by one, 
it calculates the total number of valid starting positions and adds their combined contribution in a single step.
*/

int main() {
    return 0;
}