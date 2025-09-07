#include <iostream>
#include <vector>
using namespace std;

// Brute Force Approach : Time Complexity : O(n) + O(nz) + O(n-nz) = O(2n) __ Space Complexity : O(n)
void moveZerosBrute(vector<int>& a) {
    vector<int> temp;           //temporary array:
    int n = a.size();          //size of original array.
    //copy non-zero elements from original -> temp array:
    for (int i = 0; i < n; i++) if (a[i] != 0) temp.push_back(a[i]);

    int nz = temp.size();       // number of non-zero elements.

    //copy elements from temp and fill first nz fields of original array:
    for (int i = 0; i < nz; i++) a[i] = temp[i];

    //fill rest of the cells with 0:
    for (int i = nz; i < n; i++) a[i] = 0;
}

// Optimal Approach : Time Complexity : O(x) + O(n-x) = O(n) __ Space Complexity : O(1)
void moveZerosOptimal1(vector<int>& a){
    int n = a.size(); //size of original array.
    int j = -1; //place the pointer j:
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            j = i;
            break;
        }
    }

    //If array doesn't contain any zero then j will remain -1 ... so no need to do any change in the array
    if (j == -1) return;

    //Move the pointers i and j and swap accordingly __ j always points to the first zero and i points to the first non-zero element after j
    for (int i = j + 1; i < n; i++) {
        if (a[i] != 0) {
            swap(a[i], a[j]);
            j++;
        }
    }
}

// Optimal Approach 2 : Time Complexity : O(n) __ Space Complexity : O(1)
// This approach is similar to the first one but uses a single loop and a single pointer to track the position of the last non-zero element.
// we know that final array will have all non-zero elements at the beginning and all zero elements at the end.
// we consider i = 0 as the position of the first non-zero element in the final array.
// we iterate through the array and whenever we find a non-zero element, we swap it with the element at index i and increment i by 1.
// we do so because we know that the first non-zero element will appear at index 0, the second non-zero element will appear at index 1 and so on.
// so we can swap the non-zero element with the element at index i and increment i by 1. 
// __ This way we can move all non-zero elements to the beginning of the array and all zero elements to the end of the array.
void moveZerosOptimal2(vector<int>& arr){
    int i = 0;
    int n = arr.size();
    for(int j=0; j<n; j++){
        if(arr[j] != 0){
            swap(arr[i], arr[j]);
            i++;
        }
    }
}

int main() {
    vector<int> arr = {0,1,2,0,3,0,0,4,0,5,0,6};
    moveZerosOptimal1(arr);
    for(int x : arr) cout << x << " ";
    return 0;
}