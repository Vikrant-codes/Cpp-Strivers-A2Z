#include <iostream>
#include <utility>
using namespace std;

// Method 1 -- using a third variable
void swapTemp(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}

// Method 2 -- using Addition and Subtraction __ Limitations : Be careful with overflow in some languages with fixed integer sizes.
void swapAddSub(int &a, int &b) {
    a = a+b;
    b = a-b;
    a = a-b;
}

// Method 3 -- using XOR 
void swapXOR(int &a, int &b) {
    a = a ^ b;    // a = a ^ b
    b = a ^ b;    // b = a ^ b = (a ^ b) ^ b = a ^ (b ^ b) = a ^ 0 = a 
    a = a ^ b;    // a = a ^ b = (a ^ b) ^ a = a ^ (b ^ a) = a ^ (a ^ b) = (a ^ a) ^ b = 0 ^ b = b
}

int main() {
    int a = 5;
    int b = 3;
    cout << "Swapping using a third variable" << endl;
    cout << "Before swapping : " << a << " " << b << endl;
    swapTemp(a,b);
    cout << "After swapping : " << a << " " << b << endl; 

    int x = 7;
    int y = 11;
    cout << "Swapping using Addition and Subtraction" << endl;
    cout << "Before swapping : " << x << " " << y << endl;
    swapAddSub(x,y);
    cout << "After swapping : " << x << " " << y << endl; 

    int p = 2;
    int q = 13;
    cout << "Swapping using XOR" << endl;
    cout << "Before swapping : " << p << " " << q << endl;
    swapXOR(p,q);
    cout << "After swapping : " << p << " " << q << endl; 

    return 0;
}