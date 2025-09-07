#include <iostream>
using namespace std;

/*
<-- Pass-by-Value (Copy is passed) -->
> Behavior: The function receives a copy of the argument.
> Effect: Changes inside the function do not affect the original variable.

<-- Pass-by-Reference (Original is passed) -->
> Behavior: The function receives a reference to the argument.
> Effect: Changes inside the function do affect the original variable.
*/
void passByValue(int x) {
    x = x + 10; // Modify the copy
    cout << "Inside passByValue: " << x << endl;
}

void passByReference(int &x) {
    x = x + 10; // Modify the original
    cout << "Inside passByReference: " << x << endl;
}
void displayArray(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void modifyArray(int arr[], int len) {
    for(int i=0; i<len; i++) {
        arr[i] *= 2;
    }
    cout << "Inside modifyArray : ";
    displayArray(arr, len);
}

int main() {
    int a = 5;
    passByValue(a);
    cout << "After passByValue: " << a << endl; // Original remains unchanged
    passByReference(a);
    cout << "After passByReference: " << a << endl; // Original value is changed

    int arr[5] = {1,2,3,4,5};
    cout << "Before Modifying : ";
    displayArray(arr, 5);
    modifyArray(arr, 5);
    cout << "After modifyArray : ";
    displayArray(arr, 5);
    return 0;
}
