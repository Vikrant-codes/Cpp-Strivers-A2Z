# Math Functions in C++ (`<cmath>`)

All these functions live in the `<cmath>` header and mostly operate on `double` (some have `int` overloads too).

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout << sqrt(25) << endl;      // 5   - square root
    cout << pow(2, 5) << endl;     // 32  - 2 raised to power 5
    cout << abs(-7) << endl;       // 7   - absolute value (int version needs <cstdlib> or <cmath>)
    cout << fabs(-7.5) << endl;    // 7.5 - absolute value for floating point

    cout << ceil(4.2) << endl;     // 5   - rounds UP to nearest integer
    cout << floor(4.8) << endl;    // 4   - rounds DOWN to nearest integer
    cout << round(4.5) << endl;    // 5   - rounds to nearest integer

    cout << log(1) << endl;        // 0   - natural log (base e)
    cout << log10(100) << endl;    // 2   - log base 10
    cout << exp(1) << endl;        // 2.71828... - e^1

    cout << max(3, 7) << endl;     // 7   - larger of two values (in <algorithm>)
    cout << min(3, 7) << endl;     // 3   - smaller of two values (in <algorithm>)

    return 0;
}
```

## Trigonometric Functions (angles in radians)

```cpp
#include <cmath>
const double PI = 3.14159265;

double angle = PI / 2;   // 90 degrees in radians

cout << sin(angle) << endl;   // 1
cout << cos(0) << endl;       // 1
cout << tan(PI / 4) << endl;  // 1

// converting degrees to radians
double degrees = 90;
double radians = degrees * PI / 180;
```

## Common Function Reference

| Function | Description | Example |
|---|---|---|
| `sqrt(x)` | square root | `sqrt(16)` → 4 |
| `pow(x, y)` | x raised to power y | `pow(3, 3)` → 27 |
| `abs(x)` / `fabs(x)` | absolute value | `abs(-5)` → 5 |
| `ceil(x)` | round up | `ceil(3.1)` → 4 |
| `floor(x)` | round down | `floor(3.9)` → 3 |
| `round(x)` | round to nearest | `round(3.5)` → 4 |
| `log(x)` | natural log | `log(1)` → 0 |
| `log10(x)` | log base 10 | `log10(1000)` → 3 |
| `exp(x)` | e^x | `exp(0)` → 1 |
| `sin/cos/tan(x)` | trig functions (radians) | — |
| `max(a, b)` / `min(a, b)` | larger/smaller value (`<algorithm>`) | — |
| `fmod(a, b)` | modulus for floats | `fmod(5.5, 2)` → 1.5 |

## Practical Example: Distance between two points

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    cout << "Distance: " << distance << endl;  // 5
    return 0;
}
```

## Practical Example: Check if a number is prime

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
    cout << isPrime(17) << endl;  // 1 (true)
    cout << isPrime(15) << endl;  // 0 (false)
    return 0;
}
```
