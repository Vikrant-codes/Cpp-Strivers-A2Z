// Find all subsequences with sum equals to K
/*
Given an array arr[] of length n and a number k, 
the task is to find all the subsequences of the array with sum of its elements equal to k.

Note: A subsequence is a subset that can be derived from an array by removing zero or more elements, 
without changing the order of the remaining elements.

Examples :-

Input: arr[] = [1, 2, 3], k = 3 
Output: [ [1, 2], [3] ]
Explanation: All the subsequences of the given array are:
[ [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3], [] ]
Out of which only two subsequences have sum of their elements equal to 3.

Input: arr[] = [1, 2, 3], k = 7
Output: []
Explanation: Sum of all the elements of the array is 6, which is smaller than the required sum, 
thus they are no subsequences with sum of its elements equal to 7.

Input: arr[] = [17, 18, 6, 11, 2, 4], k = 6  
Output: [ [2, 4], [6] ] 
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive Approach: Time Complexity : O(2^n) __ Space Complexity : O(n)

void findSubseq(vector<int>& arr, int k, vector<int>& subseq, int i, int sum, vector<vector<int>>& res) {
    if (i == arr.size()) {
        if (sum == k)
            res.push_back(subseq);
        return;
    }

    // Why not early exit when sum == k ? 
    /*
    While traversing and generating the subsequence, suppose the sum became equal to k while i != arr.size(),
    why can't we just add the subseq to result vector and return immediately? 

    If sum became k, then adding further elements will be in vain, but the array might have 0 as well.
    assume {a,b,c,d} is the current subseq having desired sum k, and say array is like this
        arr = {a, e, f, b, c, g, d, 0};
    Now, if we simply added {a,b,c,d} to result and returned, we will never be able to consider the subseq {a,b,c,d,0}
    if we completely traversed till the end with take/not-take condition, we will see that there are two subsequences
    with sum k, which are {a, b, c, d} and {a, b, c, d, 0}.
    Also, if arr can have negatives as well, it could be of the form {a, e, f, b, c, g, d, x, -x}
    Now, {a, b, c, d, x, -x} also forms a valid subseq, and this also would never be considered if we did early return
    */

    // pick the current element
    subseq.push_back(arr[i]);
    sum += arr[i];
    findSubseq(arr, k, subseq, i + 1, sum, res);

    // not pick the current element
    subseq.pop_back();
    sum -= arr[i];
    findSubseq(arr, k, subseq, i + 1, sum, res);
}

vector<vector<int>> subsequencesSumK(vector<int>& arr, int k) {
    vector<vector<int>> res;

    vector<int> subseq = {};

    findSubseq(arr, k, subseq, 0, 0, res);

    return res;
}

int main() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9};
    int k = 10;

    vector<vector<int>> res = subsequencesSumK(arr, k);

    for (vector<int> subseq : res) {
        cout << "[ ";
        for (int x : subseq) cout << x << " ";
        cout << "]\n";
    }

    return 0;
}