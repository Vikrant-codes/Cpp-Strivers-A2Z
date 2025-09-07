#include <iostream>
#include <vector>
using namespace std;

int Largest(vector<int> arr) {
    int i = 0;
    int j = arr.size() - 1;
    int l = arr[0];         // initialize largest with first array element
    // Use two pointer approach to check whether arr[i] or arr[j] is greater than current maximum .. Incerement i and decrement j afterwards
    while(i <= j){
        // if either arr[i] or arr[j] is greater than the largest element
        if(arr[i] > l || arr[j] > l){
            // largest = arr[i] if arr[i] >= arr[j] else arr[j]
            l = arr[i] >= arr[j] ? arr[i] : arr[j];
        }
        i++;
        j--;
    }
    return l;
}

int secondLargest(vector<int> arr) {
    int n = arr.size();
    int l = arr[0];
    int sl = -1;
    for(int i = 1; i < n; i++){
        if (arr[i] > l){
            sl = l;
            l = arr[i];
        }
        else if (arr[i] > sl && arr[i] != l) sl = arr[i];
    }
    return sl;
}

int secondSmallest(vector<int> arr) {
    int n = arr.size();
    int mn = arr[0];
    int smn = INT_MAX;
    for(int i=0; i<n; i++){
        if(arr[i] < mn){
            smn = mn;
            mn = arr[i];
        }
        else if(arr[i] < smn && arr[i] != mn) smn = arr[i];
    }
    return smn;
}

int main() {
    vector<int> arr = {17,23,54,46,38,72,63,89,91,100,23,13,99,120,37,48,54,61,93};
    int mxm = Largest(arr);
    int second_mxm = secondLargest(arr);
    int second_mnm = secondSmallest(arr);

    cout << "Largest : " << mxm << "\t Second Largest : " << second_mxm;
    cout << "\t Second Smallest : " << second_mnm;
    return 0;
}