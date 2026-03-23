/*
Leetcode - 832. Flipping an Image : Easy

Given an n x n binary matrix image, flip the image horizontally, then invert it, and return the resulting image.
To flip an image horizontally means that each row of the image is reversed.
For example, flipping [1,1,0] horizontally results in [0,1,1].
To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0.
For example, inverting [0,1,1] results in [1,0,0].

Examples :-

Input: image = [[1,1,0],[1,0,1],[0,0,0]]
Output: [[1,0,0],[0,1,0],[1,1,1]]
Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]

Input: image = [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]

Constraints :-
- n == image.length
- n == image[i].length
- 1 <= n <= 20
- images[i][j] is either 0 or 1.
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n^2) + O(n^2) __ Space Complexity : O(1)
/*
We have to do 2 things - 
    1) Flip the image horizontally (reverse each row)
    2) invert the bits.
So, we firstly traverse the rows are reverse each row - O(n^2)
Then, we again traverse the matrix to invert the bits. - O(n^2)
*/
vector<vector<int>> flipAndInvertImageNaive(vector<vector<int>>& image) {
    int n = image.size();

    // flip horizontally, i.e., reverse each row
    for (int i=0; i<n; i++) {
        int j=0, k=n-1;         // use two pointers to reverse each row
        while (j<k) {
            swap(image[i][j], image[i][k]);
            j++; k--;
        }
    }

    // invert bits
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            image[i][j] = (image[i][j]==0) ? 1: 0;
        }
    }

    return image;
}

// Optimal Approach (Single Pass solution) : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
We can do everything (flip rows horizontally and invert bits) in-place in one pass.

Approach -
- Reverse each row
- Invert the bits
- Do both together to do it in one pass (while reversing the rows, invert the bits).
*/
// helper function - to invert the bit
void flipBit(int& bit) {
    bit = (bit == 0) ? 1 : 0;       // we could also use bit = bit ^ 1 to invert the bits.
}

// helper function - reverse the row (while also inverting each bit)
void reverseRow(vector<int>& row, int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        flipBit(row[i]);
        flipBit(row[j]);

        swap(row[i], row[j]);
        i++; j--;
    }

    // if there are 'odd' elements in the row, then both i & j point at same element when loop ends
    // this element does not need to be swapped as it doesn't have any pair element to swap with, but we need to invert it
    // so if i & j point to same location when loop ends -> row has odd elements -> invert the ith/jth bit
    if (i == j) flipBit(row[i]);
}

vector<vector<int>> flipAndInvertImage1(vector<vector<int>>& image) {
    int n = image.size();

    // flip & invert = reverse each row and also invert each bit while reversing
    for (auto& row : image) reverseRow(row, n);
    
    return image;
}

// This code is equivalent to the below one (this one is not using any function to do the task)
vector<vector<int>> flipAndInvertImage2(vector<vector<int>>& image) {
    int n = image.size();

    // flip & invert = reverse each row and also invert each bit while reversing
    for (auto& row : image) {
        int i = 0, j = n - 1;
        while (i < j) {
            row[i] = (row[i] == 0) ? 1 : 0;         // flip ith bit
            row[j] = (row[j] == 0) ? 1 : 0;         // flip jth bit
            
            swap(row[i], row[j]);                   // swap values to reverse row
            
            i++; j--;
        }
        // if i & j point to same element after loop ends, invert this element 
        if (i == j) row[i] = (row[i] == 0) ? 1 : 0;  
    }

    return image;
}

// Best Approach : Time Complexity : O(n^2) __ Space Complexity : O(1)
/*
Approach Intuition:-
🔥 Key Observation (the whole trick)
Instead of: swap + invert both
We analyze what actually happens depending on values.

🧪 Case Analysis

Let’s take a pair: left = row[l], right = row[r]

✅ Case 1: Different bits (0,1) or (1,0)
Example: [1 .... 0]
Step 1: Reverse (swap) -> [0 .... 1]
Step 2: Invert -> [1 .... 0]
👉 We got same as original
💡 Conclusion: Swap + invert cancels out (if the left & right bits are different) → NO CHANGE ➡️ So we do nothing

✅ Case 2: Same bits (0,0) or (1,1)
Example: [0 .... 0]
Step 1: Reverse (swap) -> [0 .... 0]   // no change
Step 2: Invert -> [1 .... 1]
👉 Final result = both bits flipped
💡 Conclusion: Only inversion matters ➡️ So we just flip both bits

🔁 Why no swapping is needed?
Because:
When bits are different, final result = original → no work needed
When bits are same, swapping does nothing → only flip matters
👉 So swap becomes useless in both cases

🧪 Full Example Walkthrough
Input: [1 0 1 0 0]

Step-by-step:
- (l=0, r=4) : 1 != 0 → do nothing
- (l=1, r=3) : 0 == 0 → flip both → becomes 1,1
Row becomes: [1 1 1 1 0]
- Middle (l=r=2) : 1 → flip → 0
Final: [1 1 0 1 0]

⚡ Why this is optimal
- No swap() calls
- Single traversal
- In-place
- Less operations → faster in practice
*/
vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
    int n = image.size();

    for (auto& row : image) {
        int l = 0, r = n-1;
    
        while (l < r) {
            if (row[l] == row[r]) {
                row[l] ^= 1;         // flip bit : row[l] = row[l] ^ 1
                row[r] ^= 1;         // flip bit : row[r] = row[r] ^ 1
            }
            l++; r--;
        }
    
        if (l == r) row[l] ^= 1;     // if l == r, we still need to invert this bit
    }
    
    return image;
}

int main() {
    return 0;
}