/*
Leetcode - 1313. Decompress Run-Length Encoded List : Easy

We are given a list nums of integers representing a list compressed with run-length encoding.

Consider each adjacent pair of elements [freq, val] = [nums[2*i], nums[2*i+1]] (with i >= 0).  
For each such pair, there are freq elements with value val concatenated in a sublist. 
Concatenate all the sublists from left to right to generate the decompressed list.

Return the decompressed list.

Examples :-

Input: nums = [1,2,3,4] __ Output: [2,4,4,4]
Explanation: The first pair [1,2] means we have freq = 1 and val = 2 so we generate the array [2].
The second pair [3,4] means we have freq = 3 and val = 4 so we generate [4,4,4].
At the end the concatenation [2] + [4,4,4] is [2,4,4,4].

Input: nums = [1,1,2,3] __ Output: [1,3,3]

Constraints :-
- 2 <= nums.length <= 100
- nums.length % 2 == 0
- 1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

/*
✅ Intuition
The input list nums is given in a special format called Run-Length Encoding (RLE).
Every adjacent pair represents:
- nums[2*i] → frequency
- nums[2*i + 1] → value
So if nums = [3, 5, 2, 4], it represents:
- 3 occurrences of 5
- 2 occurrences of 4
Your task is to "decompress" this encoded list into the full list: [5, 5, 5, 4, 4]

The intuition is simple:
➡️ Read each (freq, value) pair and repeat the value freq times.
➡️ Append all repeated values to an output vector.

✅ Algorithm
1. Let nums have length 2n, so there are n encoded pairs.
2. Loop through the range i = 0 to n-1:
- Extract freq = nums[2*i]
- Extract val = nums[2*i + 1]
3. Push val into the answer vector freq times:
- Use a simple loop (while (freq--)) to append the value.
4. Return the fully built vector ans.

⏱ Time Complexity
Let the final decompressed list have M total elements.
Time Complexity = O(M)
- Every element of the decompressed output is pushed exactly once.
- Even though the outer loop runs n times, the inner loop runs freq times.
- Summed over all pairs, the total number of pushes = M.
So runtime is proportional to how many numbers are output.

💾 Space Complexity
Space Complexity = O(M) : You store the entire decompressed list in ans, which has size M.
Aside from that: Only a few integer variables → O(1) auxiliary space.
*/
vector<int> decompressRLElist(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size()/2;
    for (int i=0; i<n; i++) {
        int freq = nums[2*i];
        int val = nums[2*i+1];
        while (freq--)
            ans.push_back(val);
    }
    return ans;
}

int main() {
    return 0;
}