# Operators in C++

## Arithmetic Operators

```cpp
int a = 10, b = 3;
cout << a + b << endl;  // 13
cout << a - b << endl;  // 7
cout << a * b << endl;  // 30
cout << a / b << endl;  // 3  (integer division - decimal part dropped)
cout << a % b << endl;  // 1  (modulus - remainder)

double x = 10, y = 3;
cout << x / y << endl;  // 3.333... (float division since operands are double)
```

**Note:** `%` (modulus) only works with integer operands, not float/double.

## Relational Operators

Return `bool` (`true`/`false`).

```cpp
int a = 5, b = 8;
cout << (a == b) << endl;  // 0 (false)
cout << (a != b) << endl;  // 1 (true)
cout << (a > b) << endl;   // 0
cout << (a < b) << endl;   // 1
cout << (a >= b) << endl;  // 0
cout << (a <= b) << endl;  // 1
```

## Logical Operators

```cpp
bool p = true, q = false;
cout << (p && q) << endl;  // AND -> 0
cout << (p || q) << endl;  // OR  -> 1
cout << (!p) << endl;      // NOT -> 0
```

`&&` and `||` use short-circuit evaluation — if the first operand of `&&` is false, the second is never evaluated (same for `||` with true).

## Assignment Operators

```cpp
int a = 10;
a += 5;   // a = a + 5   -> 15
a -= 3;   // a = a - 3   -> 12
a *= 2;   // a = a * 2   -> 24
a /= 4;   // a = a / 4   -> 6
a %= 4;   // a = a % 4   -> 2
```

## Increment / Decrement Operators

```cpp
int a = 5;
cout << a++ << endl;  // 5 (post-increment: use then increment) -> a is now 6
cout << ++a << endl;  // 7 (pre-increment: increment then use)

int b = 5;
cout << b-- << endl;  // 5 -> b is now 4
cout << --b << endl;  // 3
```

## Bitwise Operators

Operate directly on binary representation.

```cpp
int a = 12;  // 1100
int b = 10;  // 1010

cout << (a & b) << endl;   // AND  -> 8  (1000)
cout << (a | b) << endl;   // OR   -> 14 (1110)
cout << (a ^ b) << endl;   // XOR  -> 6  (0110)
cout << (~a) << endl;      // NOT  -> -13 (inverts all bits)
cout << (a << 2) << endl;  // left shift  -> 48 (multiplies by 2^2)
cout << (a >> 2) << endl;  // right shift -> 3  (divides by 2^2)
```

## Ternary (Conditional) Operator

Shorthand for simple if-else.

```cpp
int a = 10, b = 20;
int max = (a > b) ? a : b;
cout << max << endl;  // 20
```

## Comma Operator

```cpp
int a = (1, 2, 3);  // evaluates left to right, result is last expression
cout << a << endl;  // 3
```

## `sizeof` Operator

```cpp
cout << sizeof(int) << endl;     // 4
cout << sizeof(3.14) << endl;    // 8
```

## Operator Precedence (high to low, simplified)

```
() []                     -> highest
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
= += -= *= /=             -> lowest
```

Use parentheses when unsure — clarity beats memorizing precedence tables.
