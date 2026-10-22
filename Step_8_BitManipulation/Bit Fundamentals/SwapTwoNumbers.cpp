#include<bits/stdc++.h>
using namespace std;

// Method - 1: Using a third variable
void swapTemp(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}

// Method - 2: Using Arithmetic operations
// Limitations : Be careful with overflow in some languages with fixed integer sizes.
void swapMath(int &a, int &b) {
    a = a + b;
    b = a - b;      // b = a - b = (a + b) - b = a
    a = a - b;      // a = a - b = (a + b) - (a) = b
}

// Method - 3: Using XOR
void swapXOR(int &a, int &b) {
    a = a ^ b;    // a = a ^ b
    b = a ^ b;    // b = a ^ b = (a ^ b) ^ b = a ^ (b ^ b) = a ^ 0 = a 
    a = a ^ b;    // a = a ^ b = (a ^ b) ^ (a) = a ^ (b ^ a) = a ^ (a ^ b) = (a ^ a) ^ b = 0 ^ b = b
}

int main() {
    return 0;
}