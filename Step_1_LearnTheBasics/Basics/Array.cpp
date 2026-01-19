#include<iostream>
using namespace std;

int main() {
    int arr[7];
    // sizeof operator : determine the size in bytes of a: variable, data type, class, objects, etc.
    // sizeof(arr) -> Total size of array in bytes, sizeof(arr[0]) -> Size of single element in bytes 
    int arr_size = sizeof(arr);
    int arr_ele_size = sizeof(int);         // since elements are of 'int' datatype
    // Length = Total size / Size of single element
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Enter 7 elements : ";
    for(int i=0; i<7; i++) {
        cin >> arr[i];
    }
    for(int i=0; i<7; i++) {
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }
    cout << "Squaring Each element" << '\n';
    for(int i=0; i<7; i++) {
        arr[i] *= arr[i];
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    // 2 D Array
    int twodarr[3][5];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 5; j++) {
            twodarr[i][j] = i * 10 + j;
            cout << "2D Array[" << i << "][" << j << "] = " << twodarr[i][j] << '\t';
        }
        cout << '\n';
    }

    // arr having default value as 9
    int exm[10] = {9};          // 9 is assigned to arr[0] only rest others are 0
    for(int x : exm) cout << x << ' '; 
    fill(exm, exm+10, 9); // Fill all elements with 9
    cout << '\n';
    for(int x : exm) cout << x << ' ';

    return 0;
}