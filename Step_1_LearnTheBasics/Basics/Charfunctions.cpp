#include <iostream>
#include <cctype>
// The <cctype> header provides functions for working with characters (from the old C <ctype.h>).
// They’re mostly character classification and conversion utilities.
// All functions take an int (often a char promoted to int) and return either int (true/false, or converted char).
using namespace std;

// Functions available in <cctype>:
/*
🔹 Character classification functions : These return non-zero (true) if condition is satisfied, else 0 (false):

Function	            Meaning	                            Example
isalpha(ch)         	Alphabetic (A–Z, a–z)	            'Z' → true
isdigit(ch)           	Decimal digit (0–9)	                '5' → true
isalnum(ch)         	Alphanumeric (A–Z, a–z, 0–9)	    'a' → true
islower(ch)         	Lowercase letter (a–z)	            'm' → true
isupper(ch)         	Uppercase letter (A–Z)	            'G' → true
isspace(ch)         	Whitespace (' ', \n, \t, etc.)	    '\t' → true
iscntrl(ch)             Control character (\n, \t, etc.)	'\n' → true
isgraph(ch)         	Printable but not space	            '@' → true
isprint(ch)         	Printable (including space)	        ' ' → true
ispunct(ch)         	Punctuation	                        '!' → true
isxdigit(ch)       	    Hexadecimal digit (0–9, A–F, a–f)	'B' → true

🔹 Character conversion functions : These return the converted character as int:

Function	        Meaning	                Example
tolower(ch)	        Upper → lower	        'A' → 'a'
toupper(ch)	        Lower → upper	        'z' → 'Z'
*/

int main() {
    char chars[] = {'A', 'z', '5', ' ', '!', 'f','@','#','\t'};

    for (char c : chars) {
        cout << "Character: " << c << endl;

        if (isalnum(c)) cout << " - Alphanumeric\n";
        if (isalpha(c)) cout << " - Alphabetic\n";
        if (isdigit(c)) cout << " - Digit\n";
        if (isspace(c)) cout << " - Whitespace\n";
        if (isupper(c)) cout << " - Uppercase\n";
        if (islower(c)) cout << " - Lowercase\n";
        if (ispunct(c)) cout << " - Punctuation\n";
        if (isxdigit(c)) cout << " - Hexadecimal digit\n";
        if (isprint(c)) cout << " - Printable\n";
        if (iscntrl(c)) cout << " - Control character\n";

        cout << "   tolower: " << (char)tolower(c) << "\n";
        cout << "   toupper: " << (char)toupper(c) << "\n";
        cout << "----------------------\n";
    }

    char ch = '\n';
    if (iscntrl(ch)) cout << "newline is a control character\n";
    if (isspace(ch)) cout << "newline is a whitespace character\n";
    if (!isprint(ch)) cout << "newline is not a printable character\n";

    return 0;
}