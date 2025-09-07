#include <iostream>
using namespace std;

int main() {
    int num;
    // for loop
    for(int i = 1; i <= 7; i = i + 1) {
        cout << "I love C++ x " << i << endl;
    }
    cout << '\n';
    // while loop
    int i = 1;
    while(i <= 7) {
        cout << "Wizard Codes x " << i << endl;
        i++;
    }
    cout << '\n';
    // do-while loop
    do {
        cout << "Enter a positive number: ";
        cin >> num;
    } while (num <= 0);
    cout << "You entered: " << num << endl;

    return 0;
}
