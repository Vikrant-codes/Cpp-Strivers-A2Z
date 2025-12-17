/*
Count Substrings with At Most K Distinct Characters

You are given a string s and an integer k.
Your task is to count the total number of substrings of s such that each substring contains at most k distinct characters.
A substring is a continuous part of the string.

Examples :-

Input : s = "aab", k = 2 __ Output : 6
Explanation :- Valid substrings (at most 2 distinct characters): "a", "a", "b", "aa", "ab" & "aab".

Input : s = "abc", k = 2 __ Output : 5
Explanation :- Valid substrings (at most 2 distinct characters): "a", "b", "c", "ab" & "bc".

*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n^3) __ Space Complexity : O(n)
/*
✅ Intuition
• Initialize cnt = 0.
• Generate all possible substrings using two for loops
• For each substring, count the no. of distinct characters.
• If the distinct_count is less than/equal to k i.e. (<= k), increment cnt.
• If distinct_count exceeds k, break out of current j loop since incrementing j further will only increase the distinct_count.
• Return cnt.

♾️ Complexity Analysis 
> Time Complexity
Outer loops
• i runs from 0 to n-1
• j runs from i to n-1
Total substrings → O(n²)

Inside inner loop
For each substring, you call: distinctChars(substr)
• Length of substr = j - i + 1 → worst case O(n)
• Inserting into unordered_set → O(1) average per insert
So each inner iteration costs O(n) in worst case.

⭐ Total Time Complexity :- O(n^2) * O(n) = O(n^3)
| The early break helps in practice, but does not change worst-case complexity.

> Space Complexity :- O(n)
• unordered_set<char> → at most number of unique chars (constant for fixed alphabet) → O(1)
• substr → can grow up to length n → O(n)
*/
// distinctChars function return the count of distinct chars in the substring
int distinctChars(string& s) {
    unordered_set<char> st;
    for (char c : s) st.insert(c);
    return st.size();
}
int countSubstrNaive(string& s, int k) {
    int n = s.size();
    if (k > n) return 0;
    int cnt = 0;
    for (int i=0; i<n; i++) {
        string substr = "";
        for (int j=i; j<n; j++) {
            substr += s[j];
            int distinct = distinctChars(substr);
            if (distinct <= k) cnt++;
            else break; 
        }
    }
    return cnt;
}

// Optimal Approach (Sliding Window 2 Pointers) :- Time Complexity : O(n) __ Space Complexity : O(k) / O(1)
/*
✅ INTUITION
We want to count all substrings with at most k distinct characters.
Key observation (this is the heart of the solution):
| For a fixed ending index j, there are many substrings ending at j, not just one.
Ex- suppose s = "abcdefa", k = 3 and j is at c, then substrings with at most 3 chars ending at j are "abc", "bc" & "C".

So, we use 2 Pointers + Sliding Window Approach to tackle this problem.
2 Pointers i & j denote the start & end of the window.
We keep expanding the window (by incrementing j) until the count of distinct chars in that window <= k.
Once the count exceeds k, we shrink the window from the left by incrementing i. 

To keep track of the count of distinct characters, we use a map with <char, int> that will keep track of the 
characters and their frequencies in the current window. 
When we move j, we will increment jth character value in the map using mpp[s[j]]++.
mpp.size() will tell us the count of distinct characters in the current window.
If this count exceeds k, we shrink window by incrementing i and decrementing the value of ith character from the map.
If this mpp[s[i]] becomes 0 at some point, we erase it from the map, since it is no longer in the current window.
This shrinking continues until map size becomes less than k.

Also to get the count of substrings with at most k chars in the current window, we see
If the current window [i … j] has at most k distinct characters, then:
| i...j    |
| i+1...j  |
| i+2...j  |
| ...      |
| j...j    |
All of these are valid substrings. 
How many such valid substrings ? (j−i+1)
So instead of counting substrings one-by-one, we count in batches.

🤔 Why sliding window works here ? 
• Expanding j → adds one character
• Distinct characters can increase
• If they exceed k, we move i forward to restore validity
• Once valid again, every substring ending at j is valid
• This monotonic behavior (expand → shrink → valid) makes sliding window ideal.

➡️ ALGORITHM (step-by-step logic)
1. Initialize:
    • i = 0, j = 0
    • count = 0
    • Frequency map to track characters, unordered_map<char, int>
2. While j < n:
    • Include s[j] in the frequency map
    • If distinct characters exceed k:
        • Move i forward
        • Decrease frequencies
        • Remove characters with frequency 0
    • Now the window [i … j] has at most k distinct characters
    • Add: count += (j - i + 1)
    • Move j forward
3. Return count

♾️ COMPLEXITY ANALYSIS
⏱️ Time Complexity: O(n)
Why?
• j moves from 0 → n-1 once
• i also moves from 0 → n-1 once
• Each character is added and removed at most once
Total operations = linear.

💾 Space Complexity: O(k)
• Frequency map holds at most k distinct characters. 
• For fixed alphabet (like lowercase letters): O(1)

⭐ Final Mental Model (remember this)
| At most K distinct = count how many valid starting points exist for every ending index
That’s why (j - i + 1) works and that’s why sliding window is perfect here.
*/
int countSubstrAtMostK(string& s, int k) {
    int n = s.size();
    if (k > n) return 0;

    int i = 0, j = 0, cnt = 0;
    unordered_map<char, int> mpp;

    while (j < n) {
        mpp[s[j]]++;

        if (mpp.size() > k) {
            while (mpp.size() > k) {
                mpp[s[i]]--;
                if (mpp[s[i]] == 0) mpp.erase(s[i]);
                i++;
            }        
        }

        cnt += (j - i + 1);
        j++;
    }

    return cnt;
}

// Most Optimal Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
🔴 For large strings, using unordered_map to keep track of distinct chars kills performance !!
Even though the algorithm is O(n), unordered_map has heavy constant overhead:
• hashing on every access
• dynamic memory allocations
• erase operations are costly
• poor cache locality
For large strings (like n = 10^5), this kills performance. 

So, instead of using map, we use a freq vector of size 26 (26 lowercase alphabets) to keep track of frequencies of 
the alphabets and the count of distinct characters.

To do so, initialize a 26 sized vector having default values 0. Initially distinct count is also 0.
While expanding the window, check whether the freq of current character is 0 in the freq vector.
If it is 0, it means we are adding a new distinct character so increment distinct.
Increment the frequency of current char in the freq vector.

Thus, while expanding j :
    int idx = s[j] - 'a';
    if (freq[idx] == 0) distinct++;   // new character enters window
    freq[idx]++;

Also, while shrinking, we decrement the frequency of ith character and 
if the frequency then reaches 0, we decrement distinct count since the ith character has left the window.

When shrinking i :
    int idx = s[i] - 'a';
    freq[idx]--;
    if (freq[idx] == 0) distinct--;   // character completely removed

🔍 Why this works ?
• freq[x] == 0 → x not in window
• freq[x] > 0 → x present in window
• distinct only changes when a character enters or leaves the window

🔥 Result
• True O(1) operations
• No TLE
• Cache-friendly
• Competitive-programming standard
*/
int AtMostK(string& s, int k) {
    int n = s.size();
    if (k > n) return 0;

    int i = 0, j = 0, cnt = 0, distinct = 0;
    vector<int> freq(26);

    while (j < n) {
        int ind = s[j] - 'a';
        if (freq[ind] == 0) distinct++;             // new character enters window
        freq[ind]++;

        if (distinct > k) {
            while (distinct > k) {
                int idx = s[i] - 'a';
                freq[idx]--;
                if (freq[idx] == 0) distinct--;     // character completely removed
                i++;
            }
        }

        cnt += (j - i + 1);
        j++;
    }

    return cnt;
}

int main() {
    string s = "aabcbcdbca";
    int k = 2;
    cout << "Brute Force : " << countSubstrNaive(s, k) << endl;
    cout << "2 Pointers Sliding Window : " << countSubstrAtMostK(s, k);

    return 0;
}