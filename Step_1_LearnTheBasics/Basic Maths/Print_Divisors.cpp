// GFG - All divisors of a Number : Easy

#include <iostream>
#include <vector>
using namespace std;

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
// Check for all numbers from 1 to n and print the number if it divides n completely.
void printDivisors(int n) {
    for (int i = 1; i <= n; i++)
        if (n % i == 0)
            cout << i << " ";
}




/*
GFG - All divisors of a Number : Easy

Given an integer n, return all the divisors of n in the ascending order.
 
Examples :-

Input : n = 20 __ Output: 1 2 4 5 10 20
Explanation: 20 is completely divisible by 1, 2, 4, 5, 10 and 20.

Input: n = 21191 __ Output: 1 21191
Explanation: As 21191 is a prime number, it has only 2 factors(1 and the number itself).

Constraints:- 1 ≤ n ≤ 10^9
*/

vector<int> getDivisors(int n) {
    vector<int> v;
    int pos = 0;
    for(int i=1; i*i <= n; i++) {
        if (n % i == 0) {
            v.insert(v.begin()+pos, i);
            pos++;
            if (n/i != i) {
                v.insert(v.begin()+pos, n/i);
            }
        }
    }
    return v;
}

int main() {
    
    return 0;
}