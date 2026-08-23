# Integer and Floating-Point Number Representation

Computers do not store numbers as the mathematical objects we think of them as. At the hardware level, memory contains **bits**—`0`s and `1`s. Integer and floating-point representations are conventions that tell the computer how to interpret groups of those bits as numbers.

This note builds the representation from the ground up:

1. How binary numbers represent unsigned integers
2. How signed integers are represented
3. Sign-magnitude, one's complement, and two's complement
4. Why modern computers use two's complement
5. Integer ranges and overflow
6. How fractional numbers are represented in binary
7. Why floating-point representation is necessary
8. IEEE 754 single precision (`float`)
9. IEEE 754 double precision (`double`)
10. Special values, precision, rounding, and common pitfalls

---

## 1. The Fundamental Idea: Memory Stores Bits

A computer's basic storage unit is a **bit**.

A bit can have only two states:

```text
0
1
```

Physical hardware can implement this in many ways—different voltage levels, transistor states, charge states, etc.—but logically we treat each state as `0` or `1`.

Bits are grouped together:

```text
8 bits   = 1 byte
16 bits  = 2 bytes
32 bits  = 4 bytes
64 bits  = 8 bytes
```

For example, a 32-bit piece of memory might contain:

```text
01000001010010000000000000000000
```

The bits themselves do not inherently mean "integer", "float", "character", etc.

The **interpretation** depends on the data type and representation being used.

The exact same 32 bits could potentially be interpreted as:

- an unsigned integer
- a signed integer
- an IEEE 754 `float`
- several characters
- part of some other data structure

So:

> **Memory stores bits. Data types define how those bits are interpreted.**

---

# 2. Binary Representation of Positive Integers

Before dealing with negative numbers, start with positive integers.

The binary system is base 2.

Each position represents a power of 2:

```text
...  2^4  2^3  2^2  2^1  2^0
...  16    8    4    2    1
```

For example:

```text
13 = 8 + 4 + 1
   = 2^3 + 2^2 + 2^0
```

Therefore:

```text
13 decimal = 1101 binary
```

For an 8-bit representation:

```text
00001101
```

The leading zeros do not change the value.

---

## 3. Unsigned Integers

An **unsigned integer** uses all available bits for the magnitude.

For an `n`-bit unsigned integer:

```text
000...000 = 0
000...001 = 1
000...010 = 2
...
111...111 = 2^n - 1
```

Therefore:

```text
Range = 0 to 2^n - 1
```

For 8 bits:

```text
minimum = 0
maximum = 255
```

because:

```text
2^8 - 1 = 255
```

The maximum value is obtained when every bit is `1`:

```text
11111111
```

which equals:

```text
128 + 64 + 32 + 16 + 8 + 4 + 2 + 1
= 255
```

---

# 4. The Problem of Signed Integers

What about negative numbers?

Suppose we have only 8 bits.

We need to represent:

```text
... -3, -2, -1, 0, 1, 2, 3 ...
```

There are several possible representations.

Historically and conceptually, three important approaches are:

1. Sign-magnitude
2. One's complement
3. Two's complement

Modern general-purpose computers use **two's complement** for signed integers.

Understanding why requires looking at all three.

---

# 5. Sign-Magnitude Representation

The simplest idea is:

> Use one bit for the sign and the remaining bits for the magnitude.

Usually:

```text
0 = positive
1 = negative
```

For 8 bits:

```text
sign | magnitude
```

For example:

```text
+5 = 00000101
-5 = 10000101
```

The magnitude is `5`:

```text
0000101
```

and only the sign bit changes.

## Problem 1: Two representations of zero

We get:

```text
+0 = 00000000
-0 = 10000000
```

So there are **two zeros**.

That wastes one possible bit pattern and complicates hardware.

## Problem 2: Arithmetic is complicated

Adding signed numbers requires special handling of signs and magnitudes.

For example, the processor would have to reason differently about:

```text
(+5) + (+3)
(+5) + (-3)
(-5) + (+3)
(-5) + (-3)
```

The hardware becomes more complicated.

---

# 6. One's Complement

Another idea is:

> Represent a positive number normally, and represent a negative number by flipping every bit of the positive number.

For example:

```text
+5 = 00000101
```

Flip every bit:

```text
11111010
```

Therefore:

```text
-5 = 11111010
```

This operation is called the **one's complement**.

---

## 6.1 How to calculate one's complement

Simply invert every bit:

```text
Original: 10110010
         ↓↓↓↓↓↓↓↓
1's comp: 01001101
```

---

## 6.2 Problem: Two zeros again

Positive zero:

```text
00000000
```

Its one's complement is:

```text
11111111
```

So:

```text
+0 = 00000000
-0 = 11111111
```

Again, we have two representations of zero.

---

## 6.3 Addition requires end-around carry

This is the more important problem.

Consider:

```text
+5 = 00000101
-5 = 11111010
```

Adding:

```text
  00000101
+ 11111010
------------
  11111111
```

But `11111111` represents negative zero in one's complement.

So one's complement arithmetic needs a special rule called **end-around carry**.

If an addition produces a carry beyond the most significant bit, that carry must be added back to the least significant bit.

This means the hardware arithmetic is less clean than we would like.

---

# 7. Two's Complement

Two's complement solves the major problems of the previous approaches.

To obtain the negative representation of a number:

1. Invert all bits
2. Add `1`

For example, to represent `-5`:

Start with `+5`:

```text
00000101
```

Invert:

```text
11111010
```

Add 1:

```text
11111011
```

Therefore:

```text
-5 = 11111011
```

---

# 8. Why Two's Complement Is Preferred

Two's complement has several major advantages.

## 8.1 Only one representation of zero

In 8-bit two's complement:

```text
00000000 = 0
```

There is no separate `-0`.

The bit pattern:

```text
11111111
```

represents `-1`, not negative zero.

If we try to represent `-0` by finding its two's complement.
```text
00000000 = 0
Invert all bits (1's complement): 11111111
Add 1 to one's complement to get the two's complement
   11111111
        + 1
   --------
  100000000 
   --------
Adding 1 propagates a carry of 1 forward which is placed at the 9th bit, 
since we are only dealing with 8 bits, this 9th bit is discarded thus giving us 
two's complement = 00000000
```
---

## 8.2 Addition and subtraction use the same binary adder

This is the biggest practical advantage.

Consider:

```text
5 + (-3)
```

8-bit representations:

```text
  00000101   = +5
+ 11111101   = -3
------------
  00000010   = +2
```

The carry outside the 8-bit range is simply discarded.

This is extremely convenient for hardware.

The same binary addition circuitry can perform signed arithmetic without needing a separate mechanism for positive and negative numbers.

Subtraction can also be converted into addition:

```text
A - B = A + (-B)
```

and `-B` is obtained using two's complement.

---

# 9. Two's Complement Range

For an `n`-bit signed integer using two's complement:

```text
minimum = -2^(n-1)

maximum = 2^(n-1) - 1
```

Therefore, for 8 bits:

```text
minimum = -128
maximum = +127
```

Range:

```text
-128 ... +127
```

Notice that there are:

```text
256
```

possible bit patterns.

And:

```text
128 negative values
+ 127 positive values
+ 1 zero
= 256
```

---

## 9.1 Why is the minimum -128?

The most significant bit has a special negative weight.

For an 8-bit two's complement number:

```text
b7 b6 b5 b4 b3 b2 b1 b0
```

the weights are:

```text
-128  64  32  16  8  4  2  1
```

For example:

```text
10000000
```

means:

```text
-128
```

while:

```text
01111111
```

means:

```text
127
```

---

# 10. Understanding Two's Complement Mathematically

For an `n`-bit pattern:

```text
b(n-1) ... b1 b0
```

its value is:

```text
-b(n-1) * 2^(n-1)
+ b(n-2) * 2^(n-2)
+ ...
+ b1 * 2^1
+ b0 * 2^0
```

For example:

```text
11111011
```

has value:

```text
-128 + 64 + 32 + 16 + 8 + 2 + 1
```

which is:

```text
-5
```

---

# 11. How the Computer Actually Stores an Integer

Suppose we write:

```cpp
int x = 13;
```

Typically, on modern systems, `int` is 32 bits.

Conceptually, memory contains:

```text
00000000 00000000 00000000 00001101
```

The CPU's integer representation interprets these bits as a signed two's-complement integer.

If:

```cpp
int x = -13;
```

the bits would be the two's complement representation of `13`.

Start:

```text
00000000 00000000 00000000 00001101
```

Invert:

```text
11111111 11111111 11111111 11110010
```

Add 1:

```text
11111111 11111111 11111111 11110011
```

So `-13` is stored as:

```text
11111111 11111111 11111111 11110011
```

---

# 12. Important: Integer Representation vs Memory Byte Order

There are two separate concepts that are often confused.

### Number representation

For example:

```text
-13
```

is represented using two's complement.

### Byte order

If the value occupies multiple bytes, the computer also needs to decide which byte is stored at the lowest memory address.

This is called **endianness**.

For example, the 32-bit value:

```text
0x12345678
```

has four bytes:

```text
12 34 56 78
```

A little-endian machine stores them in memory as:

```text
78 56 34 12
```

A big-endian machine stores:

```text
12 34 56 78
```

Endianness does **not** change the mathematical representation of the integer. It changes the order of its bytes in memory.

---

# 13. Integer Overflow

Because an integer has a fixed number of bits, it cannot represent every possible integer.

For an 8-bit signed two's complement integer:

```text
maximum = 127
```

Adding 1:

```text
01111111
+       1
---------
10000000
```

`10000000` represents:

```text
-128
```

So the representation wraps around at the boundary.

This illustrates an important principle:

> **Fixed-width representations have finite ranges.**

For C++, exact overflow behavior depends on whether the integer is signed or unsigned. In particular, signed integer overflow in C++ is not defined as ordinary two's-complement wraparound by the language standard, while unsigned arithmetic is defined modulo \(2^n\).

---

# 14. Why Integers Are Easy Compared with Floating Point

Integers are relatively straightforward because every bit can contribute directly to the value.

For an unsigned binary integer:

```text
101101
```

we calculate:

```text
1*2^5 + 0*2^4 + 1*2^3 + 1*2^2 + 0*2^1 + 1*2^0
```

giving:

```text
32 + 8 + 4 + 1 = 45
```

But what about numbers like:

```text
3.14
0.5
0.1
123456.789
```

We need another representation.

---

# 15. Binary Representation of Fractions

Binary fractions work similarly to decimal fractions.

Decimal:

```text
123.456
```

uses:

```text
10^2  10^1  10^0  .  10^-1  10^-2  10^-3
```

Binary uses powers of 2:

```text
2^2  2^1  2^0  .  2^-1  2^-2  2^-3 ...
```

For example:

```text
0.101₂
```

means:

```text
1 * 2^-1
+ 0 * 2^-2
+ 1 * 2^-3
```

which is:

```text
1/2 + 1/8
= 0.625
```

Therefore:

```text
0.101₂ = 0.625₁₀
```

---

# 16. Not Every Decimal Fraction Has a Finite Binary Representation

This is extremely important.

Consider:

```text
0.5
```

Since:

```text
0.5 = 1/2 = 2^-1
```

it has an exact binary representation:

```text
0.1₂
```

But:

```text
0.1₁₀
```

does not have a finite binary representation.

Its binary expansion is:

```text
0.0001100110011001100110011...
```

and continues forever.

This is similar to how:

```text
1/3 = 0.333333333...
```

cannot be represented exactly using a finite number of decimal digits.

The important lesson is:

> A finite decimal fraction is not necessarily a finite binary fraction.

---

# 17. Why Floating-Point Numbers Are Needed

Suppose we want to represent:

```text
123456789
```

An integer representation works well.

But suppose we want:

```text
123456789.123456
```

We need both:

- a large magnitude
- a fractional part

We could use a fixed number of digits after the decimal point, but that creates a problem.

For example, if we always store:

```text
xxxxxxxx.xx
```

we can represent values with two decimal places, but not values requiring a much larger or smaller scale.

Scientific notation solves this conceptually.

For example:

```text
1234000000
```

can be written as:

```text
1.234 × 10^9
```

and:

```text
0.000001234
```

can be written as:

```text
1.234 × 10^-6
```

Floating-point representation applies the same basic idea using **base 2**.

---

# 18. Scientific Notation in Binary

A binary floating-point number can conceptually be written as:

```text
sign × significand × 2^exponent
```

For example:

```text
101.101₂
```

can be normalized:

```text
1.01101₂ × 2^2
```

Why?

Move the binary point two positions left:

```text
101.101
   ↓
1.01101 × 2^2
```

This gives us three pieces of information:

```text
sign
significand
exponent
```

IEEE 754 stores these pieces in a carefully designed bit layout.

---

# 19. IEEE 754

The most widely used floating-point standard is **IEEE 754**.

It defines:

- how floating-point values are encoded
- precision
- exponent representation
- zero
- positive and negative infinity
- NaN
- subnormal numbers
- rounding rules

Two formats are especially important in C++:

```text
float  → usually IEEE 754 binary32
double → usually IEEE 754 binary64
```

The C++ standard itself does not universally require IEEE 754 for every implementation, but mainstream modern systems commonly use it.

---

# 20. IEEE 754 Single Precision — `float`

A typical C++ `float` uses **32 bits**.

The layout is:

```text
┌──────┬───────────┬───────────────────────┐
│ Sign │ Exponent  │  Fraction / Mantissa  │
│ 1 bit│  8 bits   │        23 bits        │
└──────┴───────────┴───────────────────────┘
```

Total:

```text
1 + 8 + 23 = 32 bits
```

These fields have different jobs.

### Sign

```text
1 bit
```

### Exponent

```text
8 bits
```

### Fraction / Mantissa

```text
23 bits
```

The fraction is also commonly called the **fraction field** or **significand field** in explanations of IEEE 754.

---

# 21. Why Is the Fraction Only 23 Bits?

This is a subtle but important detail.

For normal IEEE 754 numbers, the significand is normalized so that it has the form:

```text
1.xxxxx...
```

The leading `1` is therefore implicit.

For example:

```text
1.101101 × 2^5
```

The leading `1` does not need to be stored because it is known to exist for normal numbers.

So the 23 stored fraction bits effectively provide **24 bits of significand precision**:

```text
implicit 1 + 23 stored bits
= 24 significant binary bits
```

This is sometimes called the **hidden bit** or **implicit leading 1**.

---

# 22. The Exponent Is Not Stored Directly

The exponent uses 8 bits.

You might expect it to store something like:

```text
-5
```

or:

```text
+10
```

directly.

Instead IEEE 754 uses a **bias**.

For single precision:

```text
exponent bits = 8
bias = 127
```

The stored exponent is:

```text
actual exponent + 127
```

For example, if the actual exponent is:

```text
+5
```

the stored exponent is:

```text
5 + 127 = 132
```

and:

```text
132 decimal = 10000100 binary
```

So the exponent field contains:

```text
10000100
```

---

# 23. Why Use a Bias?

Using a biased exponent allows exponent values to be compared more conveniently as unsigned bit patterns and avoids needing a separate sign bit for the exponent.

For normal single-precision numbers, stored exponent values:

```text
1 through 254
```

represent actual exponents:

```text
-126 through +127
```

The two extreme exponent encodings:

```text
00000000
11111111
```

are reserved for special cases.

---

# 24. IEEE 754 Normalized Number Formula

For a normal single-precision value:

```text
value = (-1)^sign × (1 + fraction/2^23) × 2^(E - 127)
```

where:

- `sign` = sign bit
- `E` = stored exponent interpreted as an unsigned integer
- `fraction` = 23-bit fraction field interpreted as an integer

The important conceptual form is:

```text
sign × significand × 2^exponent
```

---

# 25. Example: Representing 5.5 as a `float`

Let's encode:

```text
5.5
```

First convert to binary.

```text
5 = 101₂
0.5 = .1₂
```

Therefore:

```text
5.5 = 101.1₂
```

Normalize:

```text
1.011 × 2^2
```

So:

```text
sign = 0
actual exponent = 2
```

Single-precision exponent:

```text
2 + 127 = 129
```

129 in binary:

```text
10000001
```

Fraction after the implicit leading `1`:

```text
01100000000000000000000
```

Therefore the 32 bits are:

```text
0 | 10000001 | 01100000000000000000000
```

or:

```text
01000000101100000000000000000000
```

The important thing is not memorizing this bit pattern, but understanding where each part comes from.

---

# 26. IEEE 754 Double Precision — `double`

A typical C++ `double` uses **64 bits**.

Its layout is:

```text
┌──────┬────────────┬────────────────────────────────────────┐
│ Sign │ Exponent   │                Fraction                │
│ 1 bit│  11 bits   │                52 bits                 │
└──────┴────────────┴────────────────────────────────────────┘
```

Total:

```text
1 + 11 + 52 = 64 bits
```

Compared with `float`:

| Property | `float` | `double` |
|---|---:|---:|
| Total bits | 32 | 64 |
| Sign | 1 | 1 |
| Exponent | 8 | 11 |
| Fraction | 23 | 52 |
| Effective normal precision | 24 bits | 53 bits |
| Exponent bias | 127 | 1023 |

Again, these are the standard IEEE 754 binary32/binary64 characteristics commonly used by C++ implementations.

---

# 27. Double Precision Exponent

Double precision has:

```text
11 exponent bits
```

so its bias is:

```text
2^(11-1) - 1
= 1023
```

Therefore:

```text
stored exponent = actual exponent + 1023
```

For normal numbers, stored exponent values:

```text
1 through 2046
```

represent actual exponents:

```text
-1022 through +1023
```

---

# 28. Double Precision Formula

For a normal binary64 value:

```text
value =
(-1)^sign
× (1 + fraction/2^52)
× 2^(E - 1023)
```

The key difference from single precision is that double has:

```text
52 stored fraction bits
```

and therefore:

```text
53 bits of significand precision
```

because of the implicit leading `1`.

---

# 29. Float vs Double: What Does "Precision" Actually Mean?

This is a common point of confusion.

`double` does not simply mean:

> "The same number but twice as accurate."

It provides a larger representation with:

- more significand bits → much better precision
- more exponent bits → much larger range

Approximately:

```text
float  ≈ 7 decimal significant digits
double ≈ 15–17 decimal significant digits
```

These are approximate decimal precision figures, not exact universal limits for every operation.

The fundamental precision comes from the number of significant binary bits:

```text
float  → 24 bits
double → 53 bits
```

---

# 30. The Three IEEE 754 Categories

IEEE 754 does not use the same formula for every bit pattern.

The exponent field is especially important.

For binary32:

```text
Exponent = 00000000
Exponent = 00000001 ... 11111110
Exponent = 11111111
```

represent different categories.

---

# 31. Normal Numbers

When:

```text
exponent ≠ 0
and
exponent ≠ all 1s
```

the number is a **normal number**.

The significand is:

```text
1.fraction
```

and:

```text
value =
(-1)^sign
× (1.fraction)
× 2^(E-bias)
```

This is the main range of ordinary floating-point numbers.

---

# 32. Zero

When:

```text
exponent = 00000000
fraction = 00000000000000000000000
```

we get zero.

There are actually two representations:

```text
sign = 0 → +0
sign = 1 → -0
```

So IEEE 754 intentionally has both:

```text
+0
-0
```

Unlike two's-complement integers, floating-point arithmetic has signed zero because it is useful for certain numerical and mathematical operations.

---

# 33. Subnormal Numbers

When:

```text
exponent = 00000000
fraction ≠ 0
```

the value is **subnormal** (also called denormal in older terminology).

For these numbers, the implicit leading `1` is not used.

Instead, the significand behaves like:

```text
0.fraction
```

and the effective exponent is the minimum normal exponent.

For binary32:

```text
value =
(-1)^sign
× (0.fraction)
× 2^-126
```

Subnormal numbers allow IEEE 754 to represent values closer to zero than the smallest normal number.

This creates a gradual transition toward zero rather than an abrupt jump.

---

# 34. Infinity

When:

```text
exponent = all 1s
fraction = all 0s
```

we get infinity.

Two possibilities:

```text
sign = 0 → +∞
sign = 1 → -∞
```

Examples of operations that can produce infinity include sufficiently large overflow and, under IEEE 754 floating-point rules, division by zero such as:

```text
1.0 / 0.0
```

for floating-point operands.

---

# 35. NaN — Not a Number

When:

```text
exponent = all 1s
fraction ≠ 0
```

the value is **NaN**.

NaN means that the result is not an ordinary numerical value.

Examples can include invalid floating-point operations such as:

```text
0.0 / 0.0
```

or certain invalid operations involving infinities.

NaN is unusual because:

```cpp
NaN == NaN
```

is false under ordinary IEEE comparison semantics.

This is why checking for NaN is normally done using:

```cpp
std::isnan(x)
```

rather than:

```cpp
x == NaN
```

---

# 36. Complete IEEE 754 Layout

For single precision:

```text
Sign     Exponent       Fraction
 1 bit     8 bits         23 bits

┌───┬──────────┬─────────────────────────┐
│ S │ EEEEEEEE │ FFFFFFFFFFFFFFFFFFFFFFF │
└───┴──────────┴─────────────────────────┘
```

For double precision:

```text
Sign     Exponent          Fraction
 1 bit     11 bits           52 bits

┌───┬─────────────┬──────────────────────────────────────────────────────┐
│ S │ EEEEEEEEEEE │ FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF │
└───┴─────────────┴──────────────────────────────────────────────────────┘
```

---

# 37. Why Floating Point Is Called "Floating"

In a fixed-point representation, the binary point is conceptually fixed.

For example:

```text
101101.101
```

might always reserve three bits after the point.

In floating-point representation, the point can effectively move because we store a significand together with an exponent.

For example:

```text
1.011 × 2^2
```

and:

```text
1.011 × 2^-10
```

use the same significand but different scales.

Therefore the binary point effectively **floats**.

---

# 38. Why `0.1 + 0.2` Is Not Exactly `0.3`

This famous example follows directly from the representation.

Decimal:

```text
0.1
```

does not have a finite binary representation.

So a floating-point number stores the nearest representable binary value.

Likewise:

```text
0.2
```

is generally stored as an approximation.

When the computer calculates:

```cpp
0.1 + 0.2
```

it is really adding the stored approximations.

The result is therefore not guaranteed to be the exact mathematical value:

```text
0.3
```

For example, printing with sufficient precision can reveal a result near:

```text
0.30000000000000004
```

The exact displayed decimal depends on the type, implementation, and formatting.

The important lesson is:

> Floating-point arithmetic operates on representable approximations, not arbitrary real numbers.

---

# 39. Precision vs Range

Floating-point representation has two different concepts that should not be mixed.

## Range

How large or small a number can be.

Primarily influenced by:

```text
exponent bits
```

## Precision

How many significant digits/bits can be represented accurately.

Primarily influenced by:

```text
significand bits
```

So:

```text
more exponent bits → greater range

more significand bits → greater precision
```

`double` improves both relative to `float`.

---

# 40. Why Floating-Point Numbers Have Gaps

Floating-point numbers cannot represent every real number.

Even more importantly, the spacing between representable numbers is not constant.

Near zero, numbers can be very closely spaced.

As the magnitude grows, the gap between neighboring representable numbers becomes larger.

Conceptually:

```text
small numbers:

| | | | | | | | | | | |

large numbers:

|    |    |    |    |    |
```

This happens because the available significand precision is finite while the exponent changes the scale.

---

# 41. A Useful Mental Model

Think of floating-point representation as scientific notation with a fixed number of significant binary digits.

For example:

```text
1.101101 × 2^10
```

The exponent says:

> "How far should I scale this number?"

The significand says:

> "What digits are significant?"

The sign says:

> "Positive or negative?"

IEEE 754 essentially packs these three pieces into a fixed number of bits.

---

# 42. What Actually Happens When You Write `float x = 5.5f`?

Suppose we write:

```cpp
float x = 5.5f;
```

Conceptually:

### Step 1: Convert the number to binary

```text
5.5 = 101.1₂
```

### Step 2: Normalize it

```text
1.011 × 2^2
```

### Step 3: Determine the sign

Positive:

```text
S = 0
```

### Step 4: Encode the exponent

Actual exponent:

```text
2
```

Single-precision bias:

```text
127
```

Stored exponent:

```text
129
```

Binary:

```text
10000001
```

### Step 5: Store the fraction

The normalized value is:

```text
1.011
```

The leading `1` is implicit.

Stored fraction:

```text
01100000000000000000000
```

### Step 6: Combine

```text
0 | 10000001 | 01100000000000000000000
```

That 32-bit pattern is what represents the value.

---

# 43. What Happens When the Number Cannot Be Represented Exactly?

Suppose we have:

```cpp
float x = 0.1f;
```

The process is conceptually:

```text
decimal 0.1
      ↓
binary expansion
      ↓
infinite binary fraction
      ↓
only finite significand bits available
      ↓
round to a representable IEEE 754 value
      ↓
store the resulting bit pattern
```

So the stored value is very close to `0.1`, but generally not exactly `0.1`.

This is not a bug.

It is a consequence of finite binary representation.

---

# 44. Rounding

When an exact mathematical result lies between two representable floating-point values, IEEE 754 specifies rounding rules.

The default rounding mode on typical systems is:

```text
round to nearest, ties to even
```

This means the result is generally rounded to the nearest representable value, with a special rule when the exact value is exactly halfway between two candidates.

This helps reduce systematic rounding bias.

---

# 45. Integer vs Floating-Point Representation

The key differences can be summarized as follows.

| Feature | Integer | Floating Point |
|---|---|---|
| Main purpose | Whole numbers | Very large/small values with fractions |
| Representation | Binary magnitude / two's complement for signed integers | Sign + exponent + significand |
| Decimal point | Not applicable | Effectively moves |
| Precision | Exact within range | Limited |
| Range | Fixed and finite | Very large range |
| Fractional values | Not directly represented by ordinary integer type | Supported |
| Special values | Generally no NaN/Infinity | ±0, ±∞, NaN, subnormals |
| Rounding | Usually exact for representable integer operations | Frequently required |

---

# 46. The Big Picture

At the hardware level, everything eventually becomes bits.

For an integer:

```text
number
   ↓
binary representation
   ↓
fixed-width bit pattern
```

For a signed integer:

```text
number
   ↓
two's complement representation
   ↓
fixed-width bit pattern
```

For a floating-point number:

```text
number
   ↓
binary scientific notation
   ↓
sign + exponent + significand
   ↓
IEEE 754 encoding
   ↓
fixed-width bit pattern
```

---

# 47. The Most Important Things to Remember

## Integers

### Unsigned

For `n` bits:

```text
0 ... 2^n - 1
```

### Signed two's complement

For `n` bits:

```text
-2^(n-1) ... 2^(n-1)-1
```

Negative number:

```text
invert bits
+
add 1
```

Two's complement is preferred because:

- only one zero
- addition works naturally
- subtraction can be performed through addition
- hardware implementation is simpler
- no end-around carry is required

---

## Floating Point

IEEE 754 broadly uses:

```text
sign × significand × 2^exponent
```

### `float` / binary32

```text
1 sign bit
8 exponent bits
23 fraction bits
```

Effective normal precision:

```text
24 bits
```

Bias:

```text
127
```

### `double` / binary64

```text
1 sign bit
11 exponent bits
52 fraction bits
```

Effective normal precision:

```text
53 bits
```

Bias:

```text
1023
```

---

# 48. Final Mental Model

If you understand the following picture, you understand the core idea of computer number representation:

```text
                    MEMORY
                      │
                      ▼
   ┌─────────────────────────────────────┐
   │ 01000000 10110000 00000000 00000000 │
   └─────────────────────────────────────┘
                      │
          ┌───────────┴────────────┐
          │                        │
      INTEGER                 FLOATING POINT
          │                        │
          ▼                        ▼
   interpret bits as       interpret fields as
binary/two's complement  sign + exponent + fraction
          │                        │
          ▼                        ▼
     1085276160                   5.5 
```
The same set of bits `01000000 10110000 00000000 00000000` can represent either `1085276160` or `5.5`.

The bits themselves do not "know" that they represent `1085276160` or `5.5`.

The **type and representation rules give those bits meaning**.

That is the fundamental idea behind number representation in computers.