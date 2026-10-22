#include <bits/stdc++.h>
using namespace std;

void flipFlag(bool& flag) {
    flag = !flag;
}

// Using ternary operator
void flipBit1(int& bit) {
    bit = (bit == 1) ? 0 : 1;
}

// Using Arithmetics
void flipBit2(int& bit) {
    bit = 1 - bit;
}

// Using XOR
void flipBit3(int& bit) {
    bit = bit ^ 1;
}

// Array / Lookup Indexing: Cycling through a tiny array using the bit itself as the index.
void flipBit4(int& bit) {
    int arr[] = {1, 0};

    bit = arr[bit];
}

int main() {
    return 0;
}