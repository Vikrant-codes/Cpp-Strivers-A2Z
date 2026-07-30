# Variables, Data Types & Type Conversion

## Variables

A variable is a named storage location in memory whose value can change.

```cpp
int age = 20;          // declaration + initialization
float price;           // declaration only
price = 99.5;           // assignment later
int x = 5, y = 10;      // multiple declarations
const int MAX = 100;    // constant - value cannot change after this
```

## Data Types

| Type | Size (typical) | Example |
|---|---|---|
| `int` | 4 bytes | `int x = 10;` |
| `float` | 4 bytes | `float x = 3.14f;` |
| `double` | 8 bytes | `double x = 3.14159;` |
| `char` | 1 byte | `char x = 'A';` |
| `bool` | 1 byte | `bool x = true;` |
| `string` | varies | `string x = "hi";` |
| `long` / `long long` | 8 bytes | `long long x = 123456789LL;` |
| `short` | 2 bytes | `short x = 10;` |

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    return 0;
}
```

### Signed vs Unsigned

`unsigned int` only stores non-negative values but gives double the positive range compared to `int`.

```cpp
unsigned int u = 4000000000; // valid, int alone would overflow
int i = -5;                  // valid for signed int only
```

## Type Conversion

### Implicit Conversion (Type Promotion) — done automatically by compiler

```cpp
int a = 5;
double b = a;        // int -> double, automatic, no data loss
cout << b << endl;   // 5

char c = 'A';
int code = c;         // char -> int, automatic
cout << code << endl; // 65 (ASCII value)

double d = 9.7;
int e = d;             // double -> int, DATA LOSS (truncates decimal)
cout << e << endl;     // 9
```

### Explicit Conversion (Type Casting) — done manually

```cpp
double pi = 3.14159;

int x = (int)pi;           // C-style cast
int y = int(pi);           // function-style cast
int z = static_cast<int>(pi); // C++ style cast (recommended)

cout << x << " " << y << " " << z << endl; // 3 3 3
```

**Why prefer `static_cast`?** It's checked at compile time and clearly shows intent — safer than C-style casts, especially in larger codebases.

### String <-> Number Conversion

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // number to string
    int num = 42;
    string s = to_string(num);

    // string to number
    string str = "123";
    int n = stoi(str);       // string to int
    double dbl = stod("3.14"); // string to double

    cout << s << " " << n << " " << dbl << endl;
    return 0;
}
```

### Common Overflow Pitfall

```cpp
int a = 2147483647;  // max value of int
a = a + 1;            // overflow - wraps around to negative
cout << a << endl;    // undefined/implementation behavior, typically -2147483648
```
