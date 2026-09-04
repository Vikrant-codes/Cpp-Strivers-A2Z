/*
GFG - Bird and Max Fruit Gathering : Easy

Given an array arr[] representing the fruit values of trees arranged in a circle and an integer m, 
find the maximum total fruits the bird can collect by visiting at most m trees.

Bird can start from any tree and move to a neighboring tree.
The first and last trees are also considered neighbors.
The bird collects the fruit value of every tree it visits.

Examples :-

Input: arr[] = [2, 1, 3, 5, 0, 1, 4], m = 3
Output: 9
Explanation: The bird can start from the second tree and visit the second, third, and fourth trees.
The total fruit value collected is 1 + 3 + 5 = 9.

Input: arr[] = [1, 6, 2, 5, 3, 4], m = 2
Output: 8
Explanation: The bird can start from the second tree and visit the second and third trees, collecting 6 + 2 = 8. 
It can also start from the fourth tree and visit the fourth and fifth trees, collecting 5 + 3 = 8. 
The maximum total fruit value is 8.

Input: arr[] = [7, 2, 1, 3, 4], m = 2
Output: 11
Explanation: The bird can start from the fifth tree and visit the fifth and first trees, collecting 4 + 7 = 11. 
These trees are neighbors because the trees are arranged in a circle. The maximum total fruit value is 11.

Constraints :-
• 1 ≤ arr.size(), m ≤ 10^6
• 0 ≤ arr[i] ≤ 10^6
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n * m) __ Space Complexity : O(1)
/*
The idea is to start from every tree and calculate the total fruits collected from the next m trees. 
Since the trees are arranged in a circle, we use modulo % n to handle the circular movement.
*/
int maxFruitsNaive(vector<int>& arr, int m) {
    int n = arr.size();
    
    int res = 0;
    
    // Try every tree as the starting point.
    for (int i = 0; i < n; i++) {
        int sum = 0;
        
        // Collect fruits from the next m trees.
        for (int j = 0; j < m; j++) {
            sum += arr[(i + j) % n];
        }
        
        res = max(res, sum);
    }
    
    return res;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
The idea is to use a sliding window of size m and move it around the circular array. 
Instead of calculating every window sum again, remove the leftmost tree and add the new tree entering the window.
*/
int maxFruits(vector<int>& arr, int m) {
    int n = arr.size();
    
    int ans = 0;
    
    // 1st subarray of size m (from index 0 to m-1)
    for (int i = 0; i < m; i++)
        ans += arr[i];
        
        
    if (m == n) 
        return ans;
    
    int currSum = ans;
    int i = m;
    int j = 0;
    
    while (j < n) {
        currSum += arr[i] - arr[j];
        
        ans = max(ans, currSum);
            
        i = (i + 1) % n;
        j++;
    }
    
    return ans;
}

int main() {
    return 0;
}