#include <bits/stdc++.h>
using namespace std;

// GFG Variant
/*
GFG - Intersection of Two Sorted Arrays : Easy

Given two sorted arrays a[] and b[], where each array may contain duplicate elements, 
return the elements in the intersection of the two arrays in sorted order.

Note: Intersection of two arrays can be defined as the set containing distinct common elements 
that are present in both of the arrays.

Examples :-

Input: a[] = [1, 1, 2, 2, 2, 4], b[] = [2, 2, 4, 4]
Output: [2, 4]
Explanation: Distinct common elements in both the arrays are: 2 and 4.

Input: a[] = [1, 2], b[] = [3, 4]
Output: []
Explanation: No common elements.

Input: a[] = [1, 2, 3], b[] = [1, 2, 3]
Output: [1, 2, 3]
Explanation: All elements are common.

Constraints :-
• 1 ≤ a.size(), b.size() ≤ 10^5
• -10^9 ≤ a[i], b[i] ≤ 10^9
*/

// Naive Approach (Using Set): Time Complexity : O(n log n + m log m) __ Space Complexity : O(n + m)
/*
In this GFG variant, we need to store only distinct values in the result vector. 
Even if a number occurs multiple times in both arrays, we include it only once in the intersection.

- We can use two sets (ordered sets) to store the elements of both arrays, 
  which automatically removes duplicates and keeps the elements sorted.
- Iterate through one set and check whether each element exists in the other set as well. 
  If it does, the element is common to both arrays, so add it to the answer.
- Since a set stores only distinct elements in sorted order, 
  the result contains each common element exactly once, even if it occurs multiple times in both arrays.

>> Complexity Analysis
-> Time Complexity: O(n log n + m log m), where n and m are the sizes of arrays a and b. 
    This accounts for constructing both sets and checking membership.
-> Auxiliary Space Complexity: O(n + m), for storing the elements in both sets.
*/
vector<int> intersectionNaive(vector<int>& a, vector<int>& b) {
    set<int> s1(a.begin(), a.end());
    set<int> s2(b.begin(), b.end());
    
    vector<int> ans;
    
    for (const int& x : s1) {
        if (s2.count(x)) {
            ans.push_back(x);
        }
    }
    
    return ans;
}

// Optimal Approach (Using Two Pointers): Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
>> Intuition

Since both arrays are sorted, we can use the two-pointer approach to find 
common elements efficiently without using extra sets.

Initialize two pointers, i and j, at the beginning of arrays a and b. Compare a[i] and b[j]:
- If a[i] == b[j], we have found a common element. 
    Add it to the answer only if the answer is empty or its last element is different from the current element. 
    This ensures that each distinct common element is added only once, 
    even if it occurs multiple times in both arrays. 
    Then increment both pointers.
- If a[i] > b[j], increment j because b[j] is smaller and cannot match the current or any larger element in a.
- Otherwise, increment i because a[i] is smaller and cannot match the current or any larger element in b.

Continue until either pointer reaches the end of its array.
Once any of the two array is exhausted (the pointer reaches end), we no longer need to check for common elements.
We can simply return the answer vector.
Since the arrays are sorted, the answer will also be in sorted order.  

>> Complexity Analysis

-> Time Complexity: O(n + m), 
    where n and m are the sizes of arrays a and b, 
    because each pointer moves forward at most through its respective array once.

-> Auxiliary Space Complexity: O(1), excluding the output vector, 
    since we use only two pointers and no additional data structures.
*/
vector<int> intersection(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    
    int i = 0, j = 0;
    vector<int> ans;
    
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            if (ans.empty() || ans.back() != a[i]) 
                ans.push_back(a[i]);
            
            i++; j++;
        }
        
        else if (a[i] > b[j]) j++;
        else i++;
    }
    
    return ans;
}

// TUF Variant
/*
TUF - 706. Intersection of two sorted arrays

Given two sorted arrays, nums1 and nums2, return an array containing the intersection of these two arrays. 
Each element in the result must appear as many times as it appears in both arrays; 
that is, if an element appears x times in nums1 and y times in nums2, it should appear min(x, y) times in the result.

The intersection of two arrays is an array where all values are present in both arrays. 
Since both input arrays are sorted, the resulting intersection array should also be in sorted order.

Examples :-

Input: nums1 = [1, 2, 2, 3, 5], nums2 = [1, 2, 7]
Output: [1, 2]
Explanation:
The elements 1, 2 are the only elements present in both nums1 and nums2

Input: nums1 = [1, 2, 2, 3, 3, 3], nums2 = [2, 3, 3, 4, 5, 7]
Output: [2, 3, 3]
Explanation:
The element 2 appears in both arrays only one time.
The element 3 appears in both arrays two times so we add element 3 equal to its number of occurrences.

Constraints :-
• 1 <= nums1.length, nums2.length <= 1000
• -10^4 <= nums1[i], nums2[i] <= 10^4
• Both nums1 and nums2 are sorted in non-decreasing order.
*/

// Naive Approach (Hashing): Time Complexity : O(n log n + m log m) __ Space Complexity : O(n + m)
/*
>> Intuition

Unlike the previous variant, here we need to include all common occurrences of an element in the result. 
If an element appears x times in nums1 and y times in nums2, it must appear min(x,y) times in the result.

Since we need to preserve the frequency of each element, we cannot use sets, as they eliminate duplicates. 
Instead, we use two maps to store the frequency of each element in both arrays.

Iterate through one of the map (freq1) and check whether each element exists in the other map as well (freq2). 
If it does, the element is common to both arrays.
We need to check how many common occurrences of this common element exists in both of the arrays, 
which can be calculated as min(cnt1, cnt2), where cnt1 & cnt2 are no. of occurrences in nums1 & nums2 respectively.
Add the common element to the result vector that many times (i.e., min(cnt1, cnt2) times) using a loop.

Since map stores keys in sorted order, iterating through freq1 ensures that the result is also in sorted order.

>> Complexity Analysis

Let n = size of nums1, m = size of nums2

-> Time Complexity: O(n log n + m log m)
Building the maps and checking frequencies takes O(n log n + m log m) time overall, 
including inserting the common occurrences into the result.

-> Auxiliary Space Complexity: O(n + m), for storing the frequency maps.
*/
vector<int> intersectionArrayHashing(vector<int>& nums1, vector<int>& nums2) {
    map<int, int> freq1;
    map<int, int> freq2;

    for (int& x : nums1)
        freq1[x]++;
    
    for (int& x : nums2) 
        freq2[x]++;

    vector<int> res;

    for (auto& [num, cnt] : freq1) {
        // if num is present in freq2 map as well (means, it is common in both arrays)
        if (freq2.find(num) != freq2.end()) {
            int cnt2 = freq2[num];

            int occ = min(cnt, cnt2);
            
            while (occ--) {
                res.push_back(num);
            }
        }
    }

    return res;
}

// Optimal Approach (Using Two Pointers): Time Complexity : O(n + m) __ Space Complexity : O(1)
/*
>> Intuition

Since both arrays are sorted, we can use the two-pointer approach with pointers i and j 
initialized at the beginning of nums1 and nums2, respectively.

Compare nums1[i] and nums2[j]:
- If they are equal, we have found a common occurrence. 
    Add the element to res and increment both pointers. 
    This naturally ensures that an element is added only as many times as it appears in both arrays.
- If nums1[i] > nums2[j], increment j because nums2[j] is smaller and cannot match the current or any larger element in nums1.
- Otherwise, increment i because nums1[i] is smaller and cannot match the current or any larger element in nums2.

No duplicate-checking condition is needed (unlike the previous variant), 
because we are required to include all common occurrences, not just distinct elements.

>> Complexity Analysis

-> Time Complexity: O(n + m), where n and m are the sizes of nums1 and nums2, 
since each pointer traverses its array at most once.

-> Auxiliary Space Complexity: O(1), excluding the output vector, 
as we use only two pointers and no additional data structures.
*/
vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size(), m = nums2.size();

    int i = 0, j = 0;
    vector<int> res;
    
    while (i < n && j < m) {
        if (nums1[i] == nums2[j]) {
            res.push_back(nums1[i]);
            i++; j++;
        }
        else if (nums1[i] > nums2[j]) j++;
        else i++;
    }
    
    return res;
}

int main() {
    return 0;
}