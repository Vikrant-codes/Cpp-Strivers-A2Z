/*
GFG - Union of 2 Sorted Arrays : Medium

Given two sorted arrays a[] and b[], where each array may contain duplicate elements, 
the task is to return the elements in the union of the two arrays in sorted order. 
Union of two arrays can be defined as the set containing distinct elements that are present in either of the arrays.

Examples :-

Input: a[] = [1, 2, 3, 4, 5], b[] = [1, 2, 3, 6, 7]
Output: [1, 2, 3, 4, 5, 6, 7]
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5 6 7.

Input: a[] = [2, 2, 3, 4, 5], b[] = [1, 1, 2, 3, 4]
Output: [1, 2, 3, 4, 5]
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5.

Input: a[] = [1, 1, 1, 1, 1], b[] = [2, 2, 2, 2, 2]
Output: [1, 2]
Explanation: Distinct elements including both the arrays are: 1 2.

Constraints :-
• 1 ≤ a.size(), b.size() ≤ 10^5
• -10^9 ≤ a[i], b[i] ≤ 10^9
*/

#include <bits/stdc++.h>
using namespace std;

// Naive Approach (Using a set): Time Complexity : O((n + m) log (n + m)) __ Space Complexity : O(n + m)
/*
Insert all elements from both arrays into a set. 
Since a set stores only unique elements in sorted order, duplicates are automatically removed. 
Finally, copy the set into a vector and return it.

>> Complexity Analysis

Let n = a.size() and m = b.size().

-> Time Complexity

- First loop: Inserts n elements into the set. Each insertion takes O(log(n + m)) in the worst case.
- Second loop: Inserts m elements into the set. Each insertion also takes O(log(n + m)) in the worst case.
- Creating the answer vector: Copies k elements from the set, taking O(k), 
  where k is the number of distinct elements in the union.

Therefore, time complexity = O(n log(n + m) + m log (n + m) + k)
Since k ≤ (n + m), the overall time complexity is: O((n + m) log (n + m))

-> Space Complexity
- Set: Stores k distinct elements, requiring O(k) space.
- Answer vector: Stores the same k elements, requiring O(k) space.
Total auxiliary space, including the returned vector: O(k)
Since k ≤ (n + m), the worst-case space complexity is: O(n + m)
*/
vector<int> findUnionNaive(vector<int> &a, vector<int> &b) {
    set<int> s;
    
    for (int& x : a) 
        s.insert(x);
        
    for (int& x : b)
        s.insert(x);
        
    vector<int> ans(s.begin(), s.end());
    return ans;
}

// Optimal Approach (Two Pointers): Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
>> Intuition / Approach
The idea is to use the two-pointer technique to merge two sorted arrays 
into a single sorted array while avoiding duplicates.

Instead of inserting every element into a set, we take advantage of the fact that both arrays are already sorted.

-- How it works
1. Initialize two pointers: i points to the current element in array a, 
   and j points to the current element in array b. Both start at index 0.

2. Compare the current elements: While both pointers are within their arrays, compare a[i] and b[j].
   • If a[i] <= b[j], consider a[i] for the result and move i forward.
   • Otherwise, consider b[j] for the result and move j forward.
   • If both elements are equal, move both pointers forward because that value only needs to be included once.

3. Avoid duplicates: Before adding an element to res, check whether the result is empty or 
   its last element differs from the current element. Since the arrays are sorted, 
   duplicate values appear consecutively, so comparing with res.back() is sufficient.

4. Handle remaining elements: The main loop stops when either array is exhausted. 
   Copy the remaining elements from the other array, applying the same duplicate check.

5. Return the result: The resulting vector contains all unique elements from both arrays in sorted order.

>> Complexity analysis
Let n = a.size() and m = b.size().

-> Time complexity: O(n + m)
- Each pointer moves only forward, and each element is processed at most once.
- The main loop and the two remaining-element loops together take linear time.

-> Space Complexity
- Auxiliary space complexity: O(1), excluding the output vector, 
  because we use only two pointers and a constant number of variables.
  
- Output space complexity: O(n + m) in the worst case, since the result may contain every element from both arrays.
*/
vector<int> findUnion(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();

    // i and j track the current elements in the two sorted arrays.
    int i = 0, j = 0;

    vector<int> res;

    // Process both arrays together, just like merging two sorted arrays.
    while (i < n && j < m) {

        if (a[i] <= b[j]) {
            // Add a[i] only if it isn't already the last element in the result.
            if (res.empty() || res.back() != a[i])
                res.push_back(a[i]);

            // If both values are equal, move j ahead too
            if (a[i] == b[j]) j++;
            i++;
        }
        else {
            // b[j] is smaller, so consider it next.
            if (res.empty() || res.back() != b[j])
                res.push_back(b[j]);

            j++;
        }
    }

    // If b is exhausted, collect any remaining elements from a.
    while (i < n) {
        if (res.empty() || res.back() != a[i])
            res.push_back(a[i]);

        i++;
    }

    // If a is exhausted, collect any remaining elements from b.
    while (j < m) {
        if (res.empty() || res.back() != b[j])
            res.push_back(b[j]);

        j++;
    }

    return res;
}

int main() {
    return 0;
}