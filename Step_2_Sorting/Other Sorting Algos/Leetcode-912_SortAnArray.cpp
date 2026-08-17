/*
Leetcode - 912. Sort an Array : Medium

Given an array of integers nums, sort the array in ascending order and return it.
You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and 
with the smallest space complexity possible.

Examples :-

Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), 
while the positions of other numbers are changed (for example, 1 and 5).

Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessarily unique.

Constraints :-
• 1 <= nums.length <= 5 * 10^4
• -5 * 10^4 <= nums[i] <= 5 * 10^4
*/

#include <bits/stdc++.h>
using namespace std;

// 1️⃣ Using QuickSort with Median of Three Pivot & Hoare's Partitioning

// First Element as Pivot was restriction-checked, and implementing it gave "Restrictions Failed" on submission

// helper method -- return the median of three values
int getMedian(int a, int b, int c) {
    // depending on the sorted order of a, b and c, median value could be different

    // if sorted order is {a, b, c} / {c, b, a} -> median b
    if ( (b >= a && b <= c) || (b >= c && b <= a) ) 
        return b;
    // else - if sorted order is {b, c, a} / {a, c, b} -> median c
    else if ( (c >= b && c <= a) || (c >= a && c <= b) ) 
        return c;
    
    // if neither b nor c are the median, then a must be the median 
    return a;
}

// Hoare's Partition with "Median of three" as pivot
int partition(vector<int>& arr, int low, int high) {
    // Median of three - pivot
    int mid = (low + high) / 2;
    int pivot = getMedian(arr[low], arr[mid], arr[high]);

    int i = low, j = high;

    while (true) {
        while (i <= high && arr[i] < pivot) i++;
        while (j >= low && arr[j] > pivot) j--;
        if (i >= j)
            return j;
        
        swap(arr[i], arr[j]);
        i++; j--;
    }
}

// QuickSort implementation of hoare's partitioning
void quickSort(vector<int>& arr, int low, int high) {
    // Base case: if a single element is remaining or no element at all, return
    if (low >= high) 
        return;

    int p = partition(arr, low, high);      // returns the partition boundary (Hoare's partition)
    quickSort(arr, low, p);                 // recursively sort the left half
    quickSort(arr, p+1, high);              // recursively sort the right half
}

vector<int> sortArray(vector<int>& nums) {
    quickSort(nums, 0, nums.size()-1);

    return nums;
}


// 2️⃣ Using 3-Way QuickSort / Dutch National Flag Sort with Median of Three

// 3-Way Partition with "Median of three" as pivot
void partition3Way(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int mid = (low + high) / 2;
    int pivot = getMedian(arr[low], arr[mid], arr[high]);       // Median of 3 - pivot

    lt = low;           // lt points at < pivot element position (lt -> less than)
    int i = low;        // i for traversal
    gt = high;          // gt points at > pivot element position (gt -> greater than)
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        }
        else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        }
        else {
            i++;
        }
    }
}

// 3-Way QuickSort
void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high) 
        return;

    int lt, gt;
    partition3Way(arr, low, high, lt, gt);
    
    quickSort3Way(arr, low, lt-1);
    quickSort3Way(arr, gt+1, high);
}

vector<int> sortArray2(vector<int>& nums) {
    quickSort3Way(nums, 0, nums.size() - 1);
    
    return nums;
}


// 3️⃣ Using Merge Sort

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int i = low, j = mid+1;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= high) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int i = low; i <= high; i++)
        arr[i] = temp[i-low];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) 
        return;

    int mid = (low + high) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);

    merge(arr, low, mid, high);
}

vector<int> sortArray3(vector<int>& nums) {
    mergeSort(nums, 0, nums.size()-1);

    return nums;
}

int main() {
    return 0;
}