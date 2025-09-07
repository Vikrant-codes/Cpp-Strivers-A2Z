#include<iostream>
// #include<bits/stdc++.h>
// This include all C++ libraries so we don't explicityly need to include each one

using namespace std;        // we don't need to use std::cout, std::endl we can directly use cout, endl

int main(){
    cout << "Hello World!!" << endl;
    cout << "What's your name ? \n";
    string name;
    cin >> name;
    cout << "Hello " << name << '\n';
    int x, y;
    cout << "Enter x and y : ";
    cin >> x >> y;
    cout << x << " + " << y << " = " << x+y;
    return 0;
}