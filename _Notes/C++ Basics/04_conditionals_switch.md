# Conditional Statements: if-else & switch

## if statement

```cpp
int age = 20;
if (age >= 18) {
    cout << "Adult" << endl;
}
```

## if-else

```cpp
int num = -5;
if (num >= 0) {
    cout << "Positive" << endl;
} else {
    cout << "Negative" << endl;
}
```

## if-else if-else (multi-way branching)

```cpp
int marks = 75;

if (marks >= 90) {
    cout << "Grade A" << endl;
} else if (marks >= 75) {
    cout << "Grade B" << endl;
} else if (marks >= 50) {
    cout << "Grade C" << endl;
} else {
    cout << "Fail" << endl;
}
```

## Nested if

```cpp
int age = 25;
bool hasID = true;

if (age >= 18) {
    if (hasID) {
        cout << "Entry allowed" << endl;
    } else {
        cout << "ID required" << endl;
    }
} else {
    cout << "Too young" << endl;
}
```

## switch statement

Used when checking one variable against multiple fixed values. Only works with `int`, `char`, or `enum` (not `string`, not floating point).

```cpp
int day = 3;

switch (day) {
    case 1:
        cout << "Monday" << endl;
        break;
    case 2:
        cout << "Tuesday" << endl;
        break;
    case 3:
        cout << "Wednesday" << endl;
        break;
    default:
        cout << "Invalid day" << endl;
}
```

**`break` is important** — without it, execution "falls through" to the next case.

```cpp
int x = 1;
switch (x) {
    case 1:
        cout << "One ";      // no break -> falls through
    case 2:
        cout << "Two ";      // this also runs
        break;
    case 3:
        cout << "Three";
        break;
}
// Output: One Two
```

### Fall-through can be intentional (grouping cases)

```cpp
char grade = 'B';
switch (grade) {
    case 'A':
    case 'B':
        cout << "Good performance" << endl;
        break;
    case 'C':
        cout << "Average" << endl;
        break;
    default:
        cout << "Needs improvement" << endl;
}
```

## if-else vs switch

| if-else | switch |
|---|---|
| Works with ranges, complex conditions | Only exact-value matching |
| Works with any data type | Only `int`/`char`/`enum` |
| Slightly slower for many conditions | Can be faster (jump table) |
