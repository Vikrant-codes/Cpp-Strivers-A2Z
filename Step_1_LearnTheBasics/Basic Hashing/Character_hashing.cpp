#include <iostream>
using namespace std;

int main() {
    string s, s2;
    cout << "Enter String (only lowercase alphabets): ";
    cin >> s;
    int len = s.size();

    int hasharr[26] = {0};          // 26 size for 26 alphabets
    // hasharr[s[i] - 'a'] is the same as hasharr[ (int)x - 95 ]
    // Pre-compute
    for(int i = 0; i<len; i++) hasharr[s[i] - 'a'] += 1;

    int q;
    do {
        char x;
        cout << "Enter the character : ";
        cin >> x;
        // fetch
        cout << "Frequency of " << x << " is : " << hasharr[x - 'a'] << endl;
        cout << "Press 0 to exit --> ";
        cin >> q;
    } while (q != 0);

    cout << "Enter string containing any characters : ";
    cin.ignore();
    getline(cin, s2);
    int len2 = s2.size();
    // Pre-compute
    int hasharr2[256] = {0};
    for(int i = 0; i<len2; i++) hasharr2[s2[i]] += 1;
    
    int q2;
    do {
        char x;
        cout << "Enter the character : ";
        cin.get(x);         // cin >> x; will not work for whitespaces (including spcae, tab and newline characters)
        // fetch
        cout << "Frequency of " << x << " is : " << hasharr2[x] << endl;
        cout << "Press 0 to exit --> ";
        cin >> q2;
    } while (q2 != 0);

    // for lowercase alphabets : use char - 'a' as index for hasharray
    // for uppercase alphabets : use char - 'A' as index for hasharray
    // for all characters : use char as index for hasharray 

    return 0;
}