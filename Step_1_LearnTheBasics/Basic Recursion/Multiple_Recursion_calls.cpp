#include <iostream>
using namespace std;

// Fibonacci using multiple recursion calls
// This function takes an input n and returns the nth fibonacci number
// fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
int fibonacci(int n){
    if(n <= 1) return 0;
    if(n == 2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    // 0 1 1 2 3 5 8 13 21 34 55
    cout << fibonacci(11);
    return 0;
}