/*
GFG - Remove Duplicates Sorted Array : Easy

You are given a sorted array arr[] containing positive integers. 
Your task is to remove all duplicate elements from this array such that each element appears only once. 
Return an array containing these distinct elements in the same order as they appeared.

Examples :-

Input: arr[] = [2, 2, 2, 2, 2]
Output: [2]
Explanation: After removing all the duplicates only one instance of 2 will remain i.e. [2],
so modified array will contains 2 at first position and you should return array containing [2] after modifying the array.

Input: arr[] = [1, 2, 4]
Output: [1, 2, 4]
Explation:  As the array does not contain any duplicates so you should return [1, 2, 4].

Constraints :-
• 1 ≤ arr.size() ≤ 105
• 1 ≤ arr[i] ≤ 106
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach : Time Complexity : O(n log n) + O(n) __ Space Complexity : O(n)
/*
- Store the array elements in a set to get only the distinct values.
- Traverse the set and push its elements in a result vector
- Return the result vector

>> Time Complexity Analysis :-
- Inserting a element in set takes O(log n), we insert total n elements, so O(n log n)
- Traversing the set to build the result vector takes O(k) where k is the count of distinct elements (in worst case k = n)
- So, total : O(n log n) + O(n)

>> Space Complexity Analysis :-
- Set stores distinct elements, so O(k) where k = count of distinct elements, in worst case k = n (all array elements unique)
- We don't consider the result vector as extra space
- So, total : O(n)
*/
vector<int> removeDuplicatesSet(vector<int> &arr) {
    set<int> uniqueValues;
    
    for (int x : arr)
        uniqueValues.insert(x);
        
    vector<int> ans;
    
    for (int x : uniqueValues)
        ans.push_back(x);
        
    return ans;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
- We don't actually need to use a set to store the distinct values in a result vector.
- Since the given array is sorted, we know that the elements will also come in sorted order,
  so, we can easily know whether the current element is first occurrence or has already appeared before.
- Initialize a result vector and push the 0th index array element to the result vector.
- Now, start traversing the array from index 1 to end.
- For each element arr[i], check if it is already present in result vector or not
  Since elements are being pushed in result vector in sorted order as well, 
  we can directly check if the last value of result vector (using result.back() ) is smaller than current element value.
  If yes, it means current element has not been pushed to the result vector yet. So, add it to result.
- Return the result vector

>> Dry Run Example 
arr = [1, 1, 2, 2, 2, 3, 4, 4, 5]
res = []
push 1st element (0th index) to res => res = [1]

Traverse the arr elements starting from index 1
index 1: arr[i] = 1, res.back() = 1 __ since both values are same, we don't push it to result
    res = [1]
index 2: arr[i] = 2, res.back() = 1 __ 2 != 1, it means it is first occurrence of 2, push it to result
    res = [1, 2]
index 3: arr[i] = 2, res.back() = 2 __ since both values are same, we don't push it to result
    res = [1, 2]
index 4: arr[i] = 2, res.back() = 2 __ since both values are same, we don't push it to result
    res = [1, 2]
index 5: arr[i] = 3, res.back() = 2 __ 3 != 2, push 3 to result
    res = [1, 2, 3]
index 6: arr[i] = 4, res.back() = 3 __ 4 != 3, push 4 to result
    res = [1, 2, 3, 4]
index 7: arr[i] = 4, res.back() = 4 __ since both values are same, we don't push it to result
    res = [1, 2, 3, 4]
index 8: arr[i] = 5, res.back() = 4 __ 5 != 4, push 5 to result
    res = [1, 2, 3, 4, 5]
*/
vector<int> removeDuplicates(vector<int> &arr) {
    int n = arr.size();
    
    vector<int> res;
    res.push_back(arr[0]);
    
    for (int i = 1; i < n; i++)
        if (arr[i] != res.back())
            res.push_back(arr[i]);
        
    return res;
}

int main() {
    return 0;
}