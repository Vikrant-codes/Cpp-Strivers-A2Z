#include <iostream>
using namespace std;

void fun(int n) {
    if (n == 0) return;
    cout << n << '\n';
    fun(n-1);
}

void infiniteFun() {
    cout << "Hello World\n";
    infiniteFun();
}

int x = 1;
void print() {
    cout << x++ << '\n';
    print();
}

int fibonacci(int n) {
    if (n == 0 || n == 1) 
        return n;
    
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    // print();
    // fun(5);
    // infiniteFun();

    for (int i = 1; i <= 10; i++)
        cout << fibonacci(i) << " ";

    return 0;
}