#include <iostream>
#include <vector>
using namespace std;

void recBubbleSort(vector<int> & arr, int size){
    if(size == 1) return;
    for(int i=0; i<size-2; i++){
        if(arr[i] > arr[i+1]) swap(arr[i], arr[i+1]);
    }
    recBubbleSort(arr, size-1);
}

int main() {
    vector<int> arr = {5, 1, 4, 2, 8};
    int n = arr.size();
    recBubbleSort(arr, n);
    cout << "Sorted array: ";
    for(int x : arr) cout << x << " ";

    return 0;
}