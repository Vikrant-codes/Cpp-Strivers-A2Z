#include <bits/stdc++.h>
using namespace std;

// Naive Approaches: Time Complexity : O(log₂ n) __ Space Complexity : O(log₂ n)

string convert2Binary(int n) {
    string res = "";

    while (n != 0) {
        if (n & 1) res += '1';  // similar to condition, if (n % 2 == 1)  
        else res += '0';

        n = n >> 1;             // similar to n = n / 2;
    }

    reverse(res.begin(), res.end());

    return res;
}

int convert2Decimal(string& binary) {
    int n = binary.size();

    int num = 0;
    int multiplier = 1;         // initial multiplier is 2^0, which is 1.

    for (int i = n - 1; i >= 0; i--) {
        if (binary[i] == '1')
            num = num + multiplier;
        
        multiplier *= 2;
    }

    return num;
}

// Set the i-th bit: Get the binary string representation, set the i-th bit, convert the binary string back to decimal
int setBitNaive(int n, int i) {
    string binary = convert2Binary(n);
    int len = binary.size();

    binary[len - 1 - i] = '1';

    return convert2Decimal(binary);
}

// Clear the i-th bit: Get the binary string representation, clear the i-th bit, convert the binary string back to decimal
int clearBitNaive(int n, int i) {
    string binary = convert2Binary(n);
    int len = binary.size();

    binary[len - 1 - i] = '0';

    return convert2Decimal(binary);
} 

// Toggle the i-th bit: Get the binary string representation, toggle the i-th bit, convert the binary string back to decimal
int toggleBitNaive(int n, int i) {
    string binary = convert2Binary(n);
    int len = binary.size();

    binary[len - 1 - i] = '1' - binary[len - 1 - i];        // flip / toggle the bit

    return convert2Decimal(binary);
}

// Optimal Approaches (Using Bit tricks / Bitmasking): Time Complexity : O(1) __ Space Complexity : O(1)

// Set the i-th bit
/*
• 1 << i creates a bitmask with only the i-th bit set to 1.
• n | mask uses bitwise OR to set that bit to 1, leaving all other bits unchanged.
*/
int setBit(int n, int i) {
    return n | (1 << i);
}

// Clear the i-th bit
/*
• 1 << i creates a mask with the i-th bit set to 1.
• ~ inverts the mask, making the i-th bit 0 and all other bits 1.
• n & mask uses bitwise AND to clear that bit while preserving all other bits.
*/
int clearBit(int n, int i) {
    return n & ~(1 << i);
}

// Toggle the i-th bit
/*
• 1 << i creates a mask with only the \(i\)-th bit set to 1.
• n ^ mask uses bitwise XOR to flip that bit: 0 becomes 1, and 1 becomes 0. All other bits remain unchanged.
*/
int toggleBit(int n, int i) {
    return n ^ (1 << i);
}

int main() {
    return 0;
}