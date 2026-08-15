#include <iostream>
using namespace std;

// Recursive implementation of Bubble Sort (Normal Bubble Sort)
/*
Time Complexity: O(n^2) - Best, Average & Worst Case
Space Complexity: O(n) - Recursive Stack Space
*/

void bubble_sort(int arr[], int n) {
    // Base Case: If the array size is 1, it's already sorted
    if (n == 1) return;

    // Perform one pass of Bubble Sort: push the largest element to the end
    // the current array size is `n`, so we check adjacent element pairs till pair (arr[n-2], arr[n-1])
    for (int j = 0; j <= n-2; j++) {
        // Swap if elements are in the wrong order
        if (arr[j] > arr[j+1]) {
            swap(arr[j], arr[j+1]);
        }
    }

    // Recurse for the remaining unsorted part (one less than before)
    bubble_sort(arr, n-1);
}

// Optimised Recursive Bubble Sort (Early exit when no swap happens during a pass)
/*
Time Complexity: O(n) - Best Case __ O(n^2) - Average & Worst Case
Space Complexity: O(n) - Recursive Stack Space
*/ 

void bubbleSort(int arr[], int n) {
    if (n == 1) return;

    bool didSwap = false;       // Flag to check if any swap occurred in this pass

    for (int j = 0; j <= n-2; j++) {
        if (arr[j] > arr[j+1]) {
            swap(arr[j], arr[j+1]);
            didSwap = true;             // set the flag variable since we did swap values
        }
    }

    // If no swap happened, array is already sorted, so no need to perform further passes, return
    if (!didSwap) return;

    bubbleSort(arr, n-1);
}

int main() {
    int arr[] = {46, 28, 91, 55, 64, 19, 37, 82, 73};

    int n = sizeof(arr) / sizeof(arr[0]);
 
    bubbleSort(arr, n);

    cout << "After Using Bubble Sort: " << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}