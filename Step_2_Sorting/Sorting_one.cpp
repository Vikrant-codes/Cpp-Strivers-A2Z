/* 
Selection Sort, Bubble Sort & Insertion Sort
    --> Selection Sort : Find the minimum element in the array and swap it with the first element. Repeat for n-1 passes.
    --> Bubble Sort : Push the maximum element to the last by adjacent swaps in each pass... n-1 passes reuired
    --> Insertion Sort : Insert the current element at its correct position in the already sorted part of the array.

# Stable Sort : A sorting algorithm is said to be stable if it preserves the relative order of equal elements in the sorted output.
Insertion Sort & Bubble Sort are stable sort. Selection Sort is not a stable sort.

# In-place Sort : A sorting algorithm is said to be in-place if it requires only a constant amount of extra space.
Insertion, Bubble & Selection Sort are all in-place sorting algorithms.

# Adaptive Sort : A sorting algorithm is said to be adaptive if it takes advantage of existing order in its input.
Insertion Sort is adaptive. Selection and Bubble Sort are not adaptive.

# Online Sort : Online sorting algorithms process and sort data as it arrives, without having the entire input available initially. 
They are useful for streaming or dynamic data where continuous updates occur. Examples include: Insertion Sort
Insertion Sort is online sorting algo as it inserts incoming elements into their correct position in a sorted list.
Selection Sort and Bubble Sort are offline sorting algorithms, as they require the entire input to be available before sorting can begin.

# Sorting Algorithms Comarison
Algorithm	    Best Case     Average Case     Worst Case     Space Complexity     Stable?     Online?     In-Place?     Adaptive?

Selection Sort	𝑂(𝑛²)	        𝑂(𝑛²)            𝑂(𝑛²)	       𝑂(1)	             ❌ No      ❌ No       ✅ Yes	      ❌ No
Bubble Sort	    𝑂(𝑛)	        𝑂(𝑛²)	           𝑂(𝑛²)  	   𝑂(1)	             ✅ Yes     ❌ No       ✅ Yes	      ✅ Yes
Insertion Sort	𝑂(𝑛)	        𝑂(𝑛²)	           𝑂(𝑛²) 	       𝑂(1)	             ✅ Yes     ✅ Yes      ✅ Yes	      ✅ Yes
Quick Sort	    𝑂(𝑛 log𝑛)	 𝑂(𝑛 log𝑛)	     𝑂(𝑛²)         𝑂(log 𝑛) (recursive)	❌ No	  ❌ No       ✅ Yes	     ❌ No
Merge Sort	    𝑂(𝑛 log𝑛)	 𝑂(𝑛 log𝑛)	     𝑂(𝑛 log 𝑛)	  𝑂(𝑛) (extra array)	 ✅ Yes	   ❌ No       ❌ No	      ❌ No
Heap Sort	    𝑂(𝑛 log𝑛)	 𝑂(𝑛 log𝑛)	     𝑂(𝑛 log 𝑛)	  𝑂(1) (in-place)	    ❌ No	  ✅ Yes      ✅ Yes	     ❌ No
Counting Sort	𝑂(𝑛+𝑘)	     𝑂(𝑛+𝑘)	         𝑂(𝑛+𝑘)	      𝑂(𝑛+𝑘)	              ✅ Yes	    ❌ No       ❌ No	       ❌ No
Radix Sort	    𝑂(𝑛𝑘)	     𝑂(𝑛𝑘)	         𝑂(𝑛𝑘)	      𝑂(𝑛+𝑘)	              ✅ Yes	    ❌ No       ❌ No	       ❌ No
Bucket Sort	    𝑂(𝑛+𝑘)	     𝑂(𝑛+𝑘)	         𝑂(𝑛²)	     𝑂(𝑛+𝑘)	             ✅ Yes	   ❌ No       ❌ No	      ❌ No

*/

#include <iostream>
using namespace std;

/*
--> Selection Sort :  Find the minimum element in the array and swap it with the first element. Repeat for n-1 passes.
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

--> Bubble Sort : Push the maximum element to the last by adjacent swaps in each pass... n-1 passes reuired
For n elements n-1 passes are required
Pass 1 : starting from index 0 compare adjacent elements and swap if arr[j] > arr[j+1] ... keep comparing and swapping till arr[n-2] & arr[n-1]
Pass 2 : starting from index 0 compare adjacent elements and swap if arr[j] > arr[j+1] ... keep comparing and swapping till arr[n-3] & arr[n-2]
Pass 3 : starting from index 0 compare adjacent elements and swap if arr[j] > arr[j+1] ... keep comparing and swapping till arr[n-4] & arr[n-3]
....
Pass n-1 : compare arr[0] & arr[1] and swap if arr[0] > arr[1] ... keep comparing and swapping till arr[0] & arr[1]

--> Insertion Sort : Insert the current element at its correct position in the already sorted part of the array.
*/

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void selection_sort(int arr[], int n){
    // n is passed as paramter bcz arr decays to pointer when passed to fn and thus n can't be caluclated using sizeof(arr)/sizeof(arr[0])
    for(int i=0; i<n-1; i++) {
        int min = i;
        for(int j=i; j<n; j++) {
            if(arr[j]<arr[min]) min = j;
        }
        
        swap(arr[i], arr[min]);             // swap arr[i] & arr[min]
    }
}

void bubble_sort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        int didSwap = 0;
        // cout << endl << "Pass " << i+1 << " : ";
        for(int j=0; j<n-i-1; j++){
            // cout << arr[j] << " - " << arr[j+1] << " ";
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                didSwap = 1;
            }
        }
        if(didSwap == 0) break;         // if no swap done in a pass that means array is sorted so break
        // cout << endl << "Sorted array after Pass " << i+1 << " : ";
        // for(int x=0; x<n; x++) cout << arr[x] << " ";
    }
}

void insertion_sort(int arr[], int n){
    for(int i=1; i<n; i++){
        int j = i;
        // insert the ith element to its correct position in sorted half.
        // By repeatedly right-pushing the bigger elements and inserting the ith element in the empty space
        while(j>0 && arr[j-1] > arr[j]){
            swap(arr[j-1], arr[j]);
            j--;
        }
    }
}

int main(){
    int arr[] = {23,12,1,34,56,45,89,78,67};
    int arr2[] = {1,2,3,4,5,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int x : arr) cout << x << " ";
    bubble_sort(arr, n);
    cout << endl;
    for(int x : arr) cout << x << " ";
}