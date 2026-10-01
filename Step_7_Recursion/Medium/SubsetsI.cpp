/*
GFG - Subset Sums : Medium

Given an array arr of integers, return the sums of all subsets in the list.
Return the sums in any order.

Examples :-

Input: arr[] = [2, 3] __ Output: [0, 2, 3, 5]
Explanation: When no elements are taken then Sum = 0. When only 2 is taken then Sum = 2. 
When only 3 is taken then Sum = 3. When elements 2 and 3 are taken then Sum = 2+3 = 5.

Input: arr[] = [1, 2, 1] __ Output: [0, 1, 1, 2, 2, 3, 3, 4]
Explanation: The possible subset sums are 0 (no elements), 1 (either of the 1's), 2 (the element 2), and their combinations.

Input: arr[] = [5, 6, 7] __ Output: [0, 5, 6, 7, 11, 12, 13, 18]
Explanation: The possible subset sums are 0 (no elements), 5, 6, 7, and their combinations.

Constraints:
• 1 ≤ arr.size() ≤ 15
• 0 ≤ arr[i] ≤ 10^4
*/

#include<bits/stdc++.h>
using namespace std;

// Recursive Approach: Time Complexity : O(2^n) __ Space Complexity : O(2^n)
/*
We can use the standard pick/not-pick approach to get the sum of all possible subsets.
Suppose the size of the array is `n`.
For each element we have two choices, either to pick it or not-pick it.

Thus, for n elements, these choices becomes 2 * 2 * 2 * 2 * .... upto n times, giving us 2^n.
This approach thus takes O(2^n) time to generate all the possible subsets.

The subset sums are stored in some output vector and since there are 2^n subsets, there are also 2^n subset sums.
Thus the output vector takes O(2^n) auxiliary space.
The recursive stack takes O(n) space though, since the recursive depth is `n` (we can only traverse the whole array)

Thus, the space complexity is O(2^n) if we consider the output vector, else it is O(n)
*/
void findSubsets(vector<int>& arr, int ind, int sum, vector<int>& res) {
    if (ind == arr.size()) {
        res.push_back(sum);
        return;
    }
    
    // pick the current element
    findSubsets(arr, ind + 1, sum + arr[ind], res);
    
    // not-pick the current element
    findSubsets(arr, ind + 1, sum, res);
}

vector<int> subsetSums(vector<int>& arr) {
    vector<int> res;
    
    findSubsets(arr, 0, 0, res);
    
    return res;
}

int main() {
    return 0;
}