# Character Functions in C++

Characters are stored as their ASCII integer values internally, which is why char and int convert into each other so easily.

## char to int direct conversion

```cpp
#include <iostream>
using namespace std;

int main() {
    char c = 'A';
    int code = c;               // implicit conversion, no cast needed
    cout << code << endl;       // 65

    int i = 66;
    char ch = i;                // int -> char, implicit conversion
    cout << ch << endl;         // B

    // explicit version
    cout << (int)'a' << endl;   // 97
    cout << (char)(97 + 1) << endl; // 'b'
    return 0;
}
```

### Digit character to actual number

A common trick: subtract `'0'` from a digit character to get its numeric value, since digit characters `'0'`-`'9'` are contiguous in ASCII (48-57).

```cpp
char digit = '7';
int value = digit - '0';   // 55 - 48 = 7
cout << value << endl;     // 7
```

### Case conversion using ASCII arithmetic

```cpp
char lower = 'a';
char upper = lower - 32;   // 'a' - 32 = 'A' (uppercase offset)
cout << upper << endl;     // A

char upperC = 'B';
char lowerC = upperC + 32;
cout << lowerC << endl;    // b
```

## `<cctype>` Library Functions

Cleaner and safer than manual ASCII arithmetic.

```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char c = 'a';

    cout << isalpha(c) << endl;   // 1 (true) - is it a letter?
    cout << isdigit(c) << endl;   // 0 (false) - is it a digit?
    cout << isupper(c) << endl;   // 0 - is it uppercase?
    cout << islower(c) << endl;   // 1 - is it lowercase?
    cout << isspace(' ') << endl; // 1 - is it whitespace?
    cout << isalnum(c) << endl;   // 1 - letter or digit?

    cout << (char)toupper(c) << endl;  // A - convert to uppercase
    cout << (char)tolower('X') << endl; // x - convert to lowercase

    return 0;
}
```

## Practical Example: Counting vowels in a string

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Hello World";
    int count = 0;

    for (char c : s) {
        char lower = tolower(c);
        if (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u') {
            count++;
        }
    }
    cout << "Vowels: " << count << endl;  // 3
    return 0;
}
```

## Quick Reference Table

| Function | Purpose |
|---|---|
| `isalpha(c)` | true if letter |
| `isdigit(c)` | true if digit 0-9 |
| `isalnum(c)` | true if letter or digit |
| `isupper(c)` | true if uppercase |
| `islower(c)` | true if lowercase |
| `isspace(c)` | true if space/tab/newline |
| `toupper(c)` | converts to uppercase |
| `tolower(c)` | converts to lowercase |
