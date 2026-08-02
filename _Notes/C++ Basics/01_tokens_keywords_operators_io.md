# C++ Basics: Program Structure, Tokens, Keywords, Operators & I/O

## Basic Program Structure

Every C++ program needs a few standard pieces before it can do anything useful. Here's the smallest complete program:

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

`#include <iostream>` is a preprocessor directive. Before the actual compilation happens, the preprocessor copies the contents of the `iostream` header into your file — this is where the input/output tools (`cin`, `cout`) are defined, so without it you can't print or read anything.

`using namespace std;` tells the compiler that all the standard library names (`cout`, `cin`, `string`, etc.) come from the `std` namespace, so you don't have to write `std::cout` every time. It's convenient for small programs, though larger projects often avoid it to prevent naming clashes.

`int main()` is where every C++ program begins execution, no matter how many other functions exist in the file. The `int` return type means the function is expected to return a whole number back to the operating system — by convention, `return 0;` signals that the program finished successfully, while any non-zero value signals some kind of error occurred.

## Tokens

A token is the smallest meaningful unit that the compiler recognizes while reading your source code — think of it like the "words" of the language, similar to how a sentence in English is built from words and punctuation. When the compiler processes your code, it breaks everything down into a stream of these tokens before it can understand what you're asking it to do. C++ recognizes five categories of tokens:

| Token Type | What it is | Examples |
|---|---|---|
| Keywords | Reserved words with special meaning | `int`, `if`, `return`, `class` |
| Identifiers | Names you create | `sum`, `myVar`, `calculateArea` |
| Literals | Fixed values written directly in code | `10`, `3.14`, `'A'`, `"text"`, `true` |
| Punctuators | Structural symbols | `{ } ( ) ; ,` |
| Operators | Symbols that perform actions on values | `+ - * / == && ||` |

## Keywords

Keywords are words that already have a fixed, built-in meaning in C++ — the compiler treats them specially, so you cannot use them as the name of a variable, function, or class. There are close to 95 keywords in modern C++, and you've probably already used several of them without thinking of them as a separate category. A few of the most commonly used ones:

```
int      float    double   char     bool     void
if       else     switch   case     default
for      while    do       break    continue
return   class    struct   public   private
static   const    new      delete   namespace
try      catch    throw    sizeof   enum
```

If you try to name a variable after a keyword, the compiler will refuse:

```cpp
int class = 5;
```

This fails to compile because `class` already means something to C++ — it can't also be treated as a variable name.

## Identifiers

An identifier is simply a name that you, the programmer, choose for a variable, function, class, or any other entity in your program. C++ gives you freedom in naming, but with a few strict rules:

- It can contain letters, digits, and the underscore character `_`.
- It must begin with a letter or an underscore — never with a digit.
- It is case-sensitive, so `total` and `Total` are treated as two completely different names.
- It cannot be one of the reserved keywords.

```cpp
int age;
int _count;
int total_1;
```

These are all valid, but the following would fail to compile:

```cpp
int 1total;
int int;
```

`1total` starts with a digit, which isn't allowed, and `int` is a keyword, so it can't double as a variable name.

## Literals (Constants)

A literal is a fixed value that appears directly in your source code — it doesn't change, and it represents itself exactly as written. Every data type has its own way of writing literals:

```cpp
int a = 10;
float b = 3.14f;
double c = 3.14159;
char d = 'A';
string e = "Hello";
bool f = true;
int hex = 0x1A;
int oct = 032;
int bin = 0b1010;
```

Notice that character literals use single quotes (`'A'`) while string literals use double quotes (`"Hello"`) — these are not interchangeable, and mixing them up is a common beginner mistake. The `f` suffix on `3.14f` tells the compiler this is specifically a `float` rather than the default `double`. The `0x`, leading `0`, and `0b` prefixes let you write numbers directly in hexadecimal, octal, and binary respectively, which is occasionally useful in low-level or bit-manipulation code.

## Input / Output

### Output with cout

`cout` (pronounced "see-out") sends data to the standard output, which is usually your terminal screen. The `<<` operator is called the "insertion operator" — it inserts whatever is on its right into the output stream.

```cpp
int age = 20;
cout << "Age: " << age << endl;
```

You can chain as many `<<` as you like in a single statement, and `cout` will print each piece one after another. `endl` inserts a newline character and also flushes the output buffer (forces any pending output to actually be written out immediately). The alternative `"\n"` also creates a newline but is slightly cheaper performance-wise since it skips the flush — for most beginner programs the difference isn't noticeable, but it's good to know both exist.

### Input with cin

`cin` (pronounced "see-in") reads data typed by the user through the keyboard. The `>>` operator, called the "extraction operator," pulls data out of the input stream and stores it into a variable.

```cpp
int age;
string name;

cout << "Enter your name: ";
cin >> name;

cout << "Enter your age: ";
cin >> age;

cout << name << " is " << age << " years old." << endl;
```

One important detail: `cin >> name` only reads a single "word" — it stops as soon as it hits a space, tab, or newline. So if the user types "John Smith", `cin >> name` would only capture "John" and leave "Smith" waiting in the input buffer.

### Reading a full line with getline

When you need to capture an entire line of text, including spaces, `getline` is the right tool:

```cpp
string fullName;
cout << "Enter full name: ";
getline(cin, fullName);
cout << "Hello, " << fullName << endl;
```

A very common beginner pitfall happens when `cin >>` is used right before a `getline` call. After `cin >> age` reads the number, it leaves the trailing newline character (from when the user pressed Enter) still sitting in the input buffer. The very next `getline` call then immediately reads that leftover newline as an "empty line" instead of waiting for new input. The fix is to clear the buffer manually before calling `getline`:

```cpp
int age;
string name;
cin >> age;
cin.ignore();
getline(cin, name);
```

## Operators

Operators are symbols that tell the compiler to perform a specific operation on one or more values (called operands). C++ has several categories of operators, each suited to a different kind of task.

### Arithmetic Operators

These perform standard mathematical calculations.

```cpp
int a = 10, b = 3;
cout << a + b << endl;
cout << a - b << endl;
cout << a * b << endl;
cout << a / b << endl;
cout << a % b << endl;
```

This prints `13`, `7`, `30`, `3`, and `1` in that order. The division result might surprise beginners — since both `a` and `b` are integers, `a / b` performs integer division and simply drops the decimal part, giving `3` instead of `3.33`. The `%` operator gives the remainder of the division and only works with integer operands, never with `float` or `double`.

If you want a true decimal result, at least one of the operands needs to be a floating-point type:

```cpp
double x = 10, y = 3;
cout << x / y << endl;
```

This produces `3.333...` because the division is now happening between two `double` values.

### Relational Operators

These compare two values and produce a `bool` result (`true` or `false`, displayed as `1` or `0`).

```cpp
int a = 5, b = 8;
cout << (a == b) << endl;
cout << (a != b) << endl;
cout << (a > b) << endl;
cout << (a < b) << endl;
cout << (a >= b) << endl;
cout << (a <= b) << endl;
```

The output here is `0 1 0 1 0 1` — since `5` is less than `8`, the "equal to," "greater than," and "greater than or equal to" comparisons are all false, while "not equal," "less than," and "less than or equal to" are all true.

### Logical Operators

These combine or invert boolean conditions and are essential for building complex conditions in `if` statements.

```cpp
bool p = true, q = false;
cout << (p && q) << endl;
cout << (p || q) << endl;
cout << (!p) << endl;
```

`&&` (AND) only gives `true` if both sides are true, so `p && q` is `0` here. `||` (OR) gives `true` if at least one side is true, so `p || q` is `1`. `!` (NOT) simply flips the value, turning `true` into `false`.

Both `&&` and `||` use something called short-circuit evaluation: if the left-hand side of `&&` is already `false`, C++ won't even bother evaluating the right-hand side, since the overall result is guaranteed to be `false` anyway. The same logic applies to `||` when the left-hand side is already `true`. This matters in practice — it means you can safely write conditions like `if (ptr != nullptr && ptr->value > 0)` without worrying about the second part crashing the program when `ptr` is null.

### Assignment Operators

These update the value of a variable, often as a shorthand for a common pattern.

```cpp
int a = 10;
a += 5;
a -= 3;
a *= 2;
a /= 4;
a %= 4;
```

Each line here is shorthand: `a += 5` means "take the current value of `a`, add 5, and store the result back into `a`." After running through all five lines, `a` goes from `10` to `15`, then `12`, then `24`, then `6`, then `2`.

### Increment and Decrement Operators

These increase or decrease a variable's value by exactly one, and come in two flavors that behave differently depending on where they're used.

```cpp
int a = 5;
cout << a++ << endl;
cout << a << endl;
```

Post-increment (`a++`) returns the current value of `a` first, and only increments it afterward — so the first line prints `5`, and only the second line shows the updated value of `6`.

```cpp
int b = 5;
cout << ++b << endl;
```

Pre-increment (`++b`) increments the value first, then returns the new value — so this line directly prints `6`. The same distinction applies to `--` for decrementing.

### Bitwise Operators

These operate directly on the individual bits of integer values, which is useful in low-level programming, flags, and performance-sensitive code.

```cpp
int a = 12;
int b = 10;

cout << (a & b) << endl;
cout << (a | b) << endl;
cout << (a ^ b) << endl;
cout << (~a) << endl;
cout << (a << 2) << endl;
cout << (a >> 2) << endl;
```

`12` in binary is `1100` and `10` is `1010`. `&` (AND) keeps only the bits that are `1` in both numbers, giving `1000` (which is `8`). `|` (OR) keeps a bit if it's `1` in either number, giving `1110` (`14`). `^` (XOR) keeps a bit only if it differs between the two numbers, giving `0110` (`6`). `~` flips every bit, which for signed integers results in `-13` due to how negative numbers are represented. `<<` shifts bits left, which effectively multiplies by powers of two, so `a << 2` gives `48`. `>>` shifts bits right, dividing by powers of two, giving `3`.

### Ternary (Conditional) Operator

This is a compact, one-line alternative to a simple `if-else` block.

```cpp
int a = 10, b = 20;
int max = (a > b) ? a : b;
cout << max << endl;
```

The expression reads as: "if `a > b` is true, the result is `a`; otherwise, the result is `b`." Since `20` is greater than `10`, `max` becomes `20`. This is best used for short, simple decisions — anything more complex is usually clearer written as a full `if-else`.

### sizeof Operator

`sizeof` tells you how many bytes a type or variable occupies in memory.

```cpp
cout << sizeof(int) << endl;
cout << sizeof(3.14) << endl;
```

This typically prints `4` and `8`, since a standard `int` takes 4 bytes and a `double` literal takes 8 bytes on most systems (exact sizes can vary slightly by platform).

### Operator Precedence

When an expression mixes multiple operators, C++ follows a fixed order of precedence to decide what gets evaluated first — very similar to the "BODMAS" rules from school mathematics. From highest to lowest priority, simplified:

```
() []
++ -- (unary) ! ~
* / %
+ -
<< >>
< <= > >=
== !=
&
^
|
&&
||
?:
= += -= *= /=
```

Rather than memorizing this whole table, the safer habit — especially while learning — is to use parentheses whenever there's any doubt about how an expression will be evaluated. It costs nothing and makes the code clearer to read besides.
