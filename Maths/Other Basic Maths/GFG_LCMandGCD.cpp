/*
GFG - LCM And GCD : Basic

Given two integers a and b, You have to compute their LCM and GCD and return an array containing their LCM and GCD.

Examples :-

Input: a = 5 , b = 10 __ Output: [10, 5]
Explanation: LCM of 5 and 10 is 10, while their GCD is 5.

Input: a = 14 , b = 8 __ Output: [56, 2]
Explanation: LCM of 14 and 8 is 56, while their GCD is 2.

Input: a = 1 , b = 1 __ Output: [1, 1]
Explanation: LCM of 1 and 1 is 1, while their GCD is 1.

Constraints :- 
• 1 ≤ a, b ≤ 10^4
*/

#include <bits/stdc++.h>
using namespace std;

int getGCD(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b) a = a % b;
        else b = b % a;
    }
    
    return (a == 0) ? b : a;
}

vector<int> lcmAndGcd(int a, int b) {
    int gcd = getGCD(a, b);
    int lcm = (a / gcd * b);
    
    return {lcm, gcd};
}

int main() {
    return 0;
}