/* Recursion : When a function calls itself until a specified condition is met (Base Condition) */

#include <iostream>
using namespace std;

// Print 1 to N using Backtracking
void fn(int n) {
    if(n < 1) return;
    fn(n - 1);
    cout << n << " ";
}

// Print N to 1 using Backtracking
void fn2(int i, int n) {
    if(i > n) return;
    fn2(i+1, n);
    cout << i << " ";
}

int main() {
    int n;
    cout << "Enter n : ";
    cin >> n;
    fn(n);
    cout << endl;
    fn2(1, n);

    return 0;
}