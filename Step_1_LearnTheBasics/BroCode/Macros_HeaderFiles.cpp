#include <iostream>
#include <climits>          // INT_MAX & INT_MIN are defined in this header file
using namespace std;

// Header Files
/*
>> What are header files?
🔹 Definition
| A header file is a file that contains declarations or definitions that we can reuse in our program.
- Header files contains :
    • Function declarations
    • Macros
    • Constants
    • Class declarations

- Example:
• <iostream> → contains cout, cin
• <climits> → contains INT_MAX, INT_MIN

>> What does #include actually do?
It literally copies the content of that file into your code before compilation.
👉 Like this:
    #include <climits>
⬇️ becomes (conceptually):
    // content of climits pasted here
    #define INT_MAX 2147483647
    ...

>> Types of header files
1. Standard header files
    #include <iostream>
    #include <climits>
2. User-defined header files
    #include "myfile.h"

--> Difference between < > and " "
• < > → standard library headers
• " " → your own files

>> Why header files exist
- Without them: We’d have to rewrite the same code again and again. No modularity
- With them: Code becomes reusable, cleaner and organized

+------------------------------------------------------------------------+
| Header file = a file that stores reusable code (declarations/macros),  |
| and #include simply pastes it into our program before compilation.     |
+------------------------------------------------------------------------+
*/


// 🧾 Macros in C++
/*
## Macros in C++
🔹 Definition
A macro is just a shortcut name for some code.
Before the program actually compiles, the compiler replaces that name with the actual code.
| Macro = a name that gets replaced with code before compilation (like copy-paste automatically).

- Macros are preprocessor directives handled before compilation
- Defined using '#define'
- Perform direct text substitution

>> Syntax
| #define NAME value
| #define FUNC(x) expression

| Common Naming Convention :- Macros names are generally written in all uppercase.

>> Types
1. Object-like macros
| #define MAX 100
| #define PI 3.14

2. Function-like macros
| #define SQUARE(x) ((x)*(x))
| #define MIN(a,b) ((a)<(b)?(a):(b))


-> Example
    #define PI 3.14

    int main() {
        cout << PI;
    }

👉 What the compiler actually sees after replacement:
    int main() {
        cout << 3.14;
    }
So, PI is not a variable → it's just replaced with 3.14.

-> Another Example
    #define SQUARE(x) (x * x)
    cout << SQUARE(5);
👉 Becomes:
    cout << (5 * 5);

>> Key Idea (Most Important)
- Macros do not run like functions
- They just replace text before compilation

>> Key Properties
- No type checking
- No scope (global replacement)
- No function call overhead
- Can cause bugs if not careful

>> Real-life analogy
Like "Find and Replace" in Word:
- Replace PI → 3.14
- Replace SQUARE(x) → (x * x)
That’s exactly what macros do.

>> Why they can be dangerous
Because it's blind replacement:
    #define SQUARE(x) x * x
    cout << SQUARE(2 + 3);
👉 Becomes:
    cout << 2 + 3 * 2 + 3;  // wrong → 11

>> Standard (built-in) macros
• __FILE__ → file name
• __LINE__ → line number
• __DATE__ → compilation date
• __TIME__ → compilation time
• __cplusplus → C++ version

>> INT_MAX & INT_MIN
- These are defined in '#include <climits>'
- Internally, they are defined like :
    #define INT_MAX 2147483647
    #define INT_MIN (-2147483647 - 1)

>> 🧾 Useful macros in <climits>
🔹 For int
• INT_MAX → maximum value of int
• INT_MIN → minimum value of int

🔹 For char : CHAR_MAX, CHAR_MIN
• SCHAR_MAX → signed char max
• SCHAR_MIN → signed char min
• UCHAR_MAX → unsigned char max

🔹 For short : SHRT_MAX, SHRT_MIN
🔹 For long : LONG_MAX, LONG_MIN
🔹 For long long : LLONG_MAX, LLONG_MIN
🔹 For unsigned types : UINT_MAX, ULONG_MAX, ULLONG_MAX
*/

#define PI 3.1415927
#define SQUARE(x) (x * x)
#define SQUARE2(x) ((x) * (x))

int main() {
    cout << PI << '\n'; // 3.14
    int x = PI;
    cout << x << '\n';      // 3

    cout << SQUARE(5) << '\n';  // 25
    cout << SQUARE(2+3) << '\n'; // 11, since it is evaluated as SQUARE(x) = x * x => SQUARE(2+3) = 2 + 3 * 2 + 3
    cout << SQUARE2(2+ 3) << '\n';  // 25 

    return 0;
}