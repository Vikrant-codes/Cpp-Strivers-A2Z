#include <iostream>
using namespace std;

void printHello(int n) {
    // Base Condition
    if (n == 0)
        return;

    cout << "Hello World !! \n";

    printHello(n-1);
}

// Infinite Recursion -- Base condition doesn't exist or is never reached
void printHii() {
    cout << "Hii \n";

    printHii();
}

void printHii2(int n) {
    // Base Condition 
    if (n == 0)
        return;

    cout << "Hii \n";

    printHii2(n);   
    // since inside the recursive call, n is not decremented while passing, base condition never executes 
}

int fibonacci(int n) {
    if (n == 0 || n == 1) 
        return n;
    
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    printHello(5);

    for (int i = 1; i <= 10; i++)
        cout << fibonacci(i) << " ";

    return 0;
}