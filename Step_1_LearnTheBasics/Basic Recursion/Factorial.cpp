// Factorial of a given number n using recursion

#include <iostream>
using namespace std;

// Time Complexity : O(n) __ Space Complexity : O(n)
/*
>> Time Complexity: O(n)
To get fact(n), there are n recursive calls, and each call does constant work apart from the recursive call.
So, O(n) * O(1) = O(n)

>> Space Complexity: O(n)
Because recursion uses the call stack, all calls remain on the stack until fact(0) returns:
---
fact(n)
fact(n-1)
fact(n-2)
...
fact(1)
fact(0)
---
There are about n stack frames.
*/

// Using Parameterized Recursion

void fact(int n, int ans) {
    if (n == 0) {
        cout << "Factorial is: " << ans << endl;
        return; 
    }

    fact(n - 1, ans * n);
}

// parameterized recursion but returns answer instead of printing it
int factX(int n, int ans) {
    if (n == 0) 
        return ans;

    return factX(n - 1, ans * n);
}

// Using Functional Recursion

int fact(int n) {
    if (n == 0)
        return 1;

    return n * fact(n - 1);
}

int main() {
    int n = 5;

    fact(n, 1);

    cout << "Factorial is: " << factX(n, 1) << endl;
    cout << "Factorial is: " << fact(n) << endl;

    return 0;
}