/*
GFG - Find nth root of m : Easy

You are given 2 numbers n and m, the task is to find n√m (nth root of m). If the root is not integer then returns -1.

Examples :-

Input: n = 2, m = 9 __ Output: 3
Explanation: 3^2 = 9

Input: n = 3, m = 9 __ Output: -1
Explanation: 3rd root of 9 is not integer.

Input: n = 1, m = 14 __ Output: 14

Constraints: __ 1 <= n <= 30 __ 1 <= m <= 10^9
*/

#include <bits/stdc++.h>
using namespace std;

//Optimal Approach: Binary Search on Answers : Time Complexity O(n * log m) __ Space Complexity O(1)
/*
The search space is from 1 to m. We select a mid and check the value of mid^n. If mid^n == m return mid, if mid^n < m then the nth root lies in the 
right half so we move our low pointer to mid + 1, if mid^n > m then the nth root lies in the left half so we move our high pointer to mid - 1.

Time Complexity : O(n * log m) -> log m is since we are using binary search and n is the number of multiplications done to calculate mid ^ n. 
Here, in the code the chkPower function used to compare the value of mid ^ n and m runs in O(n) and the binary search runs in O(log m), 
hence the overall time complexity is O(n * log m).
*/

// Function that checks if x ^ n == m .. Returns -1 if x^n < m ... 0 if x^n == m ... 1 if x^n > m 
int chkPower(int x, int n, int m) {
    long long val = 1;              // this will store the powers of x
    for(int i=1; i<=n; i++) {
        val *= x;
        if (val > m) return 1;      // if during loop val exceeds m then return 1
    }
    if (val == m) return 0;
    return -1;                      // if val < m return -1
}

int nthRoot(int n, int m) {
    if (n == 1) return m;
    int low = 1, high = m;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int x = chkPower(mid, n, m);
        if (x == 0) return mid;
        else if (x == 1) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

int main() {
    int n = 3;
    int m = 27;
    int nthRootValue = nthRoot(n, m);
    cout << nthRootValue << endl;

    return 0;
}