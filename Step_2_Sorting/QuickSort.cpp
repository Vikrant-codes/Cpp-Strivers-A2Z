#include <iostream>
#include <vector>
#include <utility> // for std::swap
using namespace std;

int partitionLastPivot(vector<int> & arr, int low, int high) {
    int pivot = arr[high];
        int i = low;
        for(int j = low; j < high; j++){
            if (arr[j] <= pivot){
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[high], arr[i]);
        return i;
}

int partitionFirstPivot(vector<int> & arr, int low, int high) {
    int pivot = arr[low];  // Choosing first element as pivot
    int i = low + 1;       // i starts from the next element
    int j = high;          // j starts from the last element

    while (i <= j) {
        while (i <= high && arr[i] <= pivot) i++;  // Move right if element is smaller/equal to pivot (since we stop at larger element)
        while (j >= low && arr[j] > pivot) j--;    // Move left if element is greater than pivot (since we stop at smaller element)

        if (i < j) swap(arr[i], arr[j]);  // Swap if i and j haven't crossed
    }

    swap(arr[low], arr[j]);  // Place pivot at its correct position
    return j;  // Return pivot index
}

void quickSort(vector<int> & arr, int low, int high) {
    if (low < high) {
        int partIndex = partitionLastPivot(arr, low, high);
        quickSort(arr, low, partIndex - 1);
        quickSort(arr, partIndex + 1, high);
    }
}

int main() {
    vector<int> v = {4,5,3,1,2,6,8,7,9,0};
    int s = v.size();
    quickSort(v, 0, s-1);
    for(int x : v) cout << x << " ";

    return 0;
}