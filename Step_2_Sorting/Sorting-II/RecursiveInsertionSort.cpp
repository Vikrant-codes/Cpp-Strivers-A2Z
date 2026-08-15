#include <iostream>
using namespace std;

// Recursive implementation of Insertion Sort
/*
Time Complexity: 
    O(n) - Best Case
    O(n^2) - Average & Worst Case
    
Space Complexity: O(n) - Recursive Stack Space
*/

void insertion_sort(int arr[], int i, int n) {
    // Base Case: if index reaches the size, return
    if (i == n) return;

    int j = i;
    // Shift the element to the left while it's smaller than its predecessor
    while (j > 0 && arr[j] < arr[j-1]) {
        // Swap arr[j] and arr[j-1]
        swap(arr[j], arr[j-1]);
        j--;
    }

    // Recurse for the next index
    insertion_sort(arr, i+1, n);
}

int main() {
    int arr[] = {46, 28, 91, 55, 64, 19, 37, 82, 73};

    int n = sizeof(arr) / sizeof(arr[0]);
 
    insertion_sort(arr, 1, n);

    cout << "After Using Insertion Sort: " << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}