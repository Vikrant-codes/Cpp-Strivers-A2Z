/*
GFG - Check Sorted Array : Easy

Given an array arr[], check whether it is sorted in non-decreasing order. Return true if it is sorted otherwise false.

Examples :-

Input: arr[] = [10, 20, 30, 40, 50] __ Output: true

Input: arr[] = [90, 80, 100, 70, 40, 30] __ Output: false

Constraints :-
• 1 ≤ arr.size ≤ 10^6
• - 10^9 ≤ arr[i] ≤ 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Naive Approach : Time Complexity : O(n log n) __ Space Complexity : O(n)
/*
>> Naive Approach
If arr is sorted, then if we sort arr and store that sorted values in a different vector (temp), 
then temp and arr should remain same.

Ex: assume arr = [1, 2, 3, 5, 4]
    if we sort these values and store them in temp: temp = [1, 2, 3, 4, 5]
    Now, since temp != arr, this means arr is not sorted
- Use a temporary vector initialized with same values as arr
- Sort this temporary vector
- If arr is sorted, then this sorted temporary vector and arr must still be equal
- Check if temp == arr, if true arr is sorted, else not sorted
*/
bool isSortedNaive(vector<int>& arr) {
    int n = arr.size();

    vector<int> temp = arr;

    sort(temp.begin(), temp.end());

    return temp == arr;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)

/*
>> Approach 1 
We need to check whether the given array is sorted in non-decreasing order or not.
Non-decreasing order means from the start till end, 
the value of elements either remains same or increases but never decreases.

Example -> 
arrays [1, 2, 3, 4, 5, 5, 6] and [1, 2, 3, 3, 3] are sorted in non-decreasing order
whereas the array [3, 4, 3, 5] is not sorted in non-decreasing order since after 4, the next element is 3 which is smaller.

So, we can iterate over the array and write some logic to check that the value of elements never goes down (decreases)
If the value of elements decreases, it means the array is not sorted.
We can maintain a previous seen value while iterating and check that current element is greater than or equal to this value.
If the current element is smaller than this value, it means there is a decrease in value, so return false.
*/
bool isSorted1(vector<int>& arr) {
    int n = arr.size();
    
    int val = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (val > arr[i])
            return false;
            
        val = arr[i];
    }
            
    return true;
}

/*
>> Approach 2 
The array is said to be sorted in non-decreasing order, when all the elements are >= their previous index element.
For the array to be sorted in non-decreasing order, 
all the consecutive pairs of array elements must be such that arr[i] >= arr[i-1]
So, while traversing if we find an element arr[i] such that arr[i] < arr[i-1], it means the array is not sorted. 
So, return false.
If such an element is not found and traversal ends, return true.
*/
bool isSorted2(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) 
        if (arr[i] < arr[i-1])
            return false;
            
    return true;
}

int main() {
    return 0;
}