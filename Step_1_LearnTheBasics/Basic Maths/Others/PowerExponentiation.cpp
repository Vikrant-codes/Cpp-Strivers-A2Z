// Implement the pow method (pow(x, n))
/*
pow(x, n) :- It is a pre-defined method which returns x ^ n. 
Its return type is double and can work with double x & n.
*/

#include<bits/stdc++.h>
using namespace std;

// For the ease of understanding, let's first try to implement/code the pow function for positive integers x & n.

// Naive Approach :- Time Complexity : O(n) __ Space Complexity : O(1)
/*
| x raised to the power n => x ^ n = x * x * x ... n times
So, run a loop n times and multiply for x each iteration to get x ^ n.
Initially keep ans = 1, and for each iteration do ans = ans * x. 
The loop will run n times and when it ends ans will be storing x ^ n. 
*/
int myPow(int x, int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans *= x;
    return ans;
}

// Better Approach :- 


int main() {
    cout << myPow(2, 10);
    cout << myPow(5, 3);
    cout << myPow(3, 3);

    return 0;
}