# Parameterized Recursion and Functional Recursion

These two terms — **parameterized recursion** and **functional recursion** — are commonly used when learning recursion in DSA.

The difference is mainly **how the recursive function carries and returns the result**.

---

# 1. Parameterized Recursion

In **parameterized recursion**, we pass the answer/result accumulated so far as a **parameter** to the recursive function.

The recursive call keeps updating that parameter until the base case is reached.

## Example: Sum of First N Numbers

We want:

```text
1 + 2 + 3 + ... + N
```

For `N = 5`:

### Parameterized version

```C++
void sum(int n, int result) {
    if (n == 0) {
        cout << result;
        return;
    }

    sum(n - 1, result + n);
}
```

Call:

```C++
sum(5, 0);
```

### What happens?

Think of `result` as an **accumulator**:

```text
sum(5, 0)
    ↓
sum(4, 5)
    ↓
sum(3, 9)
    ↓
sum(2, 12)
    ↓
sum(1, 14)
    ↓
sum(0, 15)
```

At the base case:

```C++
n == 0
```

we have:

```text
result = 15
```

Therefore:

```text
1 + 2 + 3 + 4 + 5 = 15
```

### Key idea

The answer is being built **while going down the recursive calls**.

```text
     result
       ↓
sum(5, 0)
sum(4, 5)
sum(3, 9)
sum(2, 12)
sum(1, 14)
sum(0, 15)  ← answer
```

That's why it is called **parameterized recursion**: the changing answer is explicitly passed as a parameter.

---

# 2. Functional Recursion

In **functional recursion**, the function **returns a value**, and the recursive calls are combined to produce the final answer.

We don't explicitly carry an accumulator parameter.

For the same problem:

```C++
int sum(int n) {
    if (n == 0)
        return 0;

    return n + sum(n - 1);
}
```

Call:

```C++
int result = sum(5);
```

Now the execution looks like:

```text
sum(5)
    ↓
    5 + sum(4)
            ↓
            4 + sum(3)
                  ↓
                  3 + sum(2)
                        ↓
                        2 + sum(1)
                              ↓
                              1 + sum(0)
                                    ↓
                                    0
```

Then the functions start **returning back**:

```text
sum(0) = 0

sum(1) = 1 + 0  = 1

sum(2) = 2 + 1  = 3

sum(3) = 3 + 3  = 6

sum(4) = 4 + 6  = 10

sum(5) = 5 + 10 = 15
```

So:

```C++
cout << sum(5);
```

prints:

```text
15
```

---

# The Main Difference

This is the most important thing to understand.

## Parameterized Recursion

**"I'll carry the answer with me."**

The result is passed **downward**.

```text
     result
       ↓
sum(5, 0)
sum(4, 5)
sum(3, 9)
sum(2, 12)
sum(1, 14)
sum(0, 15)  ← answer
```

---

## Functional Recursion

**"I'll ask the smaller recursive call for its answer, then use it."**

The answer comes **back upward**.

Calling:
```text
sum(5)
    ↓
    5 + sum(4)
            ↓
            4 + sum(3)
                  ↓
                  3 + sum(2)
                        ↓
                        2 + sum(1)
                              ↓
                              1 + sum(0)
                                    ↓
                                    0
```

Return
```text
sum(5)
    ↑
    5 + sum(4)
            ↑
            4 + sum(3)
                  ↑
                  3 + sum(2)
                        ↑
                        2 + sum(1)
                              ↑
                              1 + sum(0)
                                    ↑
                                    0
Caller
    ↑ returns 15 (5 + sum(4))
sum(5)
    ↑ returns 10 (4 + sum(3))
sum(4)
    ↑ returns 6 (3 + sum(2))
sum(3)
    ↑ returns 3 (2 + sum(1))
sum(2)
    ↑ returns 1 (1 + sum(0))
sum(1)
    ↑ returns 0
sum(0)
        
```

---

# Another Example: Factorial

Factorial:

```text
5! = 5 × 4 × 3 × 2 × 1
```

## Parameterized Factorial

```C++
void factorial(int n, int result) {
    if (n == 0) {
        cout << result;
        return;
    }

    factorial(n - 1, result * n);
}
```

Call:

```C++
factorial(5, 1);
```

Execution:

```text
factorial(5, 1)
factorial(4, 5)
factorial(3, 20)
factorial(2, 60)
factorial(1, 120)
factorial(0, 120)
```

Answer = `120`.

---

## Functional Factorial

```C++
int factorial(int n) {
    if (n == 0)
        return 1;

    return n * factorial(n - 1);
}
```

Execution:

```text
factorial(5)
= 5 * factorial(4)
= 5 * (4 * factorial(3))
= 5 * (4 * (3 * factorial(2)))
= 5 * (4 * (3 * (2 * factorial(1))))
= 5 * (4 * (3 * (2 * (1 * factorial(0)))))
```

Then:

```text
factorial(0) = 1
factorial(1) = 1
factorial(2) = 2
factorial(3) = 6
factorial(4) = 24
factorial(5) = 120
```

---

# A Very Important Connection

You can think of these as two different ways of solving the **same recursive problem**.

## Parameterized

```C++
f(n, accumulatedAnswer)
```

> "I already have some answer. Keep modifying it."

The answer is **carried downward** through the recursive calls.

## Functional

```C++
f(n)
```

> "I don't have the answer yet. Ask the smaller problem to give me its answer."

The answer is **returned upward** through the recursive calls.

---

# Quick Comparison

| | Parameterized Recursion | Functional Recursion |
|---|---|---|
| Result | Passed as a parameter | Returned by the function |
| Answer built | While going down | While coming back |
| Usually uses accumulator? | Yes | No |
| Return type | Often `void` | Usually non-void |
| Example | `sum(n, result)` | `sum(n)` |
| Mental model | **Carry the answer** | **Ask for the answer** |

---

# One-Line Memory Trick

> **Parameterized recursion → carry the result down.**

> **Functional recursion → get the result back up.**