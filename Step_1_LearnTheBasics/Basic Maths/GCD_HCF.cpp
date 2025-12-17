/*
Implementation of GCD (Greatest Common Divisor) / HCF (Highest Common Factor) function 
*/

#include <iostream>
using namespace std;

int getHCF(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;

    // Make sure a, b are positive
    a = a > 0 ? a : -a;
    b = b > 0 ? b : -b;

    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

int getHCFSimplified(int a, int b) {
    // take positive value only
    a = abs(a); 
    b = abs(b); 

    if (a == 0) return b;
    if (b == 0) return a;

    while (b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

int main() {
    int gcd = getHCF(4, 6);
    cout << gcd;

    return 0;
}