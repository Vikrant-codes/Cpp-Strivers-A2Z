#include<iostream>
// #include<bits/stdc++.h>
// This include all C++ libraries so we don't explicityly need to include each one

using namespace std;        // we don't need to use std::cout, std::endl we can directly use cout, endl

int main(){
    cout << "Hello World !!" << endl;
    cout << "What's your name ? \n";
    string name;
    cin >> name;
    cout << "Hello " << name << '\n';
    int x, y;
    cout << "Enter two integers : ";
    cin >> x >> y;
    cout << x << " + " << y << " = " << x+y << endl;

    cout << "Enter a string containing characters : ";
    string s;
    // cin >> s;
    // using cin will stop taking input when any whitespace character is encountered (even a space) 

    // cin.ignore();           // Discards the leftover '\n' character from the input buffer
    getline(cin >> ws, s);
    // cin >> ws : eliminates any newline characters or whitespaces before user input
    // when we use getline, we either need to use cin.ignore() or cin>>ws to remove the '\n' chars from the input buffer

    cout << s;

    return 0;
}