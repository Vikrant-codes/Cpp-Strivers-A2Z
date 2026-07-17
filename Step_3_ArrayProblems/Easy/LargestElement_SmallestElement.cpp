// Finding largest element & smallest element in an array

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
GFG - Largest in Array : Basic

Given an array arr[]. The task is to find the largest element and return it.

Examples :-

Input: arr[] = [1, 8, 7, 56, 90] __ Output: 90
Explanation: The largest element of the given array is 90.

Input: arr[] = [5, 5, 5, 5] __ Output: 5
Explanation: The largest element of the given array is 5.

Input: arr[] = [10] __ Output: 10
Explanation: There is only one element which is the largest.

Constraints :-
• 1 <= arr.size()<= 10^6
• 0 <= arr[i] <= 10^6
*/

// Naive Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
- Sort the array
- After sorting, the largest element of the array moves to the last index (at index arr.size()-1)
- Return arr[n-1], where n is size of array

>> Time Complexity Analysis
- Sorting the array takes O(n log n) time.
- After sorting, the largest element can be get in O(1) since it is present at last index.
*/
int largestNaive(vector<int> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    return arr[n-1];
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Use a variable to store the maximum value, initialize it with the value of first element of the array.
- Traverse the array using a for loop to get each element one by one.
- In each iteration, compare the current element with the max variable.
- If the current element is greater than the max value, update the max value with the current element's value.
- After completing the loop, return max variable, which will hold the value of largest element of the array.

>> Time Complexity Analysis
- We are just iterating through the array once, so O(n)
*/ 
int largest(vector<int> &arr) {
    int n = arr.size();
    int mx = arr[0];
    // we can also initialize 'mx' with a minimum value that arr[i] can have, like INT_MIN or -1 depending on constraints
    
    for (int i = 0; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
            
    return mx;
}

// Using built-in method
int largestElement(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
    // max_element() -> returns an iterator pointing to the maximum element's location in memory
    // so to get the maximum value, we use the derefence operator (*) to get the value :- *max_element()
}

// <-- Finding Smallest Element in Array -->
// Smallest Element can also be found in similar way

// Naive Approach : Time Complexity : O(n log n) __ Space Complexity : O(1)
/*
- Sort the array
- After sorting, the smallest element can be found at the 1st position (0th index)
*/
int smallestNaive(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    return arr[0];
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Use a variable to store the minimum value, initialize it with the value of first element of the array.
- Traverse the array using a for loop to get each element one by one.
- In each iteration, compare the current element with the min variable.
- If the current element is smaller than the min value, update the min value with the current element's value.
- After completing the loop, return min variable, which will hold the value of smallest element of the array.
*/ 
int smallest(vector<int> &arr) {
    int n = arr.size();
    int mn = arr[0];
    // we can also initialize 'mn' with the maximum value that arr[i] can have, like INT_MAX or any other value depending on constraints
    
    for (int i = 0; i < n; i++)
        if (arr[i] < mn)
            mn = arr[i];
            
    return mn;
}

// Using built-in method
int smallestElement(vector<int>& arr) {
    return *min_element(arr.begin(), arr.end());
    // min_element() -> returns an iterator pointing to the minimum element's location in memory
    // so to get the minimum value, we use the derefence operator (*) to get the value :- *min_element()
}

int main() {
    return 0;
}