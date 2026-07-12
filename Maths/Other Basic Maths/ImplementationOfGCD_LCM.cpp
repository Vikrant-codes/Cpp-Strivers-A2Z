// Implementation of the pre-defined GCD & LCM methods

/*
GCD (HCF) & LCM pre-defined methods in C++

- The pre-defined methods to get hcf & lcm of two numbers are available in the 'numeric' header (#include <numeric>)
- Available from C++17 onwards.
- Works for integral types (int, long long, etc.).
- Usage :
    #include <numeric>
    
    int g = std::gcd(48, 18);  // 6
    int l = std::lcm(48, 18);  // 144

- The C++ standard does not specify the exact implementation of std::gcd() and std::lcm(), only their behavior. 
  However, most standard library implementations use something very close to the Euclidean algorithm.
*/ 

#include <bits/stdc++.h>
using namespace std;

int gcd1(int a, int b) {
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

int gcd2(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// to get lcm, we use the identity : lcm(a,b) = ∣a × b∣ / gcd(a,b)
int lcm(int a, int b) {
    if (a == 0 || b == 0)
        return 0;
    
    return abs(a / gcd(a, b) * b);
    // we are doing 'a / gcd(a, b) * b' instead of '(a * b) / gcd(a,b)' to reduce the chance of int overflow during calculation
}

int main() {
    return 0;
}