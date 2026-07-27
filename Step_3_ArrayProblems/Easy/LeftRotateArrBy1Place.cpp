#include <iostream>
#include <vector>
using namespace std;

// Left Rotate an Array by 1 Place
/*
Left-rotating an array by one place means shifting every element one position to the left 
and moving the very first element to the last (end) position. 

For example, if you start with [1, 2, 3, 4, 5], a single left rotation changes it to [2, 3, 4, 5, 1].
*/

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Save the first element into a temp variable, so its value is not lost when we shift the other elements to the left.
- Left shift other elements:- element at index 'i' moves to 'i - 1'
- Place the temp variable value at the last index since it moves to the last index after left shift.
*/
void leftRotate(vector<int>& arr) {
    int n = arr.size();
    int temp = arr[0];

    for (int i = 0; i < n-1; i++) 
        arr[i] = arr[i+1];

    arr[n-1] = temp;
}

// ------------------------------------------------------------------------------------------------------------------------------

// Right Rotate an Array by 1 Place

/*
Right-rotating an array by one place means shifting every element one position to the right 
and moving the last element to the first position. 

For example, if you start with [1, 2, 3, 4, 5], a single right rotation changes it to [5, 1, 2, 3, 4].
*/
/*
GFG - Rotate Array by One : Basic

Given an array arr, rotate the array by one position in clockwise direction.

Examples :-

Input: arr[] = [1, 2, 3, 4, 5]
Output: [5, 1, 2, 3, 4]
Explanation: If we rotate arr by one position in clockwise 5 come to the front and remaining those are shifted to the end.

Input: arr[] = [9, 8, 7, 6, 4, 2, 1, 3]
Output: [3, 9, 8, 7, 6, 4, 2, 1]
Explanation: After rotating clock-wise 3 comes in first position.

Constraints :-
• 1 ≤ arr.size() ≤ 10^5
• 0 ≤ arr[i] ≤ 10^5
*/

// Optimal Approach : Time Complexity : O(n) __ Space Complexity : O(1)
/*
- Save the last element into a temp variable, so its value is not lost when we shift the other elements to the right.
- Right shift other elements:- element at index 'i' moves to 'i + 1'
- To right shift elements, we start the traversal from right end and do
    arr[i] = arr[i-1] 
    (current element gets value of its previous element)
- Place the temp variable value at the first index since it moves to the first index after right shift.
*/
void rightRotate(vector<int>& arr) {
    int n = arr.size();
    int temp = arr[n-1];
    
    for (int i = n-1; i > 0; i--)
        arr[i] = arr[i-1];
        
    arr[0] = temp;
}

int main() {
    return 0;
}