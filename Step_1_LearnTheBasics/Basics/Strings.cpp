#include<iostream>
using namespace std;

int main() {
    // <-- Strings -->

    string s1,s2,s3;
    cout << "Input s1 (A B): ";
    /*cin >> reads input until it encounters whitespace (like spaces, tabs, or newlines).*/
    cin >> s1;          // Input "A B", s1 will store only "A"
    cout << "s1 : " << s1;
    cout << "\nInput (C D) : ";
    cin >> s1 >> s2 >> s3;    // Input "C D"
    cout << "s1 : " << s1 << " s2 : " << s2 << " s3 : " << s3 << endl;      // s1 : B  s2 : C  s3 : D

    // If you use cin before getline(), add cin.ignore() to discard the leftover newline.
    // cin.ignore() is used to ignore or clear one or more characters from the input buffer.
    // Without cin.ignore(), getline() may skip input because of the leftover \n from cin
    int x;
    string str;
    cout << "Enter an integer: ";
    cin >> x;             // Takes an integer
    cout << "Enter a sentence: ";
    cin.ignore();         // Discards the '\n' left in the buffer
    getline(cin, str);      // Now takes the full line
    cout << "You entered: " << str << endl;


    string s = "wizard";
    int len1 = s.size();
    int len2 = s.length();
    // length(): Emphasizes the concept of string length, making code more intuitive for readability.
    // size(): More generic and consistent with other container classes like vector, list, etc.
    cout << len1 << '\t' << len2 << '\n';
    
    for(int i = 0; i < len1; i++) {
        cout << s[i];
    }

    s[0] = 'W';
    cout << '\n' << "s = " << s;

    return 0;
}