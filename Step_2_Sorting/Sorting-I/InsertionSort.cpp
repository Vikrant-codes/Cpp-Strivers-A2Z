#include<iostream>
#include<vector>
using namespace std;

// Insertion Sort

/*
Insertion sort builds the sorted array one element at a time.
Assume the left portion of the array is already sorted.
Pick the next element (key) and compare it with elements on its left.
Shift all larger elements one position to the right and insert the key at its correct position.
This is similar to how we arrange cards in our hand.

After each pass, the sorted portion grows by one element.
Therefore, for an array of size n, we need at most n - 1 passes.

---
Complexity Analysis

Time Complexity: O(n) best, O(n^2) average, O(n^2) worst

Best Case: O(n)
- Array is already sorted.
- Each element is compared once with its predecessor and no shifting is needed.

Average Case: O(n²)
- Elements generally need some shifting.

Worst Case: O(n²)
- Array is sorted in reverse order.
- Every new element has to be shifted all the way to the beginning.

Space Complexity: O(1)
Sorting is done in-place and only a few extra variables are used
*/

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i-1;
        
        // Shift all elements in the sorted portion that are greater than temp, one position to the right.
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // After the loop, either j == -1 (when temp is smallest), or arr[j] <= temp. 
        // Therefore, temp belongs at j + 1.
        arr[j + 1] = temp;
    }
}

// Other Implementation
/*
For each index i, we take arr[i] and try to insert it into the sorted portion.

Instead of shifting elements like the usual insertion sort, we use adjacent swaps.
Starting from j = i, we compare the current element arr[j] with the element just before it, arr[j - 1]. 
If arr[j] is smaller, we swap them and move one position left. 
This moves the larger element one position to the right and 
places the current element one position closer to its correct position.

We continue as long as arr[j - 1] > arr[j].
The process stops when arr[j - 1] <= arr[j], or when j becomes 0.

In other words, the current element "bubbles left" through the sorted portion until it reaches its correct position.
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