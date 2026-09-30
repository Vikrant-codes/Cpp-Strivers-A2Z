/*
GFG - Good Numbers : Easy

A number is called a good number if every digit is strictly greater than the sum of all digits to its right.

Given two positive integers l and r defining a range, and a digit d, 
find all good numbers in the range [l, r] that do not contain the digit d.

Examples :-

Input: l = 200, r = 700, d = 4
Output: [210, 310, 320, 510, 520, 521, 530, 531, 610, 620, 621, 630, 631, 632, 650]
Explanation: These are all the good numbers in [200, 700] that do not contain the digit 4.

Input: l = 100, r = 500, d = 5
Output: [210, 310, 320, 410, 420, 421, 430]
Explanation: These are all the good numbers in [100, 500] that do not contain the digit 5.

Constraints :-
• 0 ≤ l ≤ 10^6
• 1 ≤ r ≤ 10^6
• 0 ≤ d ≤ 9
*/

#include <bits/stdc++.h>
using namespace std;

bool isGoodNumber(int n) {
    // we don't consider the rightmost digit for the sum comparison,
    // since it don't have any digits to its right
    
    int dig = n % 10;
    n /= 10;
    
    int sumDigits = dig;    // sum is initialized as the rightmost digit value
    
    while (n) {
        dig = n % 10;
        
        if (dig <= sumDigits)
            return false;
            
        sumDigits += dig;
        
        n /= 10;
    }
    
    return true;
}

bool notHaveDigitD(int n, int d) {
    // when n = 0 and d = 0, the while loop won't run, so we need to explicitly handle this case

    // if (n == 0 && d == 0) return false; 
    if (n == d) return false;
    // this `n == d` condition also handles this case, along with cases when n contains of single digit equal to d itself.
    
    while (n) {
        if (n % 10 == d) 
            return false;
        n /= 10;
    }
    
    return true;
}

// Combined function to check both -- good number and not containing digit d
bool isGoodNumberAndNotContainD(int n, int d) {
    // we don't consider the rightmost digit for the sum comparison,
    // since it don't have any digits to its right
    
    int dig = n % 10;
    n /= 10;
    
    if (dig == d) return false;
    
    int sumDigits = dig;    // sum is initialized as the rightmost digit value
    while (n) {
        dig = n % 10;
        
        if (dig == d || dig <= sumDigits)
            return false;
            
        sumDigits += dig;
        
        n /= 10;
    }
    
    return true;
}

vector<int> goodNumbers(int l, int r, int d) {
    vector<int> res;
    
    for (int i = l; i <= r; i++) {
        // if (isGoodNumber(i) && notHaveDigitD(i, d))
        //     res.push_back(i);
    
        if (isGoodNumberAndNotContainD(i, d))
            res.push_back(i);
    }
            
    return res;
}

int main() {
    return 0;
}