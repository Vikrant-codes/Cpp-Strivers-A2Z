#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "Enter your age : ";
    cin >> age;
    if(age >= 18) {
        cout << "You have the right to vote !!";
    }
    else {
        cout << "Sorry, you are not old enough to vote.";
    }
    cout << '\n';

    /*
    Grading System
    A ~ 80 - 100                B ~ 60 - 79                 C ~ 50 - 59
    D ~ 45 - 49                 E ~ 25 - 44                 F ~ Below 25
    */

    int marks;
    cout << "Enter your Marks (out of 100) : ";
    cin >> marks;
    if(marks < 0 || marks > 100) {
        cout << "Invalid Marks";
    }
    else if(marks < 25) {
        cout << "Grade : F";
    }
    else if(marks < 45) {
        cout << "Grade : E";
    }
    else if(marks < 50) {
        cout << "Grade : D";
    }
    else if(marks < 60) {
        cout << "Grade : C";
    }
    else if(marks < 80) {
        cout << "Grade : B";
    }
    else {
        cout << "Grade : A";
    }
    cout << '\n';

    // Switch
    cout << "Enter day of the week (1-7) : ";
    int day;
    cin >> day;
    switch(day) {
        case 1:
            cout << "Monday";
            break;
        case 2:
            cout << "Tuesday";
            break;
        case 3:
            cout << "Wednesday";
            break;
        case 4:
            cout << "Thursday";
            break;
        case 5:
            cout << "Friday";
            break;
        case 6:
            cout << "Saturday";
            break;
        case 7:
            cout << "Sunday";
            break;
        default:
            cout << "Invalid Input";
    }
    cout << "\n \n";

    // for loop
    for(int i = 1; i <= 7; i = i + 1) {
        cout << "I love C++ x " << i << endl;
    }
    cout << '\n';

    // for-each loop: loop that eases the traversal over an iterable data set
    // for-each loop is less flexible as here we can only traverse the iterable data-set from left to right.
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    for (int& x : arr) {
        cout << x << " "; 
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
    int num;
    do {
        cout << "Enter a positive number : ";
        cin >> num;
    } while (num <= 0);
    
    return 0;
}
