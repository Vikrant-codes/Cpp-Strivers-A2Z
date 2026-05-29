#include<iostream>
using namespace std;

/*
Input string from user and print in increasing order of characters :: ex - below is pattern for string "I_love_C++"
I
I_
I_l
I_lo
I_lov
I_love
I_love_
I_love_C
I_love_C+
I_love_C++
*/

int main() {
    string s;
    cout << "Enter the String : ";
    getline(cin, s);
    int len = s.size();
    for(int i=0; i<len; i++){
        for(int j=0; j<=i; j++){
            cout << s[j];
        }
        cout << endl;
    }

    return 0;
}