#include <bits/stdc++.h>
using namespace std;

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
>> What does the problem ask?
Given a string, find how many times we can form: "balloon" from its characters.
For example: text = "lblanooblnoalo"
We can form "balloon" twice.

Step 1: Think about what limits the answer
To make one "balloon" we need:
    b -> 1
    a -> 1
    l -> 2
    o -> 2
    n -> 1
So if the string contains:
    b = 5
    a = 3
    l = 8
    o = 4
    n = 2
How many balloons can we make?
Let's check each character separately:
- b allows 5 balloons
- a allows 3 balloons
- l allows 8/2 = 4 balloons (since 2 l's are required for a single balloon)
- o allows 4/2 = 2 balloons (since 2 o's are required for a single balloon)
- n allows 2 balloons
So: 5, 3, 4, 2, 2
Even though we have enough bs for 5 balloons, we only have enough os for 2 balloons.
Therefore: answer = 2

>> One-line intuition
Count how many times each required character can contribute to a complete "balloon" and 
return the smallest of those counts, because the rarest required character becomes the bottleneck.

1. Count frequencies of a, b, l, o, n. (characters of "balloon")
2. Divide counts of l and o by 2 because "balloon" needs two of each.
3. Take the minimum frequency.
*/
int maxNumberOfBalloons(string text) {
    vector<int> freq(5);        // store frequency of characters (a, b, l, o, n) (characters of 'balloon')

    for (char ch : text) {
        if (ch == 'a') freq[0]++;
        else if (ch == 'b') freq[1]++;
        else if (ch == 'l') freq[2]++;
        else if (ch == 'o') freq[3]++;
        else if (ch == 'n') freq[4]++;
    }
    freq[2] /= 2;           // two occurrences of 'l' are required for one "balloon" 
    freq[3] /= 2;           // two occurrences of 'o' are required for one "balloon" 

    for (int x : freq)
        cout << x << " ";
    cout << endl;
    
    // find the minimum frequency now
    int ans = freq[0];
    for (int x : freq) 
        if (x < ans)
            ans = x;
    
    return ans;

    // or, we could simply use the pre-defined min_element method to return the min element value
    // return *min_element(freq.begin(), freq.end());
}


int main() {
    string text = "balon";
    cout << maxNumberOfBalloons(text);

    return 0;
}