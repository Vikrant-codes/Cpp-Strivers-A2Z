/*
Leetcode - 2785. Sort Vowels in a String : Medium

Given a 0-indexed string s, permute s to get a new string t such that:
-- All consonants remain in their original places. More formally, if there is an index i with 0 <= i < s.length
such that s[i] is a consonant, then t[i] = s[i].
-- The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for pairs of indices i, j
with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i] must not have a higher ASCII value than t[j].

Return the resulting string.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase.
Consonants comprise all letters that are not vowels.

Examples :-

Input: s = "lEetcOde" __ Output: "lEOtcede"
Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all consonants. The vowels are sorted according
to their ASCII values, and the consonants remain in the same places.

Input: s = "lYmpH" __ Output: "lYmpH"
Explanation: There are no vowels in s (all characters in s are consonants), so we return "lYmpH".

Constraints :- 1 <= s.length <= 10^5
s consists only of letters of the English alphabet in uppercase and lowercase.
*/

#include <bits/stdc++.h>
using namespace std;

// My Original Approach -- Time Complexity : O(n log n) & Space Complexity : O(2*n)
/*
Approach :-
1. Loop through the string and store all the vowels in a vector along with their index positions in another vector.
2. The function isVowel() checks if a character is a vowel or not.
3. Sort the vowels vector.
4. Loop through the sorted vowels vector and replace the characters in the original string at the stored vowel index positions.
This is done to ensure sorted vowels are placed in their correct positions in the original string.

Complexity Analaysis :-
1. Time Complexity :- O(k log k + n + k) where k is the number of vowels in the string and n is the length of the string.
Looping through the string takes O(n) and isVowel() function takes O(1) time. So first for loop takes O(n) time.
Sorting the vowels vector takes O(k log k) time.
Now we loop through the sorted vowels vector which takes O(k) time.
So overall time complexity is O(k log k + n + k).
Worst case analysis :- when all characters in the string are vowels, then k = n. then in that case time complexity becomes O(n log n).

2. Space Complexity :- O(2*k) where k is the number of vowels in the string.
We are using two extra vectors to store the vowels and their index positions.
In worst case when all characters in the string are vowels, then k = n. then in that case space complexity becomes O(2*n).
*/
bool isVowel(char c)
{
    c = toupper(c); // you can also do tolower(c)
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return true;
    return false;
}

string sortVowelsMy(string s)
{
    vector<char> vowels;
    vector<int> pos;
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        if (isVowel(s[i]))
        {
            vowels.push_back(s[i]);
            pos.push_back(i);
        }
    }

    sort(vowels.begin(), vowels.end());

    for (int i = 0; i < vowels.size(); i++)
    {
        s[pos[i]] = vowels[i];
    }
    return s;
}

// Approach 2 (Small Space Optimization) -- Time Complexity : O(n log n) & Space Complexity : O(n)
/*
Approach :-
We don't need to store the index positions of the vowels in a separate vector.
We firstly store all the vowels in a vector and sort them.
After that we loop through the original string and whenever we encounter a vowel,
we replace it with the next vowel from the sorted vowels vector.
*/
string sortVowelsMy2(string s)
{
    vector<char> vowels;
    for (char c : s)
        if (isVowel(c))
            vowels.push_back(c);

    sort(vowels.begin(), vowels.end());

    int ind = 0;
    for (char &c : s) {  // use reference to modify original string
        if (isVowel(c))
            c = vowels[ind++];
    }

    return s;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔑 Intuition
- Vowels are from a fixed small set (A,E,I,O,U,a,e,i,o,u) — only 10 possibilities.
- If we know the frequency of each vowel, we can “sort” them without using a general-purpose sort.
- Iterating through the string again, we can replace vowels in order based on this frequency table → effectively sorting them in O(n).

📝 Algorithm
1. Initialize freq[10] to store counts of each vowel (A,E,I,O,U,a,e,i,o,u).
2. Loop through the string and increment the frequency for each vowel.
3. Loop through the string again:
-- If the character is a vowel, find the next vowel in vowels[] with count > 0.
-- Replace the character and decrement that count.
4. Return the modified string.

⏱️ Complexity
Time: O(n) → two passes over the string.
Space: O(1) → freq[10] is fixed, doesn’t scale with input.

✅ Why it works ?
- Because the set of vowels is fixed and small, counting their frequency is enough to sort them.
- Avoids general-purpose sort (O(k log k)) → linear time.
- Space usage is constant → very memory-efficient.
*/
string sortVowels(string s)
{
    vector<char> vowels = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    vector<int> freq(10, 0); // stores frequency of each vowel
    for (char c : s) {
        switch (c) {
        case 'A': freq[0]++;break;
        case 'E': freq[1]++;break;
        case 'I': freq[2]++;break;
        case 'O': freq[3]++;break;
        case 'U': freq[4]++;break;
        case 'a': freq[5]++;break;
        case 'e': freq[6]++;break;
        case 'i': freq[7]++;break;
        case 'o': freq[8]++;break;
        case 'u': freq[9]++;break;
        }
    }
    int ind = 0;
    for (char &c : s) {
        if (isVowel(c)) {
            while (freq[ind] == 0) ind++;
            c = vowels[ind];
            freq[ind]--;
        }
    }

    return s;
}

// Another Optimal Approach using map : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Same approach as above but using map instead of vector to store frequency of vowels.

🔑 How this works
1. map<char,int> keeps vowels sorted by ASCII automatically.
2. it points to the current vowel to place.
3. For each vowel in the string:
-- Advance it until you find a vowel with freq > 0.
-- Replace and decrement.

⏱️ Complexity
Time: O(n) — counting vowels + iterating string. The map has only ≤10 entries, so moving it is effectively O(1).
Space: O(1) — at most 10 vowels stored.
*/

string sortVowelsMap(string s) {
    map<char,int> freq;

    // Step 1: Count frequency of each vowel
    for (char c : s) {
        if (isVowel(c)) freq[c]++;
    }

    // Step 2: Iterate through string and replace vowels
    auto it = freq.begin();  // iterator to the first vowel in sorted order
    for (char &c : s) {
        if (isVowel(c)) {
            // Move iterator until we find a vowel with count > 0
            while (it->second == 0) it++;
            c = it->first;   // replace with the current vowel
            it->second--;    // decrement count
        }
    }
    return s;
}

int main()
{

    return 0;
}