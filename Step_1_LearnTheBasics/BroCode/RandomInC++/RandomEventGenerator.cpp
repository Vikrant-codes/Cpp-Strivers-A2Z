#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int randNum = rand() % 5 + 1;

    cout << "Your random super-power is :- \n";
    switch(randNum) {
        case 1: 
            cout << "Energy blasts";
            break;
        case 2: 
            cout << "Telekinesis";
            break;
        case 3: 
            cout << "Lightning control";
            break;
        case 4:
            cout << "Time manipulation";
            break;
        case 5: 
            cout << "Super speed";
            break;
    }

    return 0;
}