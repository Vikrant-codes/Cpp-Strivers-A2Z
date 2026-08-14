#include<iostream>
#include<vector>
using namespace std;

// Bubble Sort

/*
Compare adjacent elements and swap them if they are in the wrong order.
In each pass, the largest element in the unsorted part "bubbles up" to the end of the array (due to adjacent swapping). 
Hence the name Bubble Sort.
After each pass, one largest element reaches its final position.
Therefore, we need n - 1 passes in the worst case.

---
Complexity Analysis

Time Complexity: O(n^2) in best, average, and worst cases
Even if the array is already sorted, the algorithm still performs all the comparisons 
because there is no condition to stop early.

Space Complexity: O(1) — sorting is done in-place.
*/

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Optimised Bubble Sort
/*
Same idea as normal Bubble Sort, but we keep track of whether any swap happened during a pass (using a flag variable). 
If no swap occurs, the array is already sorted, so we stop early instead of completing all remaining passes.
This makes Bubble Sort faster when the array is already or nearly sorted.
Worst case: n - 1 passes; best case: just 1 pass.

--- 
Complexity Analysis

Time Complexity: O(n) best case, O(n^2) average/worst case

>> Why does the best case become O(n)?
Consider an already sorted array: [1, 2, 3, 4, 5]
During the first pass, we compare every adjacent pair:
    1 < 2
    2 < 3
    3 < 4
    4 < 5
No swaps happen, so didSwap remains false. We stop the algorithm after just the single pass.
One pass makes n - 1 comparisons → O(n).
Without the optimization, we would continue making approximately n²/2 comparisons even though the array is already sorted.

Space Complexity: O(1) — in-place sorting.
*/

void optimizedBubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        bool didSwap = false;
        
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                didSwap = true;
            }
        }
        
        // if no swap done in a pass that means array is sorted so break out of the loop or return
        if (!didSwap) break;
    }
}

int main() {
    return 0;
}