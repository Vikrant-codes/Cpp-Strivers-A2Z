#include<iostream>
#include<vector>
using namespace std;

// Bubble Sort

/*
Bubble Sort is a sorting algorithm that repeatedly compares adjacent elements 
and swaps them if they are in the wrong order.

For ascending order, if the left element is greater than the right element, we swap them.

The key idea: After each pass, the largest unsorted element "bubbles up" (moves) to the end of the array, 
just like a bubble rising to the surface.
Hence the name Bubble Sort.

After each pass, one largest element reaches its final position.
Therefore, we need n - 1 passes in the worst case.

>> Complexity Analysis

>>> Time Complexity: O(n²) — best, average, and worst case.

>>> Space Complexity: O(1) — sorting is done in-place.
*/

void bubbleSortNaive(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Optimized Bubble Sort
/*
The previous implementation always runs for O(n²) even when the array is already sorted, 
or gets sorted before n - 1 passes.

To optimize this, we track whether any swap happened during a pass or not (using a boolean flag variable). 
If no swap occurs, the array is already sorted, so we make early exit instead of completing the remaining passes.
This makes Bubble Sort faster when the array is already or nearly sorted.
Worst case: n - 1 passes; best case: just 1 pass.

>> Complexity Analysis

>>> Time Complexity: O(n) best case, O(n^2) average/worst case

-> Why does the best case become O(n)?
Consider an already sorted array: [1, 2, 3, 4, 5]
During the first pass, we compare every adjacent pair:
    1 < 2
    2 < 3
    3 < 4
    4 < 5
No swaps happen, so didSwap remains false. We stop the algorithm after a single pass.
One pass makes n - 1 comparisons → O(n).
Without the optimization, we would continue making approximately n²/2 comparisons even though the array is already sorted.

>>> Space Complexity: O(1) — in-place sorting.
*/

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // if no swap done in a pass that means array is sorted so break out of the loop or return
        if (!swapped)
            break;
    }
}

int main() {
    return 0;
}