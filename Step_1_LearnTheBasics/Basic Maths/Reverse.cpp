/*
Leetcode -- Reverse Integer -- Difficulty : Medium

Given a signed 32-bit integer x, return x with its digits reversed. 
If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
*/

#include<bits/stdc++.h>
#include<climits>  // Include this for INT_MAX and INT_MIN
using namespace std;

int reverse(int x) {
    /*
    // My approach
    int rev = 0;
    int pve = x>=0 ? 1 : 0;
    int lim = -2147483648;
    if(!pve){
        if(x == lim) return 0;
        x = -x;
    }
    while(x!=0) {
        int d = x%10;
        if(rev > 214748364 || (rev==214748364 && d >= 7)) return 0;
        else rev = rev*10 + d;
        x = x/10;
    }
    return pve ? rev : -rev;
    */
    int rev = 0;
    while (x != 0) {
        int d = x % 10;
        // Check for overflow/underflow before updating rev
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && d > 7)) return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && d < -8)) return 0;

        rev = rev * 10 + d;
        x /= 10;
    }
    return rev;
}

int main() {
    int n = 1534236461;
    int n2 = -54;
    cout << reverse(n2);
    return 0;
}