// Finding second largest element & second smallest element in an array

#include <iostream>
#include <vector>
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

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
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
    
    return secondMax;
}


int main() {
    return 0;
}