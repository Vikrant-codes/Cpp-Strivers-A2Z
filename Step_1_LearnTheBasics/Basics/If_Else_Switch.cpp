#include<iostream>
using namespace std;

int main(){
    int age;
    cout << "Enter age : ";
    cin >> age;
    if(age >= 18) {
        cout << "You are an adult";
    }
    else {
        cout << "You are not an adult";
    }

    /*
    Grading System
    A ~ 80 - 100                B ~ 60 - 79                 C ~ 50 - 59
    D ~ 45 - 49                 E ~ 25 - 44                 F ~ Below 25
    */

    int marks;
    cout << '\n' << "Input Marks : ";
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
    
    // Switch
    cout << "\nInput day no. : ";
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

    return 0;
}