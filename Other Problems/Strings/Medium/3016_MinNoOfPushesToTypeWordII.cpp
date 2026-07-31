/*
Leetcode - 3016. Minimum Number of Pushes to Type Word II : Medium

You are given a string word containing lowercase English letters.

Telephone keypads have keys mapped with distinct collections of lowercase English letters,
which can be used to form words by pushing them. For example, the key 2 is mapped with ["a","b","c"], 
we need to push the key one time to type "a", two times to type "b", and three times to type "c" .

It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters. 
The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key. 
You need to find the minimum number of times the keys will be pushed to type the string word.

Return the minimum number of pushes needed to type word after remapping the keys.

An example mapping of letters to keys on a telephone keypad is given below. 
Note that 1, *, #, and 0 do not map to any letters.

Examples :-

Input: word = "abcde" __ Output: 5
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
Total cost is 1 + 1 + 1 + 1 + 1 = 5.
It can be shown that no other mapping can provide a lower cost.

Input: word = "xyzxyzxyzxyz" __ Output: 12
Explanation: The remapped keypad given in the image provides the minimum cost.
"x" -> one push on key 2
"y" -> one push on key 3
"z" -> one push on key 4
Total cost is 1 * 4 + 1 * 4 + 1 * 4 = 12
It can be shown that no other mapping can provide a lower cost.
Note that the key 9 is not mapped to any letter: it is not necessary to map letters to every key, but to map all the letters.

Input: word = "aabbccddeeffgghhiiiiii" __ Output: 24
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
"f" -> one push on key 7
"g" -> one push on key 8
"h" -> two pushes on key 9
"i" -> one push on key 9
Total cost is 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 2 * 2 + 6 * 1 = 24.
It can be shown that no other mapping can provide a lower cost.

Constraints :-
• 1 <= word.length <= 105
• word consists of lowercase English letters.
*/

#include<bits/stdc++.h>
using namespace std;

/*
Pre-requisite: Leetcode - 3014. Minimum Number of Pushes to Type Word I : Easy
(You can see the solution for this in "Other Problems / Strings / Easy / 3014_MinNoOfPushesToTypeWordI )
*/

/*
# Greedy Approach

The key observation is:
| Characters with higher frequency should require fewer pushes.

So, while mapping characters to keys, we must try to evenly map the characters,
but the higher frequency characters must be mapped firstly, since
these would be required more so to keep the total pushes minimum, we must map them in a way that these require less pushes.

>> Intuition

Each key on the phone can hold up to 8 characters. 
The number of pushes required to type a character depends on its position on its assigned key:
• First position → 1 push
• Second position → 2 pushes
• Third position → 3 pushes
• Fourth position → 4 pushes

Our goal is to assign characters to these positions such that the total number of pushes is minimized.

Notice that if a character appears very frequently, 
assigning it to a position requiring many pushes increases the total cost significantly. 
Conversely, infrequent characters contribute much less to the total cost, even if they require more pushes.

This suggests a greedy strategy:
• Give the most frequent characters the cheapest positions (1 push).
• Give the next most frequent characters the next cheapest positions (2 pushes).
• Continue until all characters are assigned.

Since there are 8 keys, there are exactly:
• 8 positions costing 1 push
• 8 positions costing 2 pushes
• 8 positions costing 3 pushes
• 2 positions costing 4 pushes (only 26 lowercase letters exist)

After sorting the character frequencies in descending order,
the i-th most frequent character belongs to the group requiring `(i / 8) + 1` pushes.

Multiplying this cost by its frequency and summing over all characters gives the minimum total number of pushes.

The implementation for this approach is:
• Count the frequency of each character.
• Sort the frequencies in descending order.
• Assign costs in groups of eight.
• Sum frequency × assigned_cost for every character.
*/

// Implementation 1 : Time Complexity : O(n) __ Space Complexity : O(1)
/*
• Store the frequencies in a freq vector
• Use a vector of pair of char & int to store the chars along with their respective frequencies.
• Push all the characters which have non-zero frequencies in this vector of pairs.
• Sort this vector of pairs in descending order of frequencies so we can get the most frequent characters early 
    (comparator / lambda function is used to do this required sorting on this vector of pairs).
• Iterate in this vector of pairs containing the characters along with their frequencies and 
    assign costs to them in groups of 8 
    (First 8 chars having the highest frequencies are mapped so they take only 1 push,
    the next 8 chars require 2 push, and so on..)
• Total pushes can be calculated as sum of frequency × assigned_cost for every character.

>> Time Complexity: 
• Building the freq vector: O(n)
• Building the charFreq vector (containing pair of char & int): O(26) ~ O(1)
• Sorting the charFreq: can contain at most 26 pairs (26 lowercase alphabets), so O(26 log 26) ~ O(1)
• Calculating total pushes: O(26) ~ O(1)
So, total: O(n)

>> Space Complexity: 
• Freq vector stores frequency of 26 lowercase alphabets so it essentially takes constant time O(1)
• charFreq also can contain at most 26 char & their frequencies so it is also O(1)
So, total: O(1)
*/
int minimumPushes(string word) {
    vector<int> freq(26);

    for (char& ch : word)
        freq[ch - 'a']++;

    vector<pair<char, int>> charFreq;

    for (int i = 0; i < 26; i++)
        if (freq[i] != 0)
            charFreq.push_back({'a'+i, freq[i]});

    // sort(charFreq.begin(), charFreq.end(), [](pair<char, int> p1, pair<char, int> p2) {
    //     return p1.second > p2.second;
    // });

    sort(charFreq.begin(), charFreq.end(), [](const pair<char, int>& p1, const pair<char, int>& p2) {
        return p1.second > p2.second;
    });

    int pushes = 0;
    for (int i = 0; i < charFreq.size(); i++) {
        pushes += ((i / 8) + 1) * charFreq[i].second;
    }
    
    return pushes;
}

// Implementation 2 : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Notice that we never use the character after sorting.
we just need the maximum frequencies and don't have any need for the maximum occurring characters.
So, we have no need for this vector of pairs, and we can simply sort the frequency vector itself in descending order.
*/
int minimumPushes(string word) {
    vector<int> freq(26);

    for (char& ch : word)
        freq[ch - 'a']++;
    
    // sort(freq.begin(), freq.end(), [](int x, int y) {return x > y;});

    sort(freq.begin(), freq.end(), greater<int>());
    // this greater<int> is a functor used to sort in descending order

    int pushes = 0;
    for (int i = 0; i < 26; i++) {
        pushes += ((i / 8) + 1) * freq[i];
    }
    
    return pushes;
}

int main() {
    return 0;
}