#include <bits/stdc++.h>
using namespace std;

/*
Bitwise operations are much faster compared to other operations like +, -, *, /, % etc.
So, in Competitive Programming, bitwise operations are preferred over using arithmetic operators whereever possible.

This code contains commonly used bitwise tricks.
*/

// Checking if a number is odd/even
bool isOdd(int x) {
    return x & 1;
}

// Checking if a number is power of two
bool isPowerOfTwo(int x) {
    // if (x == 0) return false;
    // return x & x - 1 == 0;

    return x && !(x & (x-1));
}

// Playing with the k-th bit

bool isKthBitSet(int x, int k) {
    return x & (1 << k);
}

int setTheKthBit(int x, int k) {
    return x | (1 << k);
}

int toggleTheKthBit(int x, int k) {
    return x ^ (1 << k);
}

int unsetTheKthBit(int x, int k) {
    return x & ~(1 << k);
}

// Multiply / divide a number by powers of 2, i.e. multiply/divide the number with 2^k

int mul(int x, int k) {
    return x << k;      // same as doing x * 2^k
}

int divide(int x, int k) {
    return x >> k;      // same as doing x / 2^k
}

// Modulu of x and 2^k, i.e. x % 2^k

int modulu(int x, int k) {
    return x & ((1 << k) - 1);

    // Why this works?
    /*
    We know that dividing any number with some power of two (2^k) is same as right-shifting the bits of number by k
    
    Ex- 19 / 4 = 19 / (2^2)
    19 = 10011
    if we right shift 19 by 2 bits, we get: 19 >> 2 = 4
    because 10011 is right-shifted and become 100 | 11... this 11 part is discarded.
    This 11 is actually the remainder.

    So, if we needed 19 % 4, we actually need the bits which would be right shifted
    i.e., during x % 2^k, we need the last k bits of x.

    during 19 % 4, 4 = 2^2, so we need the last 2 bits of 19, 19 is 10011, last 2 bits = 11 = 3 (in decimal),
    so 19 % 4 = 3.
    
    How does `x & ((1 << k) - 1)` gives us the last k bits ?

    1 << k gives us a bitmask number having only a set bit at the k-th place.
    something like 00000...001000 etc.
    This `1 << k` would have a `1` bit only at the k-th place (considering 0-based indexing from right end)

    Now, `(1 << k) - 1` would give us a number having only the last k-bits set to 1, i.e., 0000..00111...1
    Thus, doing `&` with this `(1 << k) - 1`, we can get the last k-bits of our number x.
    These last k bits represent the remainder when divided by 2^k. 
    */
}

// Swapping two numbers

void swap(int& x, int& y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

// Useful Property 
/*
Suppose, countOfSetBits(A) = x
         countOfSetBits(B) = y
and,     countOfSetBits(A ^ B) = z

then, if (x + y) is even, then z will also be even.
      if (x + y) is odd, then z will also be odd.
*/

// Useful Toggle Trick
/*
Suppose we have some variable x and we want to toggle its value between A & B, i.e., 
if it's value is A, we set it to B and vice-versa
```
if (x == A)
    x = B
else if (x == B)
    x = A
```

This can be done in a single line using XOR: 
```
x = A ^ B ^ x
```
*/

void toggle(int x) {
    x = 1 ^ -1 ^ x;         // toggle the value of x between 1 & -1
}

// Addition Properties
/*
A + B = (A ^ B) + 2.(A & B)
A + B = (A | B) + (A & B)
*/

int main() {
    return 0;
}