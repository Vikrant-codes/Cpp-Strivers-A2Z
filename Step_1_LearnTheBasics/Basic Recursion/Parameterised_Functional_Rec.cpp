#include <iostream>
using namespace std;

// Sum of first N numbers using recursion -- using Parameterised Recursion and Functional Recursion
// Parameterised Recursion
void sumNparm(int n, int sum){
    if(n < 1) {
        cout << sum << endl;
        return;
    }
    sumNparm(n-1, sum + n);
}

// Functional Recursion
int sm = 0;
int sumNfun(int n){
    if(n == 1) return 1;
    return n + sumNfun(n - 1);
}


// Factorial of a number
int fact(int n){
    if (n == 1) return 1;
    return n * fact(n - 1);
}

int main(){
    int x;
    cout << "Enter x : ";
    cin >> x;
    cout << "Sum of First " << x << " numbers using Parameterised Recursion : ";
    sumNparm(x, 0);
    cout << "Sum of First " << x << " numbers using Functional Recursion : " << sumNfun(x) << endl;
    cout << "Factorial of " << x << " : " << fact(x);
    return 0;
}