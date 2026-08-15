#include <bits/stdc++.h>
using namespace std;

// Counting Sort

/*
>> Intuition
The key observation is that counting sort does not need to compare elements with each other.
If we know that the values in the array lie within a small range, then,
instead of comparing elements with each other, we ask: How many times does each value occur?

For example, consider: [4, 2, 2, 3, 1, 3]
We create a frequency array where count[x] represents how many times x occurs:
    value:  1  2  3  4
    count:  1  2  2  1
Now the sorted order is immediately determined:
    1 appears once → 1
    2 appears twice → 2, 2
    3 appears twice → 3, 3
    4 appears once → 4
So we can reconstruct the sorted array as: [1, 2, 2, 3, 3, 4]

Counting sort works well when the numbers are integers with a relatively small range.
For example: [1, 5, 2, 3, 1, 4, 2]
is a great input.
But: [1, 1000000000, 5]
is a terrible input for basic counting sort because we'd potentially need a count array of size 1,000,000,001.

>> Algorithm
1. Find the minimum and maximum values in the array.
2. Create a frequency array of size max - min + 1.
3. For every element x, increment count[x - min].
4. Iterate through the frequency array in increasing order.
5. For each index i, add/write freq[i] copies of element `i + min` into the result/original array.

Example: arr = [4, 2, 2, 8, 3, 3, 1]
min = 1, max = 8
Freq array:
    index:  0 1 2 3 4 5 6 7
    value:  1 2 3 4 5 6 7 8
    count:  1 2 2 1 0 0 0 1
Then reconstruct: 1 2 2 3 3 4 8

The subtraction by min allows us to handle arrays containing negative numbers as well.
For example: [-2, 0, -2, 1] has: min = -2
So:
    -2 → index 0
     0 → index 2
     1 → index 3

>> Complexity
Let:
    n = number of elements
    k = range of values, i.e. max - min + 1

We do:
• Find min/max → O(n)
• Create count array → O(k), (array of size k initialized with all 0s initially)
• Count elements → O(n), (traverse all elements of arr to get their frequency counts)
• Reconstruct → O(n + k) in the worst case

Therefore, 
Time: O(n + k)
Space: O(k)

This is why counting sort can be faster than O(n log n) sorting algorithms when k is small.
For example, if:
    n = 1,000,000
    k = 100
then counting sort is roughly: O(1,000,000 + 100), which is essentially O(n).

⚠️ Important caveat
Counting sort is not always O(n) in practice. More precisely, it is: O(n + k)
If k is much larger than n, it becomes inefficient.
For example: arr = [1, 1000000000]
Here: n = 2, k ≈ 1,000,000,000
Creating the count array is enormously expensive.
So, Counting sort is excellent when the value range k is reasonably small compared with the number of elements n.

Counting sort is especially useful when k is small. 
If the range of values is extremely large, the frequency array can become too expensive.
*/

void countingSort(vector<int>& arr) {
    int n = arr.size();

    // Find maximum and minimum value of arr to determine the range of elements and the size of freq array
    int maxVal = INT_MIN, minVal = INT_MAX;

    for (int& x : arr) {
        if (maxVal < x) maxVal = x;
        if (minVal > x) minVal = x;
    }

    int range = maxVal - minVal + 1;          // range of elements

    // Initialize a frequency array/vector of size 'range' having all 0s
    vector<int> freq(range, 0);

    // Count frequencies
    for (int& x : arr)
        freq[x - minVal]++;        // 'x - minVal' is done to map the element x to its corresponding index in freq array

    // Reconstruct sorted array
    int index = 0;                 // write pointer to re-write the values in original array, to put sorted elements

    for (int i = 0; i < range; i++) {
        while (freq[i] > 0) {
            arr[index] = i + minVal;   // the index i corresponds to the value 'i + minVal', re-write this value at index
            index++;                   // move the index pointer ahead for the next re-writing
            freq[i]--;                 // decrement the freq of current element as one occurrence has been written
        }
    }
}

// GFG - Counting Sort : Easy
/*
GFG - Counting Sort : Easy

Given a string s consisting of lowercase english letters, 
arrange all its letters in lexicographical order using Counting Sort.

Examples :-

Input: s = "edsab"
Output: abdes
Explanation: In lexicographical order, s will be abdes.

Input: s = "geeksforgeeks"
Output: eeeefggkkorss
Explanation:In lexicographical order, s will be eeeefggkkorss.

Constraints :- 
• 1 ≤ s.size() ≤ 10^5
*/
string countSort(string s) {
    // here the range of values is already known (since string only contains lowercase letters)
    // the range of values is [a, z], with min_val = 'a', max_val = 'z' and total 26 values.
    vector<int> freq(26);
    
    for (char& c : s) 
        freq[c - 'a']++;     // char c is mapped at index c - 'a' in the freq vector
        
    int k = 0;         // write pointer to over-write the string s, we can also create a new string and can return that
    
    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;       // the ith index belongs to the char value 'a' + i
        
        while (freq[i]) {
            s[k] = c;
            k++;
            freq[i]--;
        }
    }
    
    return s;
}

int main() {
    vector<int> arr = {2,1,5,4,3,4,2};
    countingSort(arr);

    for (int x : arr) 
        cout << x << " ";

    return 0;
}