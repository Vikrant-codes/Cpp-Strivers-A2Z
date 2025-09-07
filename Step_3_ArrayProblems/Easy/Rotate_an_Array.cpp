#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse
using namespace std;

void leftRotate1Place(vector<int>& arr){
    int temp = arr[0];
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        arr[i] = arr[i+1];
    }
    arr[n-1] = temp;
}
void rightRotate1place(vector<int>& arr){
    int n = arr.size();
    int temp = arr[n-1];
    for(int i=n-1; i>0; i--){
        arr[i] = arr[i-1];
    }
    arr[0] = temp;
}

// Left Rotate and Right Rotate by K places

// Brute Force Approach __ Time Complexity : O(k) + O(n-k) + O(k) = O(n+k) __ Space Complexity : O(k)
void leftBrute(vector<int>& arr, int k){
    vector<int> temp(k);
    int n = arr.size();
    k = k%n;
    // store first k elements to a temp array
    for(int i=0; i<k; i++){
        temp[i] = arr[i];
    }
    // shift array elements by k steps ... ith index gets value of (i+k)th index
    for(int i=0; i<n-k; i++){
        arr[i] = arr[i+k];
    }
    // put back temp elements in the last k slots of arr
    for(int i=n-k; i<n; i++){
        arr[i] = temp[i-n+k];
    }
}
void rightBrute(vector<int>& arr, int k){
    vector<int> temp(k);
    int n = arr.size();
    k = k%n;
    for(int i=0; i<k; i++){
        temp[i] = arr[n-k+i];
    }
    for(int i=n-1; i>=k; i--){
        arr[i] = arr[i-k];
    }
    for(int i=0; i<k; i++){
        arr[i] = temp[i];
    }
}

// Optimal Approach :- Reverse array from index [0:k-1] , Reverse from index [k:n-1] .... Finally Reverse the entire array
// Complexity Ananlysis __ Time Complexity : O(k) + O(n-k) + O(n) = O(2n) _ Space Complexity : O(1)
// Ex - {1,2,3,4,5,6,7}, k=3
// Step 1. Reverse from index [0:2] : Array becomes -> {3,2,1,4,5,6,7}
// Step 2. Reverse from index [3:6] : Array becomes -> {3,2,1,7,6,5,4}
// Step 3. Reverse the entire array : Array becomes -> {4,5,6,7,1,2,3}
void leftOptimal(vector<int>& arr, int k){
    int n = arr.size();
    k = k%n;
    vector<int>::iterator it = arr.begin();
    vector<int>::iterator end_it = arr.end();
    reverse(it, it+k);
    reverse(it+k, end_it);
    reverse(it, end_it);
}
void rightOptimal(vector<int>& arr, int k){
    int n = arr.size();
    k = k%n;
    vector<int>::iterator it = arr.begin();
    vector<int>::iterator end_it = arr.end();
    reverse(it, end_it-k);
    reverse(end_it-k, end_it);
    reverse(it, end_it);
}

int main() {
    vector<int> arr = {1,2,3,4,5,6,7};
    vector<int> arr2 = {1,2,3,4,5,6,7};
    vector<int> arr3 = {1,2,3,4,5,6,7};

    leftRotate1Place(arr);
    cout << "Left Rotated 1 place :- ";
    for(int x : arr) cout << x << " ";
    rightRotate1place(arr);
    cout << endl << "Right Rotated 1 place :- ";
    for(int x : arr) cout << x << " ";

    leftOptimal(arr2, 3);
    rightOptimal(arr3, 3);
    cout << endl << "Left Rotated Array :- ";
    for(int x : arr2) cout << x << " ";
    cout << endl << "Right Rotated Array :- ";
    for(int x : arr3) cout << x << " ";
}