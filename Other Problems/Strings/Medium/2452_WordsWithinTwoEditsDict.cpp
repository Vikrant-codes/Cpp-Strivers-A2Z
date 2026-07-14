/*
Leetcode - 2452. Words Within Two Edits of Dictionary : Medium

You are given two string arrays, queries and dictionary. 
All words in each array comprise of lowercase English letters and have the same length.

In one edit you can take a word from queries, and change any letter in it to any other letter. 
Find all words from queries that, after a maximum of two edits, equal some word from dictionary.

Return a list of all words from queries, that match with some word from dictionary after a maximum of two edits. 
Return the words in the same order they appear in queries. 

Examples :-

Input: queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
Output: ["word","note","wood"]
Explanation:
- Changing the 'r' in "word" to 'o' allows it to equal the dictionary word "wood".
- Changing the 'n' to 'j' and the 't' to 'k' in "note" changes it to "joke".
- It would take more than 2 edits for "ants" to equal a dictionary word.
- "wood" can remain unchanged (0 edits) and match the corresponding dictionary word.
Thus, we return ["word","note","wood"].

Input: queries = ["yes"], dictionary = ["not"]
Output: []
Explanation:
Applying any two edits to "yes" cannot make it equal to "not". Thus, we return an empty array.

Constraints :-
• 1 <= queries.length, dictionary.length <= 100
• n == queries[i].length == dictionary[j].length
• 1 <= n <= 100
• All queries[i] and dictionary[j] are composed of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(Q * D * N) __ Space Complexity : O(1)
/*
>> Approach :
• For each query word, compare it with each dictionary word.
• Count the number of differing characters.
• If the difference count is ≤ 2, include the query in the answer and stop checking further dictionary words.

The helper method areSimilar checks two words one from query and other from dictionary, 
and returns true if the count of differing characters for the two words is ≤ 2. Else return false.

>> Time Complexity 
Let:
- Q = queries.length
- D = dictionary.length
- N = word length
In the worst case, every query is compared with every dictionary word, and each comparison scans all N characters.
Time = O(Q × D × N)
With the given constraints (Q, D, N ≤ 100), the worst-case operations are about 100 × 100 × 100 = 10^6 character comparisons.

>> Space Complexity 
Apart from the output list, the algorithm only uses a few counters/variables while comparing words.
Auxiliary space = O(1)
If counting the returned result list, the total space is:
O(Q) in the worst case
because all query words may be included in the answer.
*/
bool areSimilar(const string& word1, const string& word2) {
    int n = word1.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (word1[i] != word2[i])
            cnt++;
        if (cnt > 2) return false;
    }
    return true;
}

vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
    vector<string> ans;

    for (string& word1 : queries) {
        for (string& word2 : dictionary) {
            if (areSimilar(word1, word2)) {
                ans.push_back(word1);
                break;
            }
        }
    }

    return ans;
}

int main() {
    return 0;
}