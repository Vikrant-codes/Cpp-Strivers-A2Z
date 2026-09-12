/*
GFG - Max Product Subsequence of Size K : Medium

Given an array arr[] of integers and an integer k, 
find a subsequence of size k whose product is maximum among all possible subsequences of size k. 
Return the maximum product that can be obtained.

Examples :-

Input: arr[] = [1, 2, 0, 3], k = 2
Output: 6
Explanation: Subsequence containing elements {2, 3} gives maximum product: 2*3 = 6

Input: arr[] = [1, 2, -1, -3, -6, 4], k = 4
Output: 144
Explanation: Subsequence containing {2, -3, -6, 4} gives maximum product: 2*(-3)*(-6)*4 = 144

Constraints :-
• arr.size() ≤ 30
• -10 ≤ arr[i] ≤ 10
• 1 ≤ k ≤ arr.size()
*/

#include<bits/stdc++.h>
using namespace std;

// Naive Approach (Recursive Backtracking) : Time Complexity : O(2^n) __ Space Complexity : O(n)
/*
Use Recursion/Backtracking to effectively generate all possible subsequences of size `k` and get their product.
Return the maximum product of generated subsequences.
To generate all subsequences, we use the basic idea of two choices for every element, 
either include in the current subsequence or do not include.

Since we only care about the product and not the elements of the subsequence, 
we can maintain a product variable and return that, instead of maintaining a vector for generated subsequence.

>> Complexity Analysis
Let n = arr.size()

For each element, we have two choices -> pick / not-pick.
So, total time complexity : O(2^n)

-> Space Complexity
Recursive Stack Space : O(n), since recursion depth is n.
*/

// recursive method to pick `k` elements
// cnt represents count of remaining elements to be picked
int recurse(vector<int>& arr, int ind, int pro, int cnt) {
    if (cnt == 0) {
        return pro;
    }
    
    // if the product became 0 (a 0 has been picked), no need to further pick elements
    if (pro == 0) 
        return 0;
        
    // if not enough elements left to pick
    if ((arr.size() - ind) < cnt) 
        return INT_MIN;
    
    // pick the current element
    int include = recurse(arr, ind + 1, pro * arr[ind], cnt-1);
    
    // not pick the current element
    int exclude = recurse(arr, ind + 1, pro, cnt);
    
    return max(include, exclude);
}

int maxProduct1(vector<int> &arr, int k) {
    return recurse(arr, 0, 1, k);
}


// Better Approach (My solution) :- Time Complexity : O(n log n) + O(n * k) __ Space Complexity : O(1)
/*
>> Intuition

We want to get the maximum product of `k` sized subsequence.
Unlike subarrays, subsequences don't have to keep contiguous segment of elements and 
elements from anywhere in the array can be a part of the subsequence.

We want to maximize product, so we can think of selecting the max. elements from the array 
considering that their product would be high.

So, we can sort the array since doing so we can obtain the elements in ascending order.
Since, subsequence don't care about elements being contiguous we can easily do the sorting,
although subsequences generally consider the relative order of elements, but since we are concerned only about the product,
we don't have to maintain the order of elements, so sorting them is not problematic as we don't want order to be preserved.

When we sort the array, the problem that initially was maximum product of k-sized subsequences, 
becomes maximum product of k-sized subarrays (considering array to be circular, circular consideration due to -ve elements).

Now, once we sort the array, we can think that the last k elements would be the largest elements 
and their product will be maximum, but it is not always the case.
The array can have negatives as well and two negatives when multiplied become positives and 
this could exceed the product of k largest elements.

Ex - arr = [1, 2, -1, -3, -6, 4], k = 4
Sort the array : arr = [-6, -3, -1, 1, 2, 4]
If we select the maximum 4 elements {-1, 1, 2, 4}, their product will be -8.
But for this array, the maximum product will be given by the subsequence set {2, 4, -6, -3}, which is 144.
So, we also need to consider negative elements and 
can't directly return the product of last k elements after sorting (k max. elements).

We can try to implement a fixed-sized sliding window of size `k`, and maintain the maximum window product and return that.
During this sliding window traversal, we would have to consider the array as circular as doing so will allow us to 
consider subsequences of negatives and positives.
i.e., normal sliding window would stop at [-1, 1, 2, 4], 
but considering array as circular would allow us to consider windows like: [1, 2, 4, -6], [2, 4, -6, -3], [4, -6, -3, -1].

So, we can maintain a window product `pro`, and assume arr[i] leaves the window and arr[j] enters the window,
then window product would become pro * arr[j] / arr[i].

This sliding window would've worked, but, their is still one issue that makes this sliding window idea not possible.
The problem is that array can have `0` as well, and this `0` leaving and entering window would mess up 
our window product calculations, as when 0 leaves the window, 
we would have to explicitly iterate the window to get the new product.
So, due to zero, if we try to implement this k-sized sliding window considering circular array, 
we would have to explicitly find the product of current window and maintain maximum product seen so far.

Since, we have to iterate the whole window again and again to get the product, 
then why even go through the trouble to slide the windows.
We can simply sort the array, consider array to be circular and for each index, 
we can consider that index to be the starting point of a k-sized subarray.
We can thus compute the product of k elements starting from current index and maintain the maximum product.

>> Complexity Analysis :- 

-> Time Complexity : 
- Sorting : O(n log n)
- Traversal and product computation : O(n * k)
    For each index, we compute the product of `k` elements starting from that index (considering circular array)
    This gives us O(n * k)

Thus, total time : O(n log n) + O(n * k)

-> Space Complexity : O(1)
*/

int getProduct(vector<int>& arr, int start, int k) {
    int n = arr.size();
    int pro = 1;
    
    int i = start;
    
    while(k--) {
        pro *= arr[i];
        
        i = (i + 1) % n;
    }
    return pro;
}

int maxProduct2(vector<int> &arr, int k) {
    int n = arr.size();
    
    sort(arr.begin(), arr.end());
    
    if (k == 1) 
        return arr[n-1];
    
    int maxPro = INT_MIN;
        
    for (int i = 0; i < n; i++) {
        maxPro = max(maxPro, getProduct(arr, i, k));
    }
    
    return maxPro;
}

int main() {
    return 0;
}