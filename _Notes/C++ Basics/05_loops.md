# Loops in C++

Loops repeat a block of code while a condition holds.

## for loop

Best when the number of iterations is known in advance.

```cpp
for (int i = 1; i <= 5; i++) {
    cout << i << " ";
}
// Output: 1 2 3 4 5
```

Structure: `for (initialization; condition; update)`

## while loop

Best when the number of iterations is not known beforehand; condition checked before each iteration.

```cpp
int i = 1;
while (i <= 5) {
    cout << i << " ";
    i++;
}
// Output: 1 2 3 4 5
```

## do-while loop

Executes the body at least once, since the condition is checked after execution.

```cpp
int i = 10;
do {
    cout << i << " ";
    i++;
} while (i <= 5);
// Output: 10   (runs once even though condition was false from the start)
```

## Nested loops

```cpp
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        cout << i * j << " ";
    }
    cout << endl;
}
// Prints a 3x3 multiplication table
```

## break — exits the loop entirely

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;
    cout << i << " ";
}
// Output: 1 2 3 4
```

## continue — skips current iteration, moves to next

```cpp
for (int i = 1; i <= 5; i++) {
    if (i == 3) continue;
    cout << i << " ";
}
// Output: 1 2 4 5
```

## Range-based for loop (C++11+)

Useful for iterating over containers like arrays, vectors, strings.

```cpp
int arr[] = {10, 20, 30, 40};
for (int val : arr) {
    cout << val << " ";
}
// Output: 10 20 30 40

string s = "hi";
for (char c : s) {
    cout << c << " ";
}
// Output: h i
```

## Infinite loops (use carefully)

```cpp
// for (;;) { ... }      // infinite for loop
// while (true) { ... }  // infinite while loop
// Must have a break or return inside to eventually stop
```

## Quick comparison

| Loop | Condition checked | Use case |
|---|---|---|
| `for` | before each iteration | known iteration count |
| `while` | before each iteration | unknown iteration count |
| `do-while` | after each iteration | must run at least once |
