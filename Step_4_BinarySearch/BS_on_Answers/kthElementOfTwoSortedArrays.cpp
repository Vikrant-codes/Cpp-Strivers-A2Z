/*
GFG - K-th element of two Arrays -- Medium --> (Similar to Median of two Sorted Arrays)

Given two sorted arrays a[] and b[] and an element k, the task is to find the element that would be at the kth position of the combined sorted array.

Examples :- 

Input: a[] = [2, 3, 6, 7, 9], b[] = [1, 4, 8, 10], k = 5 __ Output: 6
Explanation: The final combined sorted array would be [1, 2, 3, 4, 6, 7, 8, 9, 10]. The 5th element of this array is 6.

Input: a[] = [1, 4, 8, 10, 12], b[] = [5, 7, 11, 15, 17], k = 6 __ Output: 10
Explanation: Combined sorted array is [1, 4, 5, 7, 8, 10, 11, 12, 15, 17]. The 6th element of this array is 10.

Constraints :- 1 ≤ a.size(), b.size() ≤ 10^6 __ 1 ≤ k ≤ a.size() + b.size() __ 0 ≤ a[i], b[i] ≤ 10^8
*/

#include <bits/stdc++.h>
using namespace std;

// Brute Force Approach :- Time Complexity : O(n1 + n2) __ Space Complexity : O(n1 + n2)
// Approach :- Merge the two arrays into a third array and then return the kth element of that third array.
int kthElementBrute(vector<int>& a, vector<int>& b, int k) {
    int n1 = a.size();
    int n2 = b.size();
    vector<int> c;
    int i=0, j=0;
    while (i<n1 && j<n2) {
        if(a[i] <= b[j]) c.push_back(a[i++]);
        else c.push_back(b[j++]);
    }
    while (i < n1) c.push_back(a[i++]);
    while (j < n2) c.push_back(b[j++]);
    return c[k-1];
}

// Better Approach :- Time Complexity : O(k) __ Space Complexity : O(1)
// Approach :- Similar to median problem here also we simulate the merge step and return kth element of the hypothetical merged array
int kthElementBetter(vector<int>& a, vector<int>& b, int k) {
    int n1 = a.size();
    int n2 = b.size();
    int i=0, j=0, cnt=0;
    while (i<n1 && j<n2) {
        if (a[i] <= b[j]) {
            if (cnt == k-1) return a[i];
            i++;
        }
        else {
            if (cnt == k-1) return b[j];
            j++;
        }
        cnt ++;
    }
    while (i<n1 && cnt < k) {
        if (cnt == k-1) return a[i];
        i++; cnt++;
    }
    while (j<n2 && cnt < k) {
        if (cnt == k-1) return b[j];
        j++; cnt++;
    }

    return -1;
}

// Optimal Approach (Binary Search) :- Time Complexity : O(log(min(n1, n2))) __ Space Complexity : O(1)
/*
Pre-requisite :- Median of two sorted arrays
We can use the same approach as finding the median of two sorted arrays to find the k-th element.
In median problem, we partition the arrays into two equal halves by considering how many elements on the left half belong to array1. 
To solve this problem we use the same approach but here we keep 'k' elements on the left half only since we need to find 'kthElement'. 
So, we find a valid configuration such that elements on left = k and elements of right = total - k. 
Return max (l1, l2) as this is the kth element. 

Search Space :- we initialize low & high as -
> low = max(0, k - n2) :- this is because we need at least k elements in the left half and if k > n2 then we would definitely need to 
take elements from array1. Suppose k = 7 and array1.size() = 5 and array2.size() = 5, then we need to take "atleast" 2 elements from array1. 
So, low = max(0, k - n2)
> high = min(k, n1) :- If there are not enough elements in array1, then we can at max take n1 elements only so high = min(k, n1). 
*/

int kthElement(vector<int> &a, vector<int> &b, int k) {
    int n1 = a.size();
    int n2 = b.size();
    if (n1 > n2) return kthElement(b, a, k);
        
    int low = max(0, k - n2), high = min(n1, k);
    while (low <= high) {
        int mid1 = (low + high) / 2;
        int mid2 = k - mid1;
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
            
        if (mid1 < n1) r1 = a[mid1];
        if (mid2 < n2) r2 = b[mid2];
        if (mid1 - 1 >= 0) l1 = a[mid1 - 1];
        if (mid2 - 1 >= 0) l2 = b[mid2 - 1];
            
        if (l1 <= r2 && l2 <= r1) {
            return max(l1, l2);
        }
        else if (l1 > r2) high = mid1 - 1;
        else low = mid1 + 1;
    }
        
    return 0;           // dummy return
}

int main() {
    vector<int> a = {1,5};
    vector<int> b = {2,3,4,6,7,8};
    int k = 7;
    int kth = kthElementBetter(a, b, k);
    cout << kth;

    return 0;
}