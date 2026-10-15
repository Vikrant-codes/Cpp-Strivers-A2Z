#include<iostream>
#include<vector>
using namespace std;

// Insertion Sort

/*
Insertion Sort is a sorting algorithm that builds a sorted portion of the array 
one element at a time by inserting each element into its correct position.
Think of how we arrange playing cards in our hand: 
we pick one card and insert it into the correct position among the cards we've already sorted.

Insertion sort builds the sorted array one element at a time.
Assume the left portion of the array is already sorted.
Pick the next element (key) and compare it with elements on its left.
Shift all larger elements one position to the right and insert the key at its correct position.

After each pass, the sorted portion grows by one element.
Therefore, for an array of size n, we need at most n - 1 passes.

>> Complexity Analysis

>>> Time Complexity: O(n) best, O(n²) — average & worst cases.

Best Case: O(n)
- Array is already sorted.
- Each element is compared once with its predecessor and no shifting is needed.
- For each element, the algorithm checks if it is smaller than the element to its left. 
  Because the array is already sorted, this comparison immediately returns false.
- The inner loop never executes its body, meaning zero element swaps or shifts take place. 
  The algorithm only performs a single comparison for each position to verify the order, 
  resulting in exactly n - 1 total comparisons.

Average Case: O(n²)
- Elements generally need some shifting.

Worst Case: O(n²)
- Array is sorted in reverse order.
- Every new element has to be shifted all the way to the beginning.

>>> Space Complexity: O(1)
Sorting is done in-place and only a few extra variables are used
*/

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        
        // Shift all larger elements (> key) in the sorted portion, one position to the right.
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // After the loop, either j == -1 (when key is smallest), or arr[j] <= key. 
        
        arr[j + 1] = key;       // Insert key at its correct position
    }
}

// Other Implementation
/*
For each index i, we try to insert arr[i] at the correct position in the sorted portion.

Instead of shifting elements to the right, we can also use adjacent swaps.
Starting from j = i, we compare the current element arr[j] with the element just before it, arr[j - 1]. 
If arr[j] is smaller, we swap them and move one position left. 
This moves the larger element one position to the right and 
places the current element one position closer to its correct position.

We continue as long as arr[j - 1] > arr[j].
The process stops when arr[j - 1] <= arr[j], or when j becomes 0.

In other words, the current element "bubbles left" in the sorted portion until it reaches its correct position.
*/

void insertionSort2(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int j = i;
        
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

int main() {
    return 0;
}