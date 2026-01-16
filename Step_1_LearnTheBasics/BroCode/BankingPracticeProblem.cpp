#include <iostream>
#include <iomanip>          // header file for setprecision & fixed functions
using namespace std;

float balance = 0;

void showBalance() {
    cout << "Balance : " << setprecision(2) << fixed << balance << " Rs. \n";
}

void deposit () {
    float amount;
    cout << "How much money would you like to deposit, sir ? : ";
    cin >> amount;

    balance += amount;

    cout << amount << " Rs. deposited to your account successfully !! \n";
    showBalance();
}

void withdraw() {
    float amount;
    showBalance();
    cout << "How much money would you like to withdraw, sir ? : ";
    cin >> amount;

    if (amount > balance) 
        cout << "You don't have enough balance... Unable to withdraw \n";
    else {
        balance -= amount;
        cout << amount << " Rs. withdrawed from your account !! \n";
    }
}

int main() {
    float balance = 0;
    int choice;
    do {
        cout << "\n--------Bank--------\n";
        cout << "1. Show Balance \n2. Deposit Money \n3. Withdraw Money \n4. Exit \n";
        cout << "--------------------\n\n";

        cout << "Enter your Choice : ";
        cin >> choice;

        switch(choice) {
            case 1:
                showBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4: 
                cout << "Thanks for visiting us !!\n";
                break;
            default:
                cout << "!! Invalid choice !!\n";
        }

    } while (choice != 4);

    return 0;
}