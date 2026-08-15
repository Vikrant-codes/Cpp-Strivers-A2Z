#include<iostream>
#include<vector>
using namespace std;

// Cocktail Shaker Sort / Bidirectional Bubble Sort / Ripple Sort / Bouncing Bubble Sort
/*
A `Bidirectional Bubble Sort` algorithm — also known in computer science as the 
`Cocktail Shaker Sort`, `Ripple Sort` or `Bouncing Bubble Sort` — is a variation of the standard bubble sort algorithm.

Instead of repeatedly traversing the collection from the beginning to the end in every single pass, 
this algorithm reverses its direction each pass. 
The first pass moves left to right to push the largest element to the end, 
and the second pass immediately bounces back from right to left to pull the smallest element to the beginning.

So, the largest element “bubbles” to the right and then the smallest element “bounces” back to the left.

Normal Bubble Sort works in only one direction: 
    → → → → →
In each pass, adjacent elements are compared, so the largest unsorted element moves to the right.

Bidirectional Bubble Sort reverses the direction:
    → → → → →
    ← ← ← ← ←
    → → → → →
    ...
The backward pass causes the smallest unsorted element to move to the left.

So each complete cycle fixes two elements:
• forward → largest element goes to the right
• backward → smallest element goes to the left

>> How the Algorithm Works

1. Forward Pass: Scan the array from left to right. 
   Compare adjacent elements and swap them if they are in the wrong order. 
   This locks the largest remaining element at the end of the collection.

2. Boundary Shrinking: Reduce the upper bound of the unsorted segment since the end is now correctly sorted.

3. Backward Pass: Scan from right to left starting from the new upper bound down to the lower bound. 
   Swap out-of-order adjacent elements to pull the smallest remaining value to the front.

4. Boundary Shrinking: Increase the lower bound of the unsorted segment.

5. Repeat: Continue bouncing back and forth until a full pass occurs without any swaps, 
   meaning the array is completely sorted.

>> Comparison with Standard Bubble Sort

Feature          | Standard Bubble Sort                                 | Bidirectional Bubble Sort (Cocktail)
---------------------------------------------------------------------------------------------------------------------------
Traversals       | Unidirectional (always left-to-right)                | Bidirectional (alternates directions)
Turtle Handling  | Slow (small values at the end move left very slowly) | Fast (small values are immediately pulled left)
Worst-case Time  | O(n²)                                                | O(n²)
Best-case Time   | O(n) (when already sorted)                           | O(n) (when already sorted)
Space Complexity | O(1) (In-place sorting)                              | O(1) (In-place sorting)
*/


// Standard implementation
void cocktailSort(vector<int>& arr) {
    int n = arr.size();
    
    int left = 0;
    int right = n - 1;

    bool swapped = true;

    while (swapped) {
        swapped = false;

        // Forward pass
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // Largest element is now at 'right', shrink the boundary by decrementing right
        right--;

        // If no swap happened in forward pass, the array is sorted, so break out of loop / return
        if (!swapped) break;

        // Backward pass
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }

        // Smallest element is now at 'left', shrink the boundary by incrementing left
        left++;

        /*
        >> Why left and right are incremented / decremented?
        After one forward + backward cycle:
        [ sorted ][ unsorted portion ][ sorted ]
            ↑                              ↑
           left                           right
        So there's no reason to touch the already-sorted boundaries again.
        */
    }
}

// My first implementation
void bouncing_bubble_sort(vector<int>& arr) {
    int n = arr.size();

    int j = 0;
    bool direction_right = true;

    // total n-1 passes
    
    for (int i = 0; i < n-1; i++) {

        // if current pass direction is towards right, compare to shift the largest element to the right end
        if (direction_right) {
            // the right boundary has unsorted elements till index 'n-i-1', we go till j = n-i-2 to compare pair (n-i-2, n-i-1)
            while (j < n - i - 1) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
                j++;
            }
        }

        // else current pass direction is towards left, compare to shift the smallest element to the left end
        else {
            // the left boundary has unsorted elements starting from index 'i-1', so we go till j >= i (to compare pair (i, i-1))
            while (j >= i) {
                if (arr[j] < arr[j-1]) {
                    swap(arr[j], arr[j-1]);
                }
                j--;
            }
        }

        // reverse the direction for next pass
        direction_right = !direction_right;
    }
}

int main() {
    vector<int> arr = {9,1,3,7,2,5,6,4,8};

    bouncing_bubble_sort(arr);

    for (int x : arr)
        cout << x << " ";

    return 0;
}