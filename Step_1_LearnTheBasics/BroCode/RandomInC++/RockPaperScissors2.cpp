#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char getUserChoice() {
    char ch;
    do {
        cout << "Enter 'r' : rock, 'p' : paper, 's' : scissors -> ";
        cin >> ch;
    } while (ch != 'r' && ch != 'p' && ch != 's');
    return ch;
}

char getComputerChoice() {
    srand(time(0));
    char rps[] = {'r', 'p', 's'};
    int num = rand() % 3;
    return rps[num];
}

void showChoice(char choice) {
    switch(choice) {
        case 'r':
            cout << "Rock \n";
            break;
        case 'p':
            cout << "Paper \n";
            break;
        case 's':
            cout << "Scissors \n";
            break;
    }
}

void getResults(char p1, char p2) {
    if (p1 == p2) 
        cout << "It's a tie X_X \n";
    else if ( (p1 == 'r' && p2 == 's') || (p1 == 'p' && p2 == 'r') || (p1 == 's' && p2 == 'p') )
        cout << "You won ^_^ \n";
    else 
        cout << "You lose :[ \n";
}

int main() {
    char play = 'y';
    while (play == 'y') {
        cout << "\n---- Rock | Paper | Scissors ----\n\n";

        char player = getUserChoice();
        cout << "Your Choice: ";
        showChoice(player);

        char computer = getComputerChoice();
        cout << "Computer's Choice: ";
        showChoice(computer);
        getResults(player, computer);

        cout << "Wanna play again ? (Enter y to play again): ";
        cin >> play;
    }    

    return 0;
}