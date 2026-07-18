// Finding second largest element & second smallest element in an array

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
GFG - Second Largest : Easy

Given an array of positive integers arr[], return the second largest element from the array. 
If the second largest element doesn't exist then return -1.

Note: The second largest element should not be equal to the largest element.

Examples :-

Input: arr[] = [12, 35, 1, 10, 34, 1] __ Output: 34
Explanation: The largest element of the array is 35 and the second largest element is 34.

Input: arr[] = [10, 5, 10] __ Output: 5
Explanation: The largest element of the array is 10 and the second largest element is 5.

Input: arr[] = [10, 10, 10] __ Output: -1
Explanation: The largest element of the array is 10 and the second largest element does not exist.

Constraints :-
• 2 ≤ arr.size() ≤ 10^5
• 1 ≤ arr[i] ≤ 10^5
*/

// Naive Approach : Time Complexity : O(n log n) + O(n) __ Space Complexity : O(1)
/*
We need to find the second largest element which should not be equal to largest element.
So, for array like [2, 4, 1, 3, 5, 3, 5], the second largest element is 4 (not 5, even though 5 appears twice)
If we sort the array, it becomes [1, 2, 3, 3, 4, 5, 5]
If array had only distinct values, we could have directly returned the value at index n-2 as it would have been second maximum.
But, since array have duplicates, we need to find that value which is not equal to maximum (arr[n-1]).
So, we iterate from index n-2 to 0, and return the first element whose value is not equal to maximum (arr[n-1]).
In case, no such element exists, we need to return -1. For example cases like arr = [5, 5, 5, 5, 5]

- Sort the array
- Traverse from index n - 2 to index 0
- Return the first element we find in this direction whose value is not equal to maximum (arr[n-1])
- Since we are iterating from right end, the first such value encountered would be the second maximum (due to sorting).
- If loop exits without returning, it means second maximum doesn't exists, return -1.

>> Time Complexity Analysis:- 
- Sorting the array : O(n log n)
- Finding second maximum : 
    We need to traverse from index n-2 to index 0, to find the first element whose value is not equal to the maximum value.
    In the worst case scenario, array might be having all elements with same value, 
    in that case, we would just traverse the whole array and return -1 at end
    Ex case -> arr = [5, 5, 5, 5, 5]
    So, for such worst cases, it would take O(n) to find the second maximum. So O(n)
- Total : O(n log n) + O(n)
*/
int getSecondLargestNaive(vector<int> &arr) {
    int n = arr.size(); 
    
    sort(arr.begin(), arr.end());
    
    for (int i = n - 2; i >= 0; i--) 
        if (arr[i] != arr[n-1])
            return arr[i];
            
    return -1;
}

// Better Approach (Two Pass Search) : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
The approach is to traverse the array twice.
In first traversal, find the maximum element.
Now, we can traverse again and look for the another maximum value such that this value is not equal to the maximum element 
we found in the first traversal.

Ex - assume arr = [2, 5, 1, 4, 3, 5]
We traverse once and find that max = 5
Now, we again traverse the array and find the maximum value which is not equal to 5.
For this array, that value would be 4. So we return it as it is the second Maximum.

- Initialize max with a minimum value that arr[i] can have or we can also initialize it with arr[0]
- Traverse the array once and update the max variable so that it stores the maximum value of the array.
- Initialize secondMax variable
- Again traverse the array, but this time, find the maximum value while not considering the elements with 'max' value
- In case of array having no secondMax variable, the secondMax variable value would remain equal to what we initialized.
- So, we can check that to return -1. 
- if secondMax == initialzed_value -> means no secondMax exists, return -1
- else return secondMax

>> Time Complexity Analysis :-
- We are iterating the whole array twice, once to find maximum and another time to find the secondMaximum
- Thus, O(n) + O(n) = O(2*n)
*/
int getSecondLargestBetter(vector<int> &arr) {
    int n = arr.size(); 
    
    int max = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
            
    int secondMax = -1;
    // we have initialized secondMax with the value '-1' (notice that we initialized max with 0)
    // this initialization of secondMax with -1 helps us as we don't need to check for cases when no secondMax exists
    for (int i = 0; i < n; i++) 
        if (arr[i] > secondMax && arr[i] != max)
            secondMax = arr[i];
            
    // we can directly return secondMax as even if all array elements are equal to max
    // and secondMax doesn't get updated, it value remains -1, so we can directly return that and no need to handle such cases
    return secondMax;

    // if we had initialized secondMax with some other value (like 0 or INT_MIN), then
    // we would have to check condition if (secondMax == initialized_value), to return -1 or secondMax accordingly
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
The idea is to keep track of the largest and second largest element while traversing the array. 
Initialize max and secondMax with -1. (so, we won't have to explicitly check for cases when secondMax doesn't exists)
We know traverse the array and try to find and maintain both max & secondMax in a single traversal.
Let's see what happens when we traverse the arr. Suppose arr[i] is the current element, then there can be different cases

- If arr[i] > max
    current element is greater than max itself, that means we need to update max.
    But the value max has currently which we considered to be the maximum till now, has now become secondMaximum value 
    due to appearing of a new maximum.
    So, before updating value of max, we must firstly assign its value to secondMax. 
        secondMax = max
        max = arr[i]

- Else if arr[i] > secondMax
    This means current element value is greater than secondMax, but smaller than or equal to max.
    So, ideally we should update the value of secondMax, 
    but before doing so, we must check that this arr[i] must not be equal to max
    So, we must update secondMax for such case only when arr[i] != max
    hence the condition becomes arr[i] > secondMax and arr[i] != max.
        if (arr[i] > secondMax && arr[i] != max)
            secondMax = arr[i]

>> Time Complexity Analysis :-
- We are finding both max & secondMax in a single traversal. So, O(n)
*/
int getSecondLargest(vector<int> &arr) {
    int n = arr.size();
    
    int max = -1, secondMax = -1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            secondMax = max;
            max = arr[i];
        }
        else if (arr[i] > secondMax && arr[i] != max) {
            secondMax = arr[i];
        }
    }
    
    // no need to explicitly check for condition to return -1 since we initialized max & secondMax with -1 itself
    return secondMax;
}

// <-- Finding the second smallest element in the array -->
/*
Asssume for the given same constraints, we need to find the second smallest element in the array.

• 2 ≤ arr.size() ≤ 10^5
• 1 ≤ arr[i] ≤ 10^5

and in case of second smallest element not existing, we need to return -1.
*/
// The second smallest element can be found in similar fashion

// Naive Approach : Time Complexity : O(n log n) + O(n) __ Space Complexity : O(1)
/*
- Sort the array
- After sorting, the smallest element comes down to index 0.
- Now since we need the second smallest, we should start iterating from index 1 to end and 
    return the first element which is not equal to arr[0]
- In case, no such element exists, we return -1 after loop ends

>> Time Complexity Analysis :-
- Sorting takes O(n log n)
- Similar to how when finding second maximum, we needed to traverse the entire array for worst case scenarios,
    here also, we may need to traverse the entire array to find the secondMinimum
    Ex cases - arr = [1, 1, 1, 1, 1] or arr = [1, 1, 1, 1, 2]
    in both such cases, we traverse the whole array after sorting to find the secondMax (if it exists) or return -1.

So, Time Complexity : O(n log n) + O(n)
*/
int getSecondSmallestNaive(vector<int> &arr) {
    int n = arr.size();

    sort(arr.begin(), arr.end());

    for (int i = 1; i < n; i++) 
        if (arr[i] != arr[0])
            return arr[i];

    return -1;
}

// Better Approach (Two Pass Search) : Time Complexity : O(2*n) __ Space Complexity : O(1)
/*
Similar to how we used two pass solution to find the second maximum.

Here, we traverse the array once to find the minimum value (min)
Then, we again traverse and find the second minimum value such that its value is not equal to min.

In case of second minimum not existing, the second traversal would not update the value of secondMin 
and the value of secondMin will remain eqaul to what we initialized, 
so we just need to check if its (secondMin's) value has been updated or not.
If yes, we return secondMin, else return -1.
*/
int getSecondSmallestBetter(vector<int> &arr) {
    int n = arr.size();

    int min = 100000;
    // we initialized min with 100000 (which is 10^5), since constraints tell us that this is the max. value arr[i] can have
    // we could have also initialized it with any value greater than 10^5 like INT_MAX, or even arr[0] (in case of minimum) 
    for (int i = 0; i < n; i++) 
        if (arr[i] < min)
            min = arr[i];

    int secondMin = 100000;
    // we can initialize secondMin with any value >= 100000, 
    // but we can't initialize it with with any array element value directly like arr[0] (since this could be minimum itself)
    for (int i = 0; i < n; i++) 
        if (arr[i] < secondMin && arr[i] != min)
            secondMin = arr[i];

    // now, we need to check for cases when second minimum doesn't exists and secondMin's value is not updated
    return (secondMin == 100000) ? -1 : secondMin;
}

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
Similar to finding secondMaximum, we can also find the secondMinimum in a single traversal.
Here also, two conditions might come when traversing the array while maintaining min & secondMin

- If arr[i] < min
    current element is smaller than min itself, that means we need to update min.
    Also, before updating min, we need to assign its value to secondMin and then update the value of min 
        secondMin = min
        min = arr[i]

- Else if arr[i] > secondMin
    This means current element value is smaller than secondMin, but greater than or equal to min.
    So, we need to check that this arr[i] must not equal to min and update secondMin only when this condition check is true
        if (arr[i] < secondMin && arr[i] != min)
            secondMin = arr[i]
*/
int getSecondSmallest(vector<int> &arr) {
    int n = arr.size();
    
    int min = 100000, secondMin = 100000;

    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            secondMin = min;
            min = arr[i];
        }
        else if (arr[i] < secondMin && arr[i] != min) {
            secondMin = arr[i];
        }
    }

    return (secondMin == 100000) ? -1 : secondMin;
}

int main() {
    return 0;
}