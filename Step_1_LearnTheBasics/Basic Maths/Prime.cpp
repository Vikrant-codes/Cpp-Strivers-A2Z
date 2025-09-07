#include <iostream>
using namespace std;

bool isPrime(int n) {
    if(n<2) return 0;
    for(int i = 2; i*i <= n; i++){
        if (n%i == 0) return 0;
    }
    return 1;
}

int main() {
    cout << "Prime numbers upto 100000" << endl;
    for(int i=1; i<=100000; i++){
        if (isPrime(i)) cout << i << " ";
    }

    return 0;
}