#include <iostream>
#include <vector>
using namespace std;

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
    if(low >= high) return;         // Base condition
    int mid = low + (high - low)/2;

    mergeSort(arr, low, mid);       // For left half
    mergeSort(arr, mid+1, high);    // For right half
    merge(arr, low, mid, high);     // Merge the two halves
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int n = arr.size();
    mergeSort(arr, 0, n-1);
    for(auto x: arr) cout << x << " ";

    return 0;
}