/*
Leetcode - 1331. Rank Transform of an Array : Easy

Given an array of integers arr, replace each element with its rank.
The rank represents how large the element is. The rank has the following rules:
- Rank is an integer starting from 1.
- The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
- Rank should be as small as possible.

Examples :-

Input: arr = [40,10,20,30]
Output: [4,1,2,3]
Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.

Input: arr = [100,100,100]
Output: [1,1,1]
Explanation: Same elements share the same rank.

Input: arr = [37,12,28,9,100,56,80,5,12]
Output: [5,3,4,2,8,6,7,1,3]

Constraints :-
- 0 <= arr.length <= 10^5
- -10^9 <= arr[i] <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Approach (Sorting + HashMap) : Time Complexity : O(n log n) + O(n) + O(n) __ Space Complexity : O(2*n)
/*
The optimal solution is:
- Copy the array.
- Sort the copy.
- Assign ranks only to unique elements using a hash map.
- Traverse the original array and replace each element with its rank from the map.

>> Time Complexity
- Sorting: O(n log n)
- Building map: O(n)
- Creating answer: O(n)
-> Overall: O(n log n)

>> Space Complexity
- Copy of array: O(n)
- Hash map: O(n)
-> Overall: O(n)
*/

vector<int> arrayRankTransform(vector<int>& arr) {
    int n = arr.size();
    
    vector<int> temp = arr;
    sort(temp.begin(), temp.end());
    
    unordered_map<int, int> mpp;
    
    int pos = 1;
    for (int i = 0; i < n; i++) {
        if (mpp.find(temp[i]) == mpp.end() ) {
            mpp[temp[i]] = pos++;
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[i] = mpp[arr[i]];

    return ans;
}

// ChatGPT's solution (Same Approach Same solution)
/*
vector<int> arrayRankTransform(vector<int>& arr) {
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());

    unordered_map<int, int> rank;
    int currRank = 1;
    
    for (int num : sorted) {
        if (rank.find(num) == rank.end()) {
            rank[num] = currRank++;
        }
    }
    
    vector<int> ans;
    
    for (int num : arr) {
        ans.push_back(rank[num]);
    }
    
    return ans;
}
*/

int main() {
    return 0;
}