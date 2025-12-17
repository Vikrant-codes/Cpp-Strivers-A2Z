/*
GFG - Substrings with K Distinct : Medium

You are given a string s consisting of lowercase characters and an integer k, 
You have to count all possible substrings that have exactly k distinct characters.

Examples :-

Input: s = "abc", k = 2 __ Output: 2
Explanation: Possible substrings are ["ab", "bc"]

Input: s = "aba", k = 2 __ Output: 3
Explanation: Possible substrings are ["ab", "ba", "aba"]

Input: s = "aa", k = 1 __ Output: 3
Explanation: Possible substrings are ["a", "a", "aa"]

Constraints :-
1 ≤ s.size() ≤ 10^6
1 ≤ k ≤ 26
*/

// << Pre-requisite : Count Substrings with at most K distinct Characters >> 

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^3) __ Space Complexity : O(n)
/*
Naive Approach :- 
Generate all possible substrings and count the no of distinct chars in them. 
Count the substrings with distinct count equal to k.

The distinctChars function uses an unordered_set to get the count of distinct characters in the string.
It inserts all the substring chars into the set and then returns the size of the set as this is the count of distinct chars.

Complexity Analysis :-

Time Complexity : O(n^3) 
O(n^2) to get substrings and for each substring, the distinctChars function takes O(n), so O(n^2) * O(n) = O(n^3)

Space Complexity : O(n)
unordered_set<char> max size ≤ 26 (if lowercase letters), so O(1)
substr can grow up to length n → O(n)
*/
// distinctChars function return the count of distinct chars in the substring
int distinctChars(string& s) {
    unordered_set<char> st;
    for (char c : s) st.insert(c);
    return st.size();
}
int countSubstrNaive(string& s, int k) {
    if (k > s.size()) return 0;             // if no of distinct chars is greater than string size return 0
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        string substr = "";
        for (int j=i; j<n; j++) {
            substr += s[j];
            int distinct = distinctChars(substr);       // no. of distinct chars in the current substring 
            if (distinct == k) cnt++;
            // if distinct count > k, then expanding the substring will only increase the count, so break out of this loop
            if (distinct > k) break;        
        }
    }
    return cnt;
}

// Optimal Approach :-
/*
| >> countExactlyK = countAtMostK(s, k) - countAtMostK(s, k - 1)  << |

1️⃣ What the problem really asks
| Count all substrings that contain exactly K distinct characters
Important word: ALL
Not “find one”, not “longest”, but count every valid substring.

2️⃣ Why people naturally try a direct sliding window (and why it fails)
Natural thought: 
| “I’ll keep a window with exactly K distinct characters and count it.”
This seems reasonable… but here’s the flaw.

🔴 Core problem:
One window ≠ one substring
Sliding window always represents one continuous window: i ........ j
But multiple valid substrings can end at the same j.

❌ Example: Why direct counting fails
Example :- s = "aab", k = 2.
All substrings with exactly 2 distinct characters: "aab" & "ab", So output must be 2.

What a direct sliding window sees
At j = 2: window = "aab"
• distinct = 2 → valid
• You count 1
But you miss "ab", which also ends at index 2.

Why?
Because sliding window only tracks one left boundary (i) — but valid substrings may start at many different positions.

❌ Fundamental limitation
| A sliding window can tell you if the current window is valid, 
| but cannot tell how many valid substrings exist inside it 
| when the condition is “exactly K”.
This is why direct counting always undercounts.

3️⃣ Why “at most K” is different (and solvable)
✅ Key property of “at most K”
If the window [i … j] has at most K distinct characters, then:
| i...j    |
| i+1...j  |
| i+2...j  |
| ...      |
| j...j    |
✨ ALL of these substrings are valid
And how many are there? (j - i + 1)
This is why sliding window works perfectly for “at most K”. 

The solution for counting at most K distinct substrings can be understood in that problem.

✅ Why sliding window loves “at most K”
• Condition is monotonic
• Expanding window may violate it
• Shrinking window always fixes it
• Every valid window contributes multiple substrings at once
• This is not true for “exactly K”.

4️⃣ Now the magic step (but it’s not magic)
Let’s classify substrings by number of distinct characters.

Substrings grouped by distinct count

atMost(3) = substrings with
            1 distinct
          + 2 distinct
          + 3 distinct

atMost(2) = substrings with
            1 distinct
          + 2 distinct

Subtract them :- atMost(3) - atMost(2)
→ Everything cancels except: substrings with exactly 3 distinct characters

So: exactly 3 = atMost(3) - atMost(2) = (≤3) − (≤2)
Thus, to count exactly K, we do atMost(k) - atMost(k-1).

5️⃣ Why this is the ONLY practical way
| Approach                  | Works? | Why                        |
| ------------------------- | ------ | -------------------------- |
| Direct “exactly K” window | ❌      | Misses multiple substrings |
| Brute force               | ✅      | Too slow                   |
| AtMost(K)                 | ✅      | Counts in batches          |
| AtMost(K−1)               | ✅      | Counts smaller batches     |
| Subtract                  | ✅      | Leaves exactly K           |

6️⃣ One-line summary
We cannot directly count substrings with exactly K distinct characters using sliding window because 
multiple valid substrings can end at the same index. 
However, substrings with at most K distinct characters form a monotonic property, 
allowing us to count them efficiently. 
Subtracting atMost(K−1) from atMost(K) leaves exactly those substrings with K distinct characters.
*/

int countAtMostK(string& s, int k) {
    int n = s.size();

    int i = 0, j = 0, cnt = 0, distinct = 0;
    vector<int> freq(26);

    while (j < n) {
        int ind = s[j] - 'a';
        if (freq[ind] == 0) distinct++;
        freq[ind]++;

        if (distinct > k) {
            while (distinct > k) {
                int idx = s[i] - 'a';
                freq[idx]--;
                if (freq[idx] == 0) distinct--;
                i++;
            }
        }

        cnt += (j - i + 1);
        j++;
    }

    return cnt;
}
    
int countSubstr(string& s, int k) {
    if (k > s.size()) return 0;
    return countAtMostK(s, k) - countAtMostK(s, k - 1);
}

int main() {
    string s = "abcbacdeffgabcd";
    cout << "All Substrings of s are :- " << endl;
    int cnt = countSubstrNaive(s, 3);
    cout << "Count : " << cnt;

    return 0;
}