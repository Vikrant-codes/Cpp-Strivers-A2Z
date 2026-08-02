# Math Functions in C++ (`<cmath>`)

The `<cmath>` header provides a collection of mathematical functions covering common operations like roots, powers, rounding, logarithms, and trigonometry. Most of these functions work with `double` values, though several also have overloads for `float` and `int`.

## Common Functions

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << sqrt(25) << endl;
    cout << pow(2, 5) << endl;
    cout << abs(-7) << endl;
    cout << fabs(-7.5) << endl;

    cout << ceil(4.2) << endl;
    cout << floor(4.8) << endl;
    cout << round(4.5) << endl;

    cout << log(1) << endl;
    cout << log10(100) << endl;
    cout << exp(1) << endl;

    return 0;
}
```

`sqrt(25)` returns `5`, the square root of `25`. `pow(2, 5)` raises `2` to the power of `5`, giving `32`. `abs` and `fabs` both compute an absolute value — `abs` traditionally works on integers, while `fabs` is meant for floating-point numbers, though modern compilers often accept either interchangeably; `abs(-7)` gives `7` and `fabs(-7.5)` gives `7.5`.

`ceil` and `floor` handle rounding in opposite directions: `ceil(4.2)` rounds up to the nearest whole number regardless of how small the decimal part is, giving `5`, while `floor(4.8)` rounds down no matter how close it is to the next integer, giving `4`. `round(4.5)` rounds to the nearest whole number using conventional rounding rules, giving `5`.

`log(1)` computes the natural logarithm (base *e*), which for an input of `1` is always `0`. `log10(100)` computes the base-10 logarithm, giving `2`, since `10^2 = 100`. `exp(1)` computes *e* raised to the given power, so `exp(1)` gives approximately `2.71828`, the value of *e* itself.

## Trigonometric Functions

Trigonometric functions in C++ expect their input angle in radians, not degrees — a detail that trips up a lot of beginners coming from math classes that mostly use degrees.

```cpp
#include <cmath>
const double PI = 3.14159265;

double angle = PI / 2;

cout << sin(angle) << endl;
cout << cos(0) << endl;
cout << tan(PI / 4) << endl;
```

`sin(angle)`, with `angle` set to `PI / 2` (representing 90 degrees), gives `1`, the sine of a right angle. `cos(0)` gives `1`, since the cosine of `0` degrees is always `1`. `tan(PI / 4)` (45 degrees) gives `1` as well, since sine and cosine are equal at that angle.

If you need to convert a degree value into radians before passing it to these functions, the standard formula is:

```cpp
double degrees = 90;
double radians = degrees * PI / 180;
```

This multiplies the degree value by *pi* and divides by `180`, which is the standard conversion factor between the two units.

## max and min

Although technically part of the `<algorithm>` header rather than `<cmath>`, `max` and `min` are used constantly alongside math functions.

```cpp
cout << max(3, 7) << endl;
cout << min(3, 7) << endl;
```

`max(3, 7)` simply returns whichever of the two values is larger, giving `7`, while `min(3, 7)` returns the smaller one, giving `3`. Both work with any comparable type, not just integers.

## Function Reference

| Function | Description | Example |
|---|---|---|
| `sqrt(x)` | square root | `sqrt(16)` → 4 |
| `pow(x, y)` | x raised to the power y | `pow(3, 3)` → 27 |
| `abs(x)` / `fabs(x)` | absolute value | `abs(-5)` → 5 |
| `ceil(x)` | rounds up to nearest integer | `ceil(3.1)` → 4 |
| `floor(x)` | rounds down to nearest integer | `floor(3.9)` → 3 |
| `round(x)` | rounds to nearest integer | `round(3.5)` → 4 |
| `log(x)` | natural logarithm | `log(1)` → 0 |
| `log10(x)` | logarithm base 10 | `log10(1000)` → 3 |
| `exp(x)` | e raised to the power x | `exp(0)` → 1 |
| `sin(x)`, `cos(x)`, `tan(x)` | trigonometric functions (radians) | — |
| `max(a, b)`, `min(a, b)` | larger/smaller of two values (`<algorithm>`) | — |
| `fmod(a, b)` | remainder for floating-point division | `fmod(5.5, 2)` → 1.5 |

## Practical Example: Distance Between Two Points

A very common real-world use of math functions is computing the straight-line distance between two coordinates using the Pythagorean theorem.

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cout << "Distance: " << distance << endl;
    return 0;
}
```

This computes the difference along each axis, squares both differences using `pow`, adds them together, and takes the square root of the sum — the standard distance formula. For the points `(0, 0)` and `(3, 4)`, this gives `5`, matching the well-known 3-4-5 right triangle.

## Practical Example: Checking Whether a Number Is Prime

```cpp
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    cout << isPrime(17) << endl;
    cout << isPrime(15) << endl;
    return 0;
}
```

This function only needs to check potential divisors up to the square root of `n`, rather than all the way up to `n` itself — if `n` had a factor larger than its square root, it would necessarily also have a matching factor smaller than the square root, so checking beyond that point would be redundant. `isPrime(17)` returns `true` since no number between `2` and roughly `4.1` evenly divides `17`, while `isPrime(15)` returns `false`, since `3` divides evenly into it.
