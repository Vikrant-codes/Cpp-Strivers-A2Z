# Strings in C++

C++ offers two ways of working with text: old-style C character arrays, and the `std::string` class from the `<string>` header. Nearly all modern C++ code uses `std::string`, since it handles memory management automatically and comes with a rich set of built-in methods.

## Declaration and Initialization

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1 = "Hello";
    string s2("World");
    string s3;
    string s4 = s1;

    cout << s1 << " " << s2 << endl;
    return 0;
}
```

`s1` and `s2` show two equivalent ways to initialize a string with a value. `s3` declares an empty string, ready to be filled in later. `s4` creates a full independent copy of `s1` — modifying `s4` afterward would have no effect on `s1`. Unlike a raw C-style character array, a `std::string` isn't fixed in size — it automatically grows or shrinks in memory as needed, which is one of its biggest advantages.

## Concatenation

Joining strings together is done with the `+` operator, or `+=` to append onto an existing string in place.

```cpp
string first = "Hello";
string second = "World";

string result = first + " " + second;
first += "!";

cout << result << endl;
cout << first << endl;
```

`result` combines `first`, a space, and `second` into a single new string, `"Hello World"`. Meanwhile, `first += "!"` modifies `first` directly, appending an exclamation mark onto it, turning it into `"Hello!"`.

## Accessing Characters

Individual characters within a string can be accessed much like elements in an array, using square-bracket indexing starting from `0`.

```cpp
string s = "Hello";
cout << s[0] << endl;
cout << s.at(1) << endl;
cout << s.front() << endl;
cout << s.back() << endl;
```

`s[0]` gives `'H'`, the first character. `s.at(1)` gives `'e'`, the second character — functionally similar to `s[1]`, but `.at()` performs bounds-checking and will throw an exception if you give it an invalid index, whereas `s[]` will not warn you and simply reads invalid memory instead. `.front()` and `.back()` are convenient shortcuts for the first and last characters respectively, giving `'H'` and `'o'` here.

## Length and Size

```cpp
string s = "Hello";
cout << s.length() << endl;
cout << s.size() << endl;
```

Both `.length()` and `.size()` return the exact same thing — the number of characters in the string, which is `5` here. Both exist for historical reasons (string was originally modeled after other container types that use `.size()`), and it doesn't matter which one you choose.

## Comparing Strings

Strings can be compared directly with the usual relational operators, using lexicographic (dictionary-style) ordering.

```cpp
string a = "apple";
string b = "banana";

cout << (a == b) << endl;
cout << (a < b) << endl;
cout << a.compare(b) << endl;
```

`a == b` is `false`, since the two strings aren't identical. `a < b` is `true` because `"apple"` comes before `"banana"` alphabetically — under the hood, this comparison works character by character based on ASCII values. `.compare()` gives a more detailed result: a negative number if the calling string comes before the argument alphabetically, zero if they're equal, and a positive number if it comes after — here it returns a negative value since `'a'` comes before `'b'`.

## Substring

`.substr()` extracts a portion of a string without modifying the original.

```cpp
string s = "Hello World";
cout << s.substr(6) << endl;
cout << s.substr(0, 5) << endl;
```

`s.substr(6)` starts at index `6` and takes everything from there to the end, giving `"World"`. `s.substr(0, 5)` starts at index `0` and takes exactly `5` characters, giving `"Hello"`. The second argument, when provided, is a length, not an ending index — a detail worth remembering, since it's easy to mix up with other languages' substring functions.

## Searching

`.find()` looks for the first occurrence of a substring and returns its starting index, or a special value if nothing is found.

```cpp
string s = "Hello World";
cout << s.find("World") << endl;
cout << s.find("xyz") << endl;

if (s.find("World") != string::npos) {
    cout << "Found!" << endl;
}
```

`s.find("World")` returns `6`, since `"World"` begins at index `6` within `s`. When the search text isn't found at all, as with `"xyz"`, `.find()` returns `string::npos` — a special constant representing "not a valid position," rather than something like `-1`. Because `npos` is a somewhat unusual, very large number rather than a small negative one, the standard way to check for a failed search is always to compare against `string::npos` directly, exactly as shown in the `if` statement.

## Modifying Strings

```cpp
string s = "Hello World";

s.replace(6, 5, "C++");
cout << s << endl;

s.erase(5, 1);
cout << s << endl;

s.insert(5, " ");
cout << s << endl;
```

`.replace(6, 5, "C++")` starts at index `6`, removes `5` characters ("World"), and puts `"C++"` in their place, turning `s` into `"Hello C++"`. `.erase(5, 1)` removes exactly `1` character starting at index `5` (the space), turning it into `"HelloC++"`. `.insert(5, " ")` then inserts a space back in at index `5`, restoring it to `"Hello C++"`. Together, these three methods let you edit a string in place without rebuilding it from scratch.

## Appending and Clearing

```cpp
string s = "Hi";
s.append(" there");
cout << s << endl;

s.clear();
cout << s.empty() << endl;
```

`.append(" there")` behaves exactly like `+=`, adding text onto the end, turning `s` into `"Hi there"`. `.clear()` empties the string entirely, leaving it with a length of `0`, and `.empty()` returns `true` (`1`) whenever a string currently has no characters at all — a common and readable way to check for an empty string rather than comparing its length to zero directly.

## Converting Case

Somewhat surprisingly, `std::string` has no built-in `.toUpper()` or `.toLower()` method — case conversion is done manually, typically by looping through each character and applying a function from `<cctype>`, or using the `<algorithm>` header's `transform` function.

```cpp
#include <algorithm>
#include <cctype>

string s = "hello";
for (char &c : s) {
    c = toupper(c);
}
cout << s << endl;

string s2 = "WORLD";
transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
cout << s2 << endl;
```

In the loop version, `char &c` is a reference to each character in turn, so modifying `c` directly modifies the actual character stored inside `s`, converting the whole string to `"HELLO"`. The `transform` version achieves the same result more compactly: it applies `tolower` to every character between `s2.begin()` and `s2.end()`, writing the results back into `s2` itself, producing `"world"`.

## Iterating Over a String

```cpp
string s = "abc";
for (char c : s) {
    cout << c << " ";
}
```

This range-based loop visits each character of `s` in order, printing `a b c` — a clean way to process every character without manually managing an index.

## String and Number Conversion

```cpp
string numStr = "123";
int n = stoi(numStr);
double d = stod("3.14");

int x = 45;
string s = to_string(x);
```

`stoi` ("string to int") and `stod` ("string to double") parse a numeric value out of a string, which is essential when numeric-looking input arrives as text — for instance, from user input or a file. `to_string` works in the opposite direction, converting any number into its textual representation, useful when building up a message that includes a numeric value.

## Quick Reference

| Method | Purpose |
|---|---|
| `.length()` / `.size()` | number of characters in the string |
| `.substr(pos, len)` | extract a portion of the string |
| `.find(str)` | index of the first occurrence, or `npos` if not found |
| `.replace(pos, len, str)` | replace part of the string with new text |
| `.erase(pos, len)` | remove characters starting at a position |
| `.insert(pos, str)` | insert text at a given position |
| `.append(str)` / `+=` | add text to the end |
| `.compare(str)` | lexicographic comparison against another string |
| `.empty()` | true if the string has zero length |
| `.clear()` | empties the string entirely |
