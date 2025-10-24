#include<iostream>
using namespace std;

int main() {
    // 🧩 1. Char → ASCII (integer) : ✅ Simply assigning a char to an int gives its ASCII code.
    char ch = 'A';
    int ascii = ch;        // ascii = 65
    cout << ch << " : " << ascii << endl;

    // 🧩 2. ASCII (integer) → Char : ✅ Assigning an integer to a char gives the character of that ASCII code.
    ascii = 97;
    ch = ascii;
    cout << ascii << " : " << ch << endl;

    // 🧩 3. Char Digit → Integer : ✅ Subtract '0' (ASCII 48) to get numeric value.
    ch = '7';
    int num = ch - '0';    // num = 7
    cout << ch << " : " << num << endl;

    // 🧩 4. Integer (0–9) → Char Digit : ✅ Add '0' to convert an integer digit to its character.
    num = 5;
    ch = num + '0';   // ch = '5'
    cout << num << " : " << ch << endl;

    // 🧩 5. Alphabet → Position (a/A = 1, …, z/Z = 26)
    ch = 'e';
    int pos = tolower(ch) - 'a' + 1;   // pos = 5
    cout << ch << " : " << pos << endl;

    // 🧩 6. Position (1–26) → Alphabet
    pos = 5;
    ch = 'a' + pos - 1;   // ch = 'e'
    cout << pos << " : " << ch << endl;

    return 0;
}