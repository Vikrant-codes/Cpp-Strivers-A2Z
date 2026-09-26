/*
Leetcode - 1807. Evaluate the Bracket Pairs of a String : Medium

You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
• For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".

You know the values of a wide range of keys. 
This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] 
indicates that key keyi has a value of valuei.

You are tasked to evaluate all of the bracket pairs. 
When you evaluate a bracket pair that contains some key keyi, you will:
• Replace keyi and the bracket pair with the key's corresponding valuei.
• If you do not know the value of the key, you will replace keyi and the bracket pair 
  with a question mark "?" (without the quotation marks).

Each key will appear at most once in your knowledge. There will not be any nested brackets in s.

Return the resulting string after evaluating all of the bracket pairs.

Examples :-

Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
Output: "bobistwoyearsold"
Explanation:
The key "name" has a value of "bob", so replace "(name)" with "bob".
The key "age" has a value of "two", so replace "(age)" with "two".

Input: s = "hi(name)", knowledge = [["a","b"]]
Output: "hi?"
Explanation: As you do not know the value of the key "name", replace "(name)" with "?".

Input: s = "(a)(a)(a)aaa", knowledge = [["a","yes"]]
Output: "yesyesyesaaa"
Explanation: The same key can appear multiple times.
The key "a" has a value of "yes", so replace all occurrences of "(a)" with "yes".
Notice that the "a"s not in a bracket pair are not evaluated.

Constraints :-
• 1 <= s.length <= 10^5
• 0 <= knowledge.length <= 10^5
• knowledge[i].length == 2
• 1 <= keyi.length, valuei.length <= 10
• s consists of lowercase English letters and round brackets '(' and ')'.
• Every open bracket '(' in s will have a corresponding close bracket ')'.
• The key in each bracket pair of s will be non-empty.
• There will not be any nested bracket pairs in s.
• keyi and valuei consist of lowercase English letters.
• Each keyi in knowledge is unique.
*/

#include <bits/stdc++.h>
using namespace std;

// Hashing Approach
/*
>> Intuition

Finding the value of each key by traversing the knowledge vector every time would be too time-consuming. 
So, we need a data structure that allows us to efficiently look up the value of a key. 
We can store all key-value pairs in a map, with each key mapped to its corresponding value.

Then, we traverse s from left to right. 
Whenever we encounter '(', we collect the characters until the corresponding ')' to form the key. 
We then look up this key in the map and append its value to the result, or '?' if the key does not exist.

i.e., traverse the string:
• If the current character is not '(', add it directly to the answer.
• If we encounter '(', extract the key until ')'.
• Look up the key in the map. If it exists, append its value; otherwise, append '?'.
• Continue scanning after the closing bracket.
*/

// My solution
/*
Let:
• N = length of s
• K = number of entries in knowledge
• L = maximum key length (≤ 10)

-> Time: O(K log K + N log K)
• Building map: O(K log K)
• Each key lookup: O(log K)
• Extracting keys takes O(N) overall since every character of s is processed at most once.
More precisely, the lookup component is O(number of bracket pairs × log K), so overall O(K log K + N log K) is a safe bound.

-> Space: O(K + N)
• O(K) for the map
• O(N) for the resulting string.
*/
string evaluate(string s, vector<vector<string>>& knowledge) {
    int n = s.size();

    map<string, string> mpp;
    
    for (auto& pair : knowledge) {
        mpp[pair[0]] = pair[1];
    }

    string ans = "";
    
    int i = 0;
    while (i < n) {
    
        if (s[i] == '(') {
            i++;
    
            string key = "";
    
            while (s[i] != ')') {
                key += s[i];
                i++;
            }
    
            if (mpp.find(key) != mpp.end()) 
                ans += mpp[key];
            else 
                ans += '?';
        }

        else ans += s[i];
        
        i++;
    }

    return ans;
}

// ChatGPT's solution (Same Approach)
/*
If we use: `unordered_map<string, string> mp;` then lookups are O(1) average.

Time: O(K + N) average
Space: O(K + N)

So the only meaningful difference between the two solutions is the lookup structure:
map           → O(log K) lookup
unordered_map → O(1) average lookup
*/
string evaluate2(string s, vector<vector<string>>& knowledge) {
    unordered_map<string, string> mp;

    // Store key -> value
    for (auto& k : knowledge) {
        mp[k[0]] = k[1];
    }

    string ans;

    for (int i = 0; i < s.length(); i++) {

        if (s[i] != '(') {
            ans += s[i];
        }
        else {
            // Find closing bracket
            int j = i + 1;

            while (s[j] != ')') {
                j++;
            }

            // Extract key
            string key = s.substr(i + 1, j - i - 1);
            
            // Replace bracket pair
            if (mp.count(key)) {
                ans += mp[key];
            }
            else {
                ans += '?';
            }

            // Skip the entire "(key)"
            i = j;
        }
    }

    return ans;
}

int main() {
    return 0;
}