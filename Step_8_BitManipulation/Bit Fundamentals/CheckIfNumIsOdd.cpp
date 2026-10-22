#include <bits/stdc++.h>
using namespace std;

/*
Every binary bit represents a power of 2: 2^0, 2^1, 2^2, ..., corresponding to 1, 2, 4, ...
The rightmost bit (LSB) represents 2^0 = 1.
- Odd numbers must have this bit set to 1, 
    because the sum of all higher powers of 2 is even, and adding 1 makes it odd.
- Even numbers must have this bit set to 0, 
    because they are formed entirely from higher powers of 2, all of which are even.

Therefore, n & 1 isolates the LSB: 1 means odd; 0 means even.
This works for positive integers, negative integers, and zero in C++.

To check odd, we can thus use condition like: 
    return (n & 1) == 1;

or, we can simply use: 
    return n & 1;    // the result of n & 1 (which is either 1 or 0), is converted to bool true / false

>> Important Operator Precedence Note:-
    return n & 1 == 1;    // Incorrect
    return (n & 1) == 1;  // Correct
`n & 1 == 1` is incorrect because in this expression, 1 == 1 is evaluated first since `==` has higher precedence than `&`.
*/

// Check odd 
bool isOdd(int n) {
    // return (n & 1) == 1;
    return n & 1;
}

// Check even
bool isEven(int n) {
    // return (n & 1) == 0;
    return !(n & 1);
}

int main() {
    return 0;
}