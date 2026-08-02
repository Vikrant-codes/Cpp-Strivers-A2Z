# Variables, Data Types & Type Conversion

## Variables

A variable is a named location in memory that holds a value which can change over the course of a program. Before you can use a variable, it needs to be declared with a specific type, which tells the compiler how much memory to set aside and how to interpret the bits stored there.

```cpp
int age = 20;
float price;
price = 99.5;
int x = 5, y = 10;
const int MAX = 100;
```

`int age = 20;` both declares the variable and gives it an initial value in the same line. `float price;` only declares it — at this point `price` holds an unpredictable "garbage" value until it's actually assigned something, which happens on the next line. You can also declare several variables of the same type on one line, as shown with `x` and `y`. The `const` keyword marks a variable as unchangeable after its initial assignment — trying to modify `MAX` later in the program would cause a compile error, which is exactly the point: it protects values that should never change, like a fixed maximum limit.

## Data Types

C++ is a statically-typed language, meaning every variable's type is fixed at the point it's declared and cannot change afterward. Here are the fundamental built-in types you'll use constantly:

| Type | Typical Size | Example |
|---|---|---|
| `int` | 4 bytes | `int x = 10;` |
| `float` | 4 bytes | `float x = 3.14f;` |
| `double` | 8 bytes | `double x = 3.14159;` |
| `char` | 1 byte | `char x = 'A';` |
| `bool` | 1 byte | `bool x = true;` |
| `string` | varies | `string x = "hi";` |
| `long` / `long long` | 8 bytes | `long long x = 123456789LL;` |
| `short` | 2 bytes | `short x = 10;` |

`float` and `double` both store decimal numbers, but `double` offers roughly double the precision and is the default choice unless memory is tightly constrained. `long long` exists because a plain `int` can only hold values up to around 2.1 billion — anything larger (like factorial results or large counters) needs the extra range that `long long` provides.

You can check the exact size of any type on your system using the `sizeof` operator:

```cpp
cout << "Size of int: " << sizeof(int) << " bytes" << endl;
cout << "Size of double: " << sizeof(double) << " bytes" << endl;
cout << "Size of char: " << sizeof(char) << " bytes" << endl;
```

This will typically print `4`, `8`, and `1` respectively, though the exact numbers can theoretically vary between compilers and architectures.

### Signed vs Unsigned

By default, numeric types in C++ are "signed," meaning they can represent both negative and positive values. Adding `unsigned` in front of a type restricts it to zero and positive values only, but in exchange doubles the maximum positive value it can hold, since it no longer needs to reserve a bit for the sign.

```cpp
unsigned int u = 4000000000;
int i = -5;
```

The value `4000000000` is too large for a regular signed `int` (whose maximum is about 2.1 billion) but fits comfortably within `unsigned int`'s range. Meanwhile, a regular `int` like `i` can freely hold negative values, which an `unsigned int` never can.

## Type Conversion

Type conversion is the process of changing a value from one data type to another. C++ allows this in two distinct ways.

### Implicit Conversion (Type Promotion)

This happens automatically, without you writing any special syntax — the compiler quietly converts one type into another when it's needed.

```cpp
int a = 5;
double b = a;
cout << b << endl;
```

Here, assigning an `int` to a `double` variable is completely safe — the value `5` becomes `5.0` with no information lost, since a `double` can represent every value an `int` can, plus more.

```cpp
char c = 'A';
int code = c;
cout << code << endl;
```

This prints `65`, because characters are actually stored internally as small integers representing their position in the ASCII table — `'A'` corresponds to the number `65`. When you assign a `char` to an `int` variable, C++ automatically converts it to that underlying numeric value.

Not every implicit conversion is safe, though:

```cpp
double d = 9.7;
int e = d;
cout << e << endl;
```

This prints `9`, not `10` — assigning a `double` to an `int` truncates (chops off) the decimal part entirely rather than rounding, so precision is silently lost. This is a common source of subtle bugs, since the compiler won't warn you unless you have extra warning flags enabled.

### Explicit Conversion (Type Casting)

When you want full control over a conversion — and want it to be obvious in the code that a conversion is intentional — you use a cast.

```cpp
double pi = 3.14159;

int x = (int)pi;
int y = int(pi);
int z = static_cast<int>(pi);
```

All three lines achieve the same result, converting `pi` to the integer `3`, but they represent three different casting styles. `(int)pi` is the old C-style cast inherited from C, `int(pi)` is a function-style cast, and `static_cast<int>(pi)` is the modern C++ way of doing it. `static_cast` is generally preferred in C++ code because it's checked more carefully by the compiler and makes the programmer's intent unmistakably clear — especially valuable in larger codebases where a plain `(int)` cast could easily hide a mistake.

### String and Number Conversion

Since numbers and text are fundamentally different types, converting between them requires dedicated functions rather than a simple cast.

```cpp
int num = 42;
string s = to_string(num);

string str = "123";
int n = stoi(str);
double dbl = stod("3.14");
```

`to_string` converts any numeric type into its text representation, which is useful when you want to concatenate a number onto a string. Going the other direction, `stoi` ("string to int") and `stod` ("string to double") parse a numeric value out of a string — these are especially handy when reading numeric input that initially comes in as text, such as from a file or user input that needs validation first.

### Overflow — a common pitfall

Every integer type has a maximum value it can represent, and going past that limit causes "overflow," where the value silently wraps around rather than raising an error.

```cpp
int a = 2147483647;
a = a + 1;
cout << a << endl;
```

`2147483647` is the maximum value a standard 32-bit `int` can hold. Adding `1` past this limit doesn't raise any warning or error — instead, it wraps around to a large negative number (typically `-2147483648`), because of how the underlying binary representation works. This kind of bug can be tricky to spot, since the program keeps running without crashing; using a larger type like `long long` is the usual fix when you expect very large values.
