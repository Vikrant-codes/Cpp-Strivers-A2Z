/*
GFG - Sort a String : Basic

Given a string consisting of lowercase letters, arrange all its letters in ascending order. 

Examples :- 
Input: S = "edcab" __ Output: "abcde"
Input: S = "xzy" __ Output: "xyz"

Constraints :-
1 ≤ |S| ≤ 10^5
S contains only lowercase alphabets.
*/

#include <bits/stdc++.h>
using namespace std;

/*
One way to solve this is using sorting techniques like Insertion Sort, Bubble Sort, Merge Sort etc.. 
by treating the string as a 1-D array of characters. 
But these will take time complexities like O(n^2) or O(n * log n) depending on the sorting technique used.
Since we want to sort string containing lowercase letters only (26), 
we can use counting sort to sort collections of limited sized elements.
*/

// Counting Sort Approach:- Time Complexity : O(n) __ Space Complexity : O(1)
string sort(string s) {
    vector<int> freq(26);
    for (char c : s) freq[c-'a']++;
    
    int k=0;
    for (int i=0; i<26; i++) {
        int f = freq[i];
        while (f) {
            s[k++] = 'a' + i;
            f--;
        }
    }
    return s;
}

int main() {
    return 0;
}