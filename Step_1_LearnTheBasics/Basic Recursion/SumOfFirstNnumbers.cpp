#include <iostream>
using namespace std;

// Sum of First N Natural Numbers

// Using Parameterized Recursion
void sum(int n, int ans) {
    if (n < 1) {
        cout << ans << endl;
        return;
    }

    sum(n - 1, ans + n);
}

// Using Functional Recursion
int sum(int n) {
    if (n == 1)
        return 1;

    return n + sum(n - 1);
}

int main(){
    int n;
    cout << "Enter n : ";
    cin >> n;
    cout << "Sum of first " << n << " Natural numbers:" << endl;
    
    cout << "-> using Parameterized Recursion: ";
    sum(n, 0);
    cout << "-> using Functional Recursion: " << sum(n) << endl;

    return 0;
}