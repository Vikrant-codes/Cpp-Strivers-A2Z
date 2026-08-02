# Conditionals & Loops in C++

Programs rarely execute in a single straight line from top to bottom — they need to make decisions and repeat actions. Conditionals handle the decisions, and loops handle the repetition.

## Conditionals

### if statement

The `if` statement runs a block of code only when a given condition evaluates to `true`.

```cpp
int age = 20;
if (age >= 18) {
    cout << "Adult" << endl;
}
```

Since `age` is `20`, which satisfies `age >= 18`, the message inside the braces gets printed. If the condition had been false, that block would simply be skipped entirely, and execution would continue with whatever comes after it.

### if-else

Often you want one thing to happen when a condition is true, and something different when it's false — that's what `else` provides.

```cpp
int num = -5;
if (num >= 0) {
    cout << "Positive" << endl;
} else {
    cout << "Negative" << endl;
}
```

Since `num` is `-5`, the condition `num >= 0` is false, so the program skips the first block and runs the `else` block instead, printing "Negative".

### if-else if-else (multi-way branching)

When there are more than two possible outcomes, you can chain multiple conditions together using `else if`.

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

C++ checks each condition in order, from top to bottom, and executes the first block whose condition is true — the rest are skipped, even if they would also technically be true. Here, `marks` is `75`, so it fails the first check (`>= 90`), but passes the second (`>= 75`), so "Grade B" is printed and none of the remaining conditions are even checked.

### Nested if

An `if` statement can contain another `if` statement inside it, which is useful when a decision depends on more than one condition in sequence rather than being combined into a single logical expression.

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

The outer condition checks age first; only if that passes does the program bother checking whether the person has an ID. This mirrors how you'd reason through the logic yourself: there's no point asking for an ID from someone who's already too young to enter.

### switch statement

The `switch` statement is a cleaner alternative to a long chain of `else if` statements, but only when you're comparing a single variable against several exact, fixed values. It works with `int`, `char`, and `enum` types, but not with `string` or floating-point numbers.

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

The program jumps straight to the `case` label matching the value of `day`, which here is `3`, so it prints "Wednesday". The `default` label acts as a catch-all for any value that doesn't match any of the listed cases, similar to a final `else`.

The `break` statement at the end of each case is critical. Without it, execution doesn't stop at the end of a matching case — it keeps "falling through" and running the code in the next case as well, whether or not that case actually matches.

```cpp
int x = 1;
switch (x) {
    case 1:
        cout << "One ";
    case 2:
        cout << "Two ";
        break;
    case 3:
        cout << "Three";
        break;
}
```

Since `x` is `1`, execution starts at `case 1`. Because there's no `break` after printing "One ", the program doesn't stop there — it continues straight into `case 2` and prints "Two " as well, only stopping once it hits that `break`. The output ends up being "One Two ", which surprises a lot of beginners the first time they encounter it.

Sometimes fall-through is actually intentional, used to group multiple cases that should share the same behavior:

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

Since `case 'A'` has no code or `break` directly under it, both `'A'` and `'B'` fall through into the same "Good performance" message — this is a common and perfectly legitimate pattern for grouping related cases.

### if-else vs switch

Both tools can often solve the same problem, but they suit different situations. `if-else` handles ranges, complex boolean expressions, and any data type, while `switch` is limited to exact-value matching on a small set of types. When you're matching a single variable against several fixed values, `switch` tends to read more cleanly and can sometimes be optimized by the compiler into a faster jump table; when the logic involves ranges or multiple conditions combined together, `if-else` is the more natural and often the only option.

## Loops

Loops let you repeat a block of code multiple times without duplicating it manually, which is essential for tasks like processing every element in a list or repeating an action until some condition is met.

### for loop

The `for` loop is the natural choice when you already know how many times you want to repeat something.

```cpp
for (int i = 1; i <= 5; i++) {
    cout << i << " ";
}
```

This prints `1 2 3 4 5`. The `for` loop has three parts separated by semicolons: the initialization (`int i = 1`), which runs once at the very start; the condition (`i <= 5`), which is checked before every single iteration and stops the loop as soon as it becomes false; and the update (`i++`), which runs at the end of every iteration. Together, these three pieces control exactly how many times the loop body executes.

### while loop

The `while` loop is better suited to situations where you don't know in advance exactly how many times the loop needs to run — it simply keeps going as long as its condition stays true.

```cpp
int i = 1;
while (i <= 5) {
    cout << i << " ";
    i++;
}
```

This produces the same output as the `for` loop example above, `1 2 3 4 5`, but the structure emphasizes the condition itself rather than a fixed count — you're responsible for updating `i` manually inside the loop body, unlike with `for`, where the update is built into the loop's own syntax.

### do-while loop

A `do-while` loop is almost identical to `while`, except that it checks its condition after running the loop body rather than before. This guarantees the body always executes at least once, no matter what the condition is.

```cpp
int i = 10;
do {
    cout << i << " ";
    i++;
} while (i <= 5);
```

Even though `i` starts at `10`, which already fails the condition `i <= 5`, the loop still prints `10` once before checking the condition and immediately stopping. This behavior is useful in situations like menu-driven programs, where you want to show the menu at least once before deciding whether to repeat it.

### Nested loops

A loop can contain another loop inside its body — this is common when working with grids, tables, or anything with two dimensions.

```cpp
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        cout << i * j << " ";
    }
    cout << endl;
}
```

For every single value of the outer loop's `i`, the entire inner loop runs completely from start to finish before `i` moves on to its next value. This produces a 3x3 multiplication table, with each row representing one value of `i` multiplied against every value of `j`.

### break — exits the loop entirely

`break` immediately stops the loop altogether, regardless of what the loop's condition would otherwise say.

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;
    cout << i << " ";
}
```

This prints `1 2 3 4` and then stops — as soon as `i` reaches `5`, the `break` statement exits the loop immediately, even though the loop's own condition (`i <= 10`) would otherwise have allowed it to keep going all the way to `10`.

### continue — skips just the current iteration

`continue` is more targeted than `break` — rather than ending the loop, it skips only the rest of the current iteration and jumps straight to the next one.

```cpp
for (int i = 1; i <= 5; i++) {
    if (i == 3) continue;
    cout << i << " ";
}
```

This prints `1 2 4 5` — when `i` equals `3`, the `continue` statement skips the `cout` line for that particular iteration, but the loop itself keeps running normally afterward.

### Range-based for loop

Introduced in C++11, this is a simplified way to loop over every element of a container — such as an array, vector, or string — without manually managing an index variable.

```cpp
int arr[] = {10, 20, 30, 40};
for (int val : arr) {
    cout << val << " ";
}
```

This reads naturally as "for each value in arr," and prints `10 20 30 40`. It's shorter and less error-prone than a classic index-based loop, since there's no risk of accidentally going out of bounds.

```cpp
string s = "hi";
for (char c : s) {
    cout << c << " ";
}
```

The same syntax works just as well on a string, iterating over each character in turn and printing `h i`.

### Infinite loops

A loop whose condition never becomes false will run forever unless something inside it explicitly breaks out.

```cpp
while (true) {
    // needs a break or return somewhere inside to eventually stop
}
```

This pattern is sometimes used intentionally — for example, a program that keeps prompting the user until they choose to quit — but it always needs some kind of exit condition inside the loop body, whether that's a `break`, a `return`, or an external event.

### Choosing the right loop

| Loop | Condition checked | Best used when |
|---|---|---|
| `for` | before each iteration | the number of iterations is known ahead of time |
| `while` | before each iteration | the number of iterations depends on a condition, not a fixed count |
| `do-while` | after each iteration | the loop body must run at least once regardless of the condition |
