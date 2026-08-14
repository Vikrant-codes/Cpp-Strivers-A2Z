#include<iostream>
#include<vector>
using namespace std;

// Selection Sort

/*
Selection sort divides the array into a sorted prefix and an unsorted part.
In each pass, we select the minimum element from the unsorted part and
place it at the beginning of that part (i.e., at index i).
This is why it is called "Selection" sort — we select the minimum each pass.
After every pass, one element reaches its final position.
Therefore, for an array of size n, we need n - 1 passes.

---

Find the minimum element in the array and swap it with the first element. Repeat for n-1 passes.

For n elements n-1 passes are required
Pass 1 : starting from index 0 find the minimum and swap it with arr[0]
Pass 2 : starting from index 1 find the minimum and swap it with arr[1]
Pass 3 : starting from index 2 find the minimum and swap it with arr[2]
.... 
Pass n-1 : starting from index n-2 find the minimum and swap it with arr[n-2]

Ex - [4,3,2,1]
Pass 1 : curr = 4, min = 1, swap 4 & 1 ... array becomes [1,3,2,4]
Pass 2 : curr = 3, min = 2, swap 3 & 2 ... array becomes [1,2,3,4]
Pass 3 : curr = 3, min = 3, no swap ... array remains same [1,2,3,4]

--- 
Complexity Analysis

Time Complexity: O(n²) in all cases — best, average, and worst.
- The inner loop scans the remaining elements for every i.
- Comparisons are approximately n(n-1)/2.
- Even if the array is already sorted, we still scan the remaining elements to find the minimum.

Space Complexity: O(1)
- Only a few variables are used.
- Sorting is done in-place.
*/

void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int minInd = i;

        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minInd]) {
                minInd = j;
            }
        }

        swap(arr[i], arr[minInd]);
    }
}

/*
If we want to use array instead of vector, 
we would have to pass the array size `n` as a parameter to the sorting function
because array decays to pointer when passed to function 
and thus we won't be able to calculate `n` inside the function using sizeof(arr) / sizeof(arr[0])
*/

int main() {
    return 0;
}