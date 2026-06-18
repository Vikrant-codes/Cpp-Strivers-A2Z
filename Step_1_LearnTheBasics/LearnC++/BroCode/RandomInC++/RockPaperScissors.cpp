#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    char play = 'Y';
    while (play == 'Y' || play == 'y') {
        cout << "\n--- Rock, Paper & Scissors ---\n\n";
        cout << "1. Rock \n2. Paper \n3. Scissors \n";
        
        int choice;
        cout << "Choose your symbol : ";
        cin >> choice;

        int num = rand() % 3 + 1;           // random to imitate random selection of rock, paper & scissors

        if (choice == num) {
            cout << "--- Draw X_X ---\n";
        }
        else if (choice == 1 && num == 3) {
            cout << "--- You Won ^_^ ---\n";
        }
        else if (choice == 2 && num == 1) {
            cout << "--- You Won ^_^ ---\n";
        }
        else if (choice == 3 && num == 2) {
            cout << "--- You Won ^_^ ---\n";
        }
        else {
            cout << "--- You Lose :[  ---\n";
        }
        cout << "Wanna play again ? Enter 'y'/'Y' to play again : ";
        cin >> play;
    }

    return 0;
}