/*
Leetcode - 3517. Smallest Palindromic Rearrangement I : Medium

You are given a palindromic string s.
Return the lexicographically smallest palindromic permutation of s.

Examples :-

Input: s = "z"
Output: "z"
Explanation:
A string of only one character is already the lexicographically smallest palindrome.

Input: s = "babab"
Output: "abbba"
Explanation:
Rearranging "babab" → "abbba" gives the smallest lexicographic palindrome.

Input: s = "daccad"
Output: "acddca"
Explanation:
Rearranging "daccad" → "acddca" gives the smallest lexicographic palindrome.

Constraints :-
• 1 <= s.length <= 105
• s consists of lowercase English letters.
• s is guaranteed to be palindromic.
*/

#include <bits/stdc++.h>
using namespace std;

// Approach?
/*
| Consider a palindrome as composed of two mirror-image halves.
| Construct one half (using s), and then the other half is its reverse to obtain the lexicographically smallest permutation.

We want to re-arrange the characters of string s in such a way that 
we get the lexicographically smallest palindromic re-arrangement possible.

But while making the re-arrangement we must make sure the re-arrangement remains palindromic, 
so if we re-arrange a character at index i, its palindormic counter-part of each character must be arranged accordingly.

Ex-> assume s = "_ _ _ a _ a _ _ _", where blank spaces represent some characters,
now, suppose we are re-arranging the character 'a', to get the smallest re-arrangement, we can place it at the 0th index,
but then we would also have to place its counter-part (present at index 5), at an appropriate place so the re-arrangement 
remains palindromic. That would be "a _ _ _ _ _ _ _ a".

So, consider 's' has multiple characters occurring once or multiple times, we can not re-arrange all the characters, 
as for a character 'x' having frequency 'f', we can only arrange its 'f/2' occurrences, 
the other 'f/2' occurrences need to be arranged at the right half.

Now, right half is mirror of left half and will remain so even for answer string due to palindromic nature, 
we should not worry about re-arranging the whole string s characters, 
and instead should try to re-arrange only the left-half characters in the most optimal way 
to get the lexicographically smallest re-arrangement of left-half.
And the most optimal way to do so is to sort the left half, 
as doing so will give us the smallest lexicographically re-arrangement of left_half.

Once we get the re-arrangement of left-half, we can simply get its reverse to get the right half.
The answer string can then be build easily using the two halves.
But, we need to consider whether given string s was of odd length or even, 
since odd length string contains an extra character at middle whose palindromic counter-part doesn't exists.
So, for cases when s is of odd length, we must include this middle character in final answer as well.

-- Example 

-- s = "dacabccbacad"
This string is of even length (size = 12), left_half = "dacabc", right_half = "cbacad"
To get the answer string, we just need to re-arrange left_half to get its smallest re-arrangement.
So, sort it, left_half becomes "aabccd",
Now, right half should remain mirror of left half, since we want answer to be palindromic, so 
right half = reverse of left half = "dccbaa".
Now, answer string = left_half + right_half = "aabccddccbaa".

-- s = "xyxzxyx"
This string is of odd length (size = 7), left_half = "xyx", right_half = "xyx", middle_char = 'z'
Odd length string has one character (the middle character) whose palindromic counterpart doesn't exists.
So, this character should remain in its place, as arranging it would make it impossible to keep the answer palindromic.
So, we keep the middle character as it is and get the left_half and right_half.
Now, sort left_half, left_half becomes "xxy", right_half = mirror of left half = "yxx".
To get the answer string, we must now include the middle character and place it in middle this time also,
so, answer = left_half + middle_char + right_half = "xxy" + 'z' + "yxx" = "xxyzyxx".
*/

/*
>> Key-Observations

1. Observation 1: The string is already a palindrome
    Since it's already a palindrome:
    • the first half completely determines the second half.
    • every character in the left half has a matching character in the right half.
    • so, using the left half, we can easily determine the characters of right half (just the reverse of left half)
    • if the length is odd, the middle character never changes.


2. Observation 2: We are not rearranging arbitrarily
    Suppose
        s = "daccad"
        Left  = "dac"
        Middle = -
        Right = "cad"
    The frequencies are
        a -> 2
        c -> 2
        d -> 2
    If we want another palindrome, we don't need to think about all six characters.
    Instead,
        Take the left half.
        Rearrange it however you want.
        Mirror it.
    Example
        Left = "acd"
        Mirror: Right = "dca"
        Result: acddca
    Every character automatically gets its matching partner.
    So the problem reduces to:
    | Find the lexicographically smallest arrangement of the left half.

3. Observation 3: How do we make a string lexicographically smallest?
    If we can freely arrange characters, (like consider s = "cabd")
    the smallest arrangement is simply "abcd".
    So we should sort the left half.

>> Approach 
For a string of length n:
1. Extract the first n/2 characters.
2. Sort them (or counting sort, since only 'a'–'z' are possible).
3. Copy them into the answer.
4. If n is odd, append the middle character.
5. Append the reverse of the sorted left half.
*/

// Solution Implementations

// Using built-in sort method : Time Complexity : O(n log n) __ Space Complexity : O(n)
/*
>> Time Complexity Analysis :-

1. Build leftHalf
    for (int i = 0; i < n / 2; i++)
        leftHalf += s[i];
• Runs n/2 times.
• += is amortized O(1) for each append.
• Time: O(n)

2. Sort leftHalf
    sort(leftHalf.begin(), leftHalf.end());
• The size of leftHalf is n/2.
• Time: O( (n/2) log (n/2) ). 
• Ignoring constants, Time: O(n log n)

3. Build rightHalf
    for (int i = leftHalf.length()-1; i >= 0; i--)
        rightHalf += leftHalf[i];
• Again, n/2 iterations with amortized O(1) append.
• Time: O(n)

4. Construct the final answer
    leftHalf + rightHalf, or, leftHalf + s[n/2] + rightHalf
• The final string has length n.
• Creating it requires copying all characters once.
• Time: O(n)

| Overall Time Complexity : O(n) + O(n log n) + O(n) + O(n) = O(n log n)

>> Space Complexity Analysis
• Extra strings created:
    leftHalf → n/2
    rightHalf → n/2
    returned string → n
• The returned string isn't usually counted as auxiliary space since it's the required output.
• So the auxiliary space is: leftHalf + rightHalf = n/2 + n/2 = n
Auxiliary Space: O(n)

(The sort() implementation on std::string uses introsort, 
which requires only O(log n) stack space, so it doesn't change the overall auxiliary space.)
*/
string smallestPalindrome1(string s) {
    int n = s.length();

    string leftHalf = "";
    
    for (int i = 0; i < n / 2; i++) 
        leftHalf += s[i];
    
    sort(leftHalf.begin(), leftHalf.end());
    
    string rightHalf = "";
    
    for (int i = leftHalf.length()-1; i >= 0; i--) 
        rightHalf += leftHalf[i];
    
    return (n % 2 == 0) ? leftHalf + rightHalf : leftHalf + s[n/2] + rightHalf;
}

// Using counting Sort : Time Complexity : O(n) __ Space Complexity : O(n)
/*
Since s can only contain lowercase english alphabets (total 26 chars), 
we can use counting sort to build the sorted left half using the frequency of characters in the left half.

>> Time Complexity Analysis :-
To implement counting sort, we use a frequency array of size 26 (lowercase english alphabets)

• Building frequency array: 
    for (int i = 0; i < n / 2; i++) 
        freq[s[i] - 'a']++;

    the loop runs for n/2 iterations, so O(n/2)
• Building leftHalf using the frequency array:
    for (int i = 0; i < 26; i++) {
        while (freq[i]--) {
            leftHalf.push_back(ch);
        }
    }

    The outer loop runs 26 times (constant), 
    and the inner while loops together execute exactly n/2 times (each character is inserted once).
    Time: O(26 + n/2) = O(n/2)

All the remaining steps (building rightHalf, and constructing the final answer) are the same as in the previous approach.
So, their complexity also remains same.

This counting sort approach gets rid of the extra time taken for sorting, giving us total time: O(n)

>> Space Complexity Analysis :-
Same as the previous approach, except for the additional frequency array.
• freq → O(1) (26 integers)
• leftHalf + rightHalf → O(n)
Auxiliary Space: O(n)
*/
string smallestPalindrome2(string s) {
    int n = s.length();

    vector<int> freq(26);

    for (int i = 0; i < n / 2; i++) 
        freq[s[i] - 'a']++;

    string leftHalf = "";
    leftHalf.reserve(n / 2);

    for (int i = 0; i < 26; i++) {
        char ch = 'a' + i;
        while(freq[i]--) {
            // leftHalf = leftHalf + ch;    // ⚠️This line will do "memory limit exceed" .. Why ? (Read the comment below)
            // leftHalf += ch;
            leftHalf.push_back(ch);
        }
    }

    string rightHalf = "";
    rightHalf.reserve(n / 2);
    for (int i = leftHalf.size()-1; i >= 0; i--)
        rightHalf.push_back(leftHalf[i]);

    return (n % 2 == 0) ? leftHalf + rightHalf : leftHalf + s[n/2] + rightHalf;
}

// ⚠️ Why 'leftHalf = leftHalf + ch;' was resulting in "Memory limit exceeded"  ⚠️
/*
When we buid the string using '+' operator in this way "leftHalf = leftHalf + ch;"
This does NOT append the character in-place.
Instead, it creates a brand new temporary string on every iteration, 
copies all the existing characters into it, appends 'ch', 
and then assigns it back to leftHalf.

As the string grows larger, this results in:
- O(n²) total copying
- Many temporary string allocations
- High memory usage (which can cause MLE (Memory Limit Exceeded) on large test cases)


>> What actually happens?
Strings in C++ are immutable with respect to the + operator.
Suppose: 
    leftHalf = "abcd"; 
    char ch = 'e';
Then
    leftHalf = leftHalf + ch;
does not append directly.
It roughly becomes
    string temp = leftHalf + ch;   // creates a brand new string "abcde"
    leftHalf = temp;               // copies/moves it back

So for every character:
- Allocate a new string.
- Copy the entire old string.
- Add the new character.
- Destroy the old temporary.
This increase both work and memory usage (due to creation of lots of temporary strings)
For very large inputs, those temporary allocations can exceed the memory limit and give MLE.

>> Compare with '+='
Instead, if we use 
    leftHalf += ch;
or
    leftHalf.push_back(ch);
Now the string grows in-place.

Fix:
1. Use += or push_back() to append characters in-place.
2. Reserve the required capacity beforehand to avoid repeated reallocations. (using str.reserve())

>> Summary
| Code                                 | Complexity     | Memory Behaviour                                                  |
| ------------------------------------ | -------------- | ----------------------------------------------------------------- |
| leftHalf = leftHalf + ch;            | O(n²)          | Creates a new string every iteration (many temporary allocations) |
| leftHalf += ch;                      | O(n) amortized | Appends in-place                                                  |
| leftHalf.push_back(ch);              | O(n) amortized | Fastest and most explicit                                         |
| leftHalf.reserve(n/2); + push_back() | O(n)           | Typically a single allocation                                     |
*/

// Time Complexity : O(n) __ Space Complexity : O(n/2)
/*
>> Time Complexity
The time complexity remains the same as the previous approach.
Overall Time Complexity: O(n)

>> Space Complexity
Unlike the previous approach, we no longer create a separate rightHalf string. 
Instead, we directly append the mirrored characters from leftHalf into the final answer.
Extra memory used:
• freq → O(1) (26 integers)
• leftHalf → O(n/2)
Auxiliary Space: O(n/2) ≈ O(n)

Note: Although the asymptotic complexity is still O(n), 
this approach uses half the auxiliary string space compared to the previous solution 
(leftHalf only instead of both leftHalf and rightHalf), 
making it more space-efficient in practice.
*/
string smallestPalindrome3(string s) {
    int n = s.length();

    string ans = "";
    ans.reserve(n);
    
    vector<int> freq(26);
    for (int i = 0; i < n / 2; i++) 
        freq[s[i] - 'a']++;
    
    string leftHalf = "";
    leftHalf.reserve(n / 2);
    
    for (int i = 0; i < 26; i++) {
        char ch = 'a' + i;
        while(freq[i]--)
            leftHalf.push_back(ch);
    }

    // add the sorted left_half characters to ans .. size of left_half = n / 2
    for (int i = 0; i < n/2; i++) 
        ans.push_back(leftHalf[i]);
    
    // append the middle character to ans string for cases when s is of odd length
    if (n % 2 != 0)
        ans.push_back(s[n/2]);
    
    // append the characters of left_half in mirror (reversed) order (to get right_half characters)
    for(int i = n/2 - 1; i >= 0; i--) 
        ans.push_back(leftHalf[i]);   
    
    return ans;
}

// Optimal Implementation : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> Time Complexity
The time complexity remains the same as the previous approaches.
Overall Time Complexity: O(n)

>> Space Complexity
Unlike the previous approach, we no longer create a separate leftHalf string. 
We directly build the first half of the palindrome in the output string ans and 
later reuse those characters (in reverse order) to construct the second half.

Extra memory used:
• freq → O(1) (26 integers)
The string ans is the required output, so it is not counted as auxiliary space.

Auxiliary Space: O(1)

Note: This is the most space-efficient approach. 
By building the left half directly into the answer and then mirroring it from the same string, 
it eliminates the need for both leftHalf and rightHalf, reducing the auxiliary space from O(n) to O(1) 
(excluding the output string).
*/
string smallestPalindrome(string s) {
    int n = s.length();

    string ans = "";
    ans.reserve(n);
    
    vector<int> freq(26);
    for (int i = 0; i < n / 2; i++) 
        freq[s[i] - 'a']++;
    
    for (int i = 0; i < 26; i++) {
        char ch = 'a' + i;
        while(freq[i]--)
            ans.push_back(ch);
    }
    
    // append the middle character to ans string for cases when s is of odd length
    if (n % 2 != 0)
        ans.push_back(s[n/2]);
    
    // we need mirror chars, so extract chars from ans for index range [n/2-1, 0] & add them to ans
    for(int i = n/2 - 1; i >= 0; i--) 
        ans.push_back(ans[i]);   
    
    return ans;
}

int main() {
    return 0;
}