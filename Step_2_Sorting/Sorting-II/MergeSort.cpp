#include <iostream>
#include <vector>
using namespace std;

// Merge Sort

/*
The key idea is:
Instead of trying to sort the whole array at once, 
keep splitting it into smaller arrays until each piece is trivially sorted, 
then merge those sorted pieces back together.

Suppose we have: [5, 2, 4, 1, 3, 6]

1. Divide
Keep splitting the array in half:

        [5, 2, 4, 1, 3, 6]
            /           \
     [5, 2, 4]        [1, 3, 6]
       /    \            /   \
    [5]   [2,4]        [1]  [3,6]
           / \              / \
         [2] [4]          [3] [6]

Eventually, every subarray contains one element, which is already sorted.

2. Merge
Now merge the smaller sorted arrays while maintaining sorted order:

    [2] + [4]       → [2, 4]
    [5] + [2, 4]    → [2, 4, 5]

    [3] + [6]       → [3, 6]
    [1] + [3, 6]    → [1, 3, 6]

    [2, 4, 5] + [1, 3, 6]
                    → [1, 2, 3, 4, 5, 6]

The important observation is that merging two sorted arrays is linear.
For example:
    A = [2, 5, 8]
    B = [1, 3, 7]
Compare the first elements:
    2 vs 1 → take 1
    2 vs 3 → take 2
    5 vs 3 → take 3
    5 vs 7 → take 5
    8 vs 7 → take 7
    take remaining 8
Result = [1, 2, 3, 5, 7, 8]
We use two pointers, one for each sorted half.

>> Basic Algorithm

mergeSort(array):

    if array has 0 or 1 element:
        return

    mid = middle of array

    mergeSort(left half)
    mergeSort(right half)

    merge the two sorted halves

So there are really only two operations:
    - Divide the array into halves recursively.
    - Merge the sorted halves.

>> Time Complexit: O(n log n)
There are two dimensions to think about:

1. Recursive diving of array into two halves
Number of levels: log n
Every time we divide the array, its size is cut in half:
    n
    n/2
    n/4
    n/8
    ...
    1
It takes approximately log₂ n divisions to reach arrays of size 1.

2. Merging the two halves: Work at each level: O(n)
At every level, all elements are eventually processed during merging.
For example:
    Level 1:        n       work
    Level 2:        n       work
    Level 3:        n       work
    ...
    Level log n:    n       work

So: O(n) × O(log n) = O(n log n)

Thus, time: O(n log n) : Best, Average & Worst Case

>> Space Complexity: O(n) auxiliary space.
During merging, we generally create temporary storage for the merged result.
The recursion stack itself is O(log n), but the temporary arrays used for merging dominate, giving: Space = O(n)
*/

void merge(vector <int> &arr, int low, int mid, int high){
    vector<int> temp;
    int left = low;             // start position of the first half
    int right = mid+1;          // start position of the second half

    // Merging the two halves : compare element at left & at right .. push the smaller one into the temp array
    while (left <= mid && right <= high) {
        if(arr[left] <= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }
    // if any elements are left in the first half, push them into the temp array
    while(left <= mid){
        temp.push_back(arr[left]);
        left++;
    }
    // if any elements are left in the second half, push them into the temp array
    while(right <= high){
        temp.push_back(arr[right]);
        right++;
    }
    // Copy the elements from temp array back to the original array
    for(int i=low; i<= high; i++){
        arr[i] = temp[i-low];
    }
}

void mergeSort(vector <int> &arr, int low, int high){
    // Base condition
    if(low >= high) 
        return;      
    
    int mid = low + (high - low) / 2;
    // mid = (low + high) / 2

    mergeSort(arr, low, mid);       // call mergeSort for left half -> this will sort the left half
    mergeSort(arr, mid+1, high);    // call mergeSort for right half -> this will sort the right half
    merge(arr, low, mid, high);     // Merge the two sorted halves
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int n = arr.size();

    mergeSort(arr, 0, n-1);
    
    for(int x: arr) cout << x << " ";

    return 0;
}