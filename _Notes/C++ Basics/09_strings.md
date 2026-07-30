# Strings in C++

C++ has two ways to work with text: C-style character arrays and the `std::string` class. `std::string` (from `<string>`) is used in almost all modern code.

## Declaration and Initialization

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1 = "Hello";
    string s2("World");
    string s3;               // empty string
    string s4 = s1;          // copy of s1

    cout << s1 << " " << s2 << endl;  // Hello World
    return 0;
}
```

Unlike C-style arrays, `std::string` is **not fixed size** — it resizes automatically.

## Concatenation

```cpp
string first = "Hello";
string second = "World";

string result = first + " " + second;   // Hello World
first += "!";                            // Hello!

cout << result << endl;
cout << first << endl;
```

## Accessing Characters

```cpp
string s = "Hello";
cout << s[0] << endl;        // H
cout << s.at(1) << endl;     // e (at() also does bounds-checking, throws exception if out of range)
cout << s.front() << endl;   // H (first char)
cout << s.back() << endl;    // o (last char)
```

## Length / Size

```cpp
string s = "Hello";
cout << s.length() << endl;  // 5
cout << s.size() << endl;    // 5 (same thing, both work)
```

## Comparing Strings

```cpp
string a = "apple";
string b = "banana";

cout << (a == b) << endl;    // 0 (false)
cout << (a < b) << endl;     // 1 (true, lexicographic comparison)
cout << a.compare(b) << endl; // negative value since 'a' < 'b' alphabetically
```

## Substring

```cpp
string s = "Hello World";
cout << s.substr(6) << endl;      // World  (from index 6 to end)
cout << s.substr(0, 5) << endl;   // Hello  (from index 0, length 5)
```

## Searching

```cpp
string s = "Hello World";
cout << s.find("World") << endl;   // 6 (starting index where found)
cout << s.find("xyz") << endl;     // returns string::npos (a huge number meaning "not found")

if (s.find("World") != string::npos) {
    cout << "Found!" << endl;
}
```

## Modifying Strings

```cpp
string s = "Hello World";

s.replace(6, 5, "C++");    // replace 5 chars starting at index 6
cout << s << endl;          // Hello C++

s.erase(5, 1);               // remove 1 character starting at index 5
cout << s << endl;           // HelloC++

s.insert(5, " ");             // insert a space at index 5
cout << s << endl;            // Hello C++
```

## Appending and Clearing

```cpp
string s = "Hi";
s.append(" there");  // same effect as +=
cout << s << endl;   // Hi there

s.clear();            // empties the string
cout << s.empty() << endl;  // 1 (true)
```

## Converting Case (using loop + cctype)

`std::string` doesn't have a built-in `.toUpper()`, so it's done manually or with `transform`.

```cpp
#include <algorithm>
string s = "hello";
for (char &c : s) {
    c = toupper(c);
}
cout << s << endl;  // HELLO

// or using transform:
string s2 = "WORLD";
transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
cout << s2 << endl;  // world
```

## Iterating Over a String

```cpp
string s = "abc";
for (char c : s) {
    cout << c << " ";
}
// Output: a b c
```

## String to Number & Number to String

```cpp
string numStr = "123";
int n = stoi(numStr);      // string -> int
double d = stod("3.14");   // string -> double

int x = 45;
string s = to_string(x);   // int -> string
```

## Quick Reference

| Method | Purpose |
|---|---|
| `.length()` / `.size()` | number of characters |
| `.substr(pos, len)` | extract substring |
| `.find(str)` | index of first occurrence, or `npos` |
| `.replace(pos, len, str)` | replace part of string |
| `.erase(pos, len)` | remove characters |
| `.insert(pos, str)` | insert into string |
| `.append(str)` / `+=` | add to end |
| `.compare(str)` | lexicographic comparison |
| `.empty()` | true if length is 0 |
| `.clear()` | empties the string |
