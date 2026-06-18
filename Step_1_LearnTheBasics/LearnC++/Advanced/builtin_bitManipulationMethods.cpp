#include <bits/stdc++.h>
using namespace std;

/*
🔹 1. __builtin_popcount(x), __builtin_popcountl(x), __builtin_popcountll(x) → Counting set bits (1s)
• These methods counts number of set bits (1s)

>> Variants :-
• __builtin_popcount(x) → for unsigned int
• __builtin_popcountl(x) → for unsigned long
• __builtin_popcountll(x) → for unsigned long long

Ex - __builtin_popcount(13)  // 1101 → 3

🔹 2. __builtin_clz(x) → Count Leading zeros
• Counts leading zeros, i.e., zeros before first 1 from left
• Undefined if x == 0
Ex- __builtin_clz(8)         // 8 = 000...0001000 → 28 leading zeros

👉 Useful trick: int bits = 32 - __builtin_clz(x);  // number of bits in x
Ex- assume num = 13... binary = 1101 ... but, numbers are stored in 32 bits so 13 is actually represented in memory as -
13 = 00000000 00000000 00000000 00001101
__builtin_clz(num) -> this gives us no. of leading zeros, for 13 it will give us :- 28
Now, total bits = 32, so we do 32 - __builtin_clz(num) to get the count of bits required to represent x.
for num = 13, 32 - __builtin_clz(13) = 32 - 28 = 4

>> Variants :- __builtin_clzl, __builtin_clzll

🔹 3. __builtin_ctz(x) → Count Trailing zeros
• Counts trailing zeros, i.e., zeros after last 1 from right
• Undefined if x == 0
Ex- __builtin_ctz(8)     // 1000 → 3 trailing zeros

>> Variants :- __builtin_ctzl, __builtin_ctzll

🔹 4. __builtin_parity(x) → Parity (odd/even set bits)
Returns:
- 1 → odd number of set bits
- 0 → even number of set bits

Ex- __builtin_parity(7)  // 111 → 3 bits → 1

🔹 5. __builtin_ffs(x) → Finds First set bit from right
• Returns 1-based index of first set bit from right
• Returns 0 if x == 0
Ex- __builtin_ffs(10)  // 1010 → first 1 at pos 2 → returns 2

⚠️ Important edge cases
__builtin_clz(0) → undefined behavior
__builtin_ctz(0) → undefined behavior 
Might work on some compilers (return 32), but crash on some other compilers (that is why it is considered undefined behavior)

🔥 Clean mental map
• popcount → how many 1s
• clz → how many leading zeros, i.e., 0s before first 1
• ctz → how many trailing zeros, i.e., 0s after last 1
• ffs → 1-based index of first 1 from right
• parity → odd/even count of 1s -> if odd return 1, else return 0
*/

int main() {
    int num = 10;       // binary = 1010
    cout << __builtin_popcount(num) << '\n';   // count of set bits in num ... 10 = binary (1010) = 2 set bits
    cout << __builtin_clz(num) << '\n';        // count of leading 0s ... 10 = binary (0000.....1010) = 28 leading zeros
    cout << __builtin_ctz(num) << '\n';        // count of trailing 0s ... 10 = binary (0000.....1010) = 1 trailing zero
    
    cout << __builtin_parity(num) << '\n';     // returns 1 (if odd no. of set bits), else 0 ... 
    // for 10, binary = 1010 -> 2 set bits -> returns 0

    cout << __builtin_ffs(num) << '\n';        // find position of first set bit from right (1-based index)
    // for 10, binary = 1010 -> 1st set bit (1 bit) from right is at position 2
    
    return 0;
}