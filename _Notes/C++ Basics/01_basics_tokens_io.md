# C++ Basics: Structure, Tokens, Keywords, Identifiers, Literals & I/O

## Basic Program Structure

```cpp
#include <iostream>   // header for input/output
using namespace std;  // avoids writing std:: everywhere

int main() {
    cout << "Hello, World!" << endl;
    return 0;          // tells OS the program ran successfully
}
```

- `#include` is a preprocessor directive — it copies header code before compilation.
- `main()` is the entry point; execution always starts here.
- `return 0;` means successful termination (non-zero usually means error).

## Tokens

A **token** is the smallest individual unit in a program that the compiler understands. C++ has 5 types of tokens:

| Token Type | Examples |
|---|---|
| Keywords | `int`, `if`, `return`, `class` |
| Identifiers | `sum`, `myVar`, `calculateArea` |
| Literals (constants) | `10`, `3.14`, `'A'`, `"text"`, `true` |
| Punctuators | `{ } ( ) ; , #` |
| Operators | `+ - * / = == && ||` |

## Keywords

Reserved words with fixed meaning — cannot be used as variable/function names.

```cpp
int, float, double, char, bool, void, if, else, switch, case,
for, while, do, break, continue, return, class, struct, public,
private, static, const, new, delete, try, catch, throw, namespace
```

Total ~95 keywords in C++ (varies slightly by standard). Attempting `int class = 5;` gives a compile error.

## Identifiers

Names given to variables, functions, classes, etc.

**Rules:**
- Can contain letters, digits, and underscore `_`
- Must start with a letter or underscore (not a digit)
- Case-sensitive (`sum` and `Sum` are different)
- Cannot be a keyword

```cpp
int age;        // valid
int _count;     // valid
int total_1;    // valid
int 1total;     // INVALID - starts with digit
int int;        // INVALID - keyword
```

## Literals (Constants)

Fixed values that don't change during execution.

```cpp
int a = 10;           // integer literal
float b = 3.14f;      // floating-point literal
double c = 3.14159;   // double literal
char d = 'A';         // character literal (single quotes)
string e = "Hello";   // string literal (double quotes)
bool f = true;        // boolean literal
int hex = 0x1A;       // hexadecimal literal
int oct = 032;        // octal literal (leading 0)
int bin = 0b1010;     // binary literal (C++14+)
```

## Input / Output

### Output — `cout`

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 20;
    cout << "Age: " << age << endl;   // endl inserts a newline and flushes buffer
    cout << "Age: " << age << "\n";   // \n also gives newline, no flush
    return 0;
}
```

### Input — `cin`

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    string name;

    cout << "Enter your name: ";
    cin >> name;              // reads a single word (stops at whitespace)

    cout << "Enter your age: ";
    cin >> age;

    cout << name << " is " << age << " years old." << endl;
    return 0;
}
```

### Reading a full line — `getline`

`cin >> name` stops at the first space, so it can't read "John Smith" fully.

```cpp
#include <iostream>
using namespace std;

int main() {
    string fullName;
    cout << "Enter full name: ";
    getline(cin, fullName);   // reads entire line including spaces
    cout << "Hello, " << fullName << endl;
    return 0;
}
```

**Common pitfall:** mixing `cin >>` and `getline` — `cin >>` leaves a trailing `\n` in the buffer which `getline` then reads as an empty line. Fix with `cin.ignore();` between them.

```cpp
int age;
string name;
cin >> age;
cin.ignore();          // clears leftover newline
getline(cin, name);
```
