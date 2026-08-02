# Character Functions in C++

Under the hood, every character in C++ is stored as a small integer, following a standard called ASCII (American Standard Code for Information Interchange). For example, `'A'` is stored as the number `65`, `'a'` as `97`, and `'0'` as `48`. This is precisely why characters and integers convert into each other so effortlessly in C++ — they're really the same kind of data, just interpreted differently depending on the context.

## char to int Direct Conversion

Because a `char` is really just a small integer underneath, assigning one to the other requires no special function — the compiler handles it automatically.

```cpp
#include <iostream>
using namespace std;

int main() {
    char c = 'A';
    int code = c;
    cout << code << endl;

    int i = 66;
    char ch = i;
    cout << ch << endl;

    cout << (int)'a' << endl;
    cout << (char)(97 + 1) << endl;
    return 0;
}
```

`int code = c;` converts `'A'` into its underlying ASCII value, printing `65`. Going the other direction, `char ch = i;` takes the integer `66` and interprets it as a character, printing `B`. The explicit casts `(int)'a'` and `(char)(97 + 1)` do the same conversions manually, printing `97` and `b` respectively — since `97` is `'a'`'s ASCII code, adding `1` gives `98`, which is `'b'`.

### Digit Character to Actual Numeric Value

A frequently used trick relies on the fact that the digit characters `'0'` through `'9'` occupy consecutive ASCII values, from `48` to `57`. Subtracting the ASCII code of `'0'` from any digit character converts it directly into its numeric equivalent.

```cpp
char digit = '7';
int value = digit - '0';
cout << value << endl;
```

Here, `'7'` has ASCII value `55`, and `'0'` has ASCII value `48`. Subtracting them gives `7` — the actual number the character represents, rather than its ASCII code. This trick is extremely common when parsing digits out of user input or strings one character at a time, since input read from `cin` or a string is naturally made up of characters, not numbers.

### Case Conversion Using ASCII Arithmetic

Similarly, uppercase and lowercase letters are separated by a fixed offset of exactly `32` in the ASCII table, which allows manual case conversion through simple arithmetic.

```cpp
char lower = 'a';
char upper = lower - 32;
cout << upper << endl;

char upperC = 'B';
char lowerC = upperC + 32;
cout << lowerC << endl;
```

Subtracting `32` from a lowercase letter converts it to uppercase, so `'a' - 32` becomes `'A'`. Adding `32` to an uppercase letter does the reverse, turning `'B'` into `'b'`. While this works, it's a bit fragile — it relies on knowing exact ASCII offsets by heart — so in practice, the standard library functions covered below are almost always preferred.

## The `<cctype>` Library

Rather than relying on manual ASCII arithmetic, C++ provides a set of ready-made functions in the `<cctype>` header that check and transform characters more safely and readably.

```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char c = 'a';

    cout << isalpha(c) << endl;
    cout << isdigit(c) << endl;
    cout << isupper(c) << endl;
    cout << islower(c) << endl;
    cout << isspace(' ') << endl;
    cout << isalnum(c) << endl;

    cout << (char)toupper(c) << endl;
    cout << (char)tolower('X') << endl;

    return 0;
}
```

`isalpha`, `isdigit`, `isupper`, `islower`, `isspace`, and `isalnum` all return a non-zero value (treated as `true`) if the character matches the check, and `0` (`false`) otherwise. Here, `c` holds `'a'`, so `isalpha(c)` returns true (`1`), `isdigit(c)` returns false (`0`) since `'a'` isn't a digit, and `islower(c)` returns true since it's a lowercase letter. `toupper` and `tolower` convert a character to the opposite case, returning it as an `int`, which is why the result is typically cast back to `char` before printing — otherwise `cout` would print the underlying numeric ASCII code instead of the letter itself.

## Practical Example: Counting Vowels in a String

Combining character functions with a loop makes many text-processing tasks straightforward.

```cpp
#include <iostream>
#include <string>
#include <cctype>
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
    cout << "Vowels: " << count << endl;
    return 0;
}
```

This walks through each character in `s`, converts it to lowercase first so that the comparison works regardless of the original case, and increments `count` whenever a vowel is found. For `"Hello World"`, the vowels are `e`, `o`, and `o`, giving a final count of `3`.

## Quick Reference

| Function | Purpose |
|---|---|
| `isalpha(c)` | true if `c` is a letter |
| `isdigit(c)` | true if `c` is a digit 0-9 |
| `isalnum(c)` | true if `c` is a letter or digit |
| `isupper(c)` | true if `c` is uppercase |
| `islower(c)` | true if `c` is lowercase |
| `isspace(c)` | true if `c` is a space, tab, or newline |
| `toupper(c)` | returns the uppercase version of `c` |
| `tolower(c)` | returns the lowercase version of `c` |
