#include <iostream>
#include <vector>
using namespace std;

void recInsertionSort(vector<int> & arr, int n, int size) {
    if(n == size) return;
    int j = n;
    while (j > 0 && arr[j-1] > arr[j]){
        swap(arr[j], arr[j-1]);
        j--;
    }

    recInsertionSort(arr, n+1, size);
}

int main() {
    vector<int> arr = {5,3,1,2,4};
    int n = arr.size();
    recInsertionSort(arr, 1, n);
    cout << "Sorted array: ";
    for(int x : arr) cout << x << " ";

    return 0;
}