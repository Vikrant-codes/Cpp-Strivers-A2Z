#include <iostream>
#include <vector>
using namespace std;

int getMaximum(vector<int>& arr) {
    int n = arr.size();
    int mx = arr[0];
    // we can also initialize mx as INT_MIN

    for (int i = 0; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];

    return mx;
}

int getSecondMaximum(vector<int>& arr) {
    int n = arr.size();
    int mx = arr[0];
    int secondMax = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > mx) {
            secondMax = mx;
            mx = arr[i];
        }
        else if (arr[i] > secondMax) {
            secondMax = arr[i];
        }
    }

    return secondMax;
}

int getMinimum(vector<int>& arr) {
    int n = arr.size();
    int mn = arr[0];
    // we can also initialize mn as INT_MAX      

    for (int i = 0; i < n; i++)
        if (arr[i] < mn)
            mn = arr[i];

    return mn;
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

    return 0;
}