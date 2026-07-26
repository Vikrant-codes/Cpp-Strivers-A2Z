# Arrays and Strings in C++

## 1. Why Arrays Have a Fixed Size

An array stores elements of the **same type** in **contiguous memory**.

``` cpp
int arr[10];
```

If `sizeof(int) == 4` bytes:

-   Number of elements = 10
-   Size of each element = 4 bytes

Total memory:

    10 × 4 = 40 bytes

The compiler knows this size at compile time, so the array occupies one
fixed block of memory.

### Memory Layout

    +----+----+----+----+----+----+----+----+----+----+
    | 4B | 4B | 4B | 4B | 4B | 4B | 4B | 4B | 4B | 4B |
    +----+----+----+----+----+----+----+----+----+----+

Because every element has the same size, the compiler can calculate the
address of any element directly.

------------------------------------------------------------------------

## 2. Why `std::string` Is Different

`std::string` is **not** just a sequence of characters.

It is a **class** that manages character storage for you.

Conceptually, a string object contains:

-   A pointer to the character data
-   The current length (`size`)
-   The allocated storage (`capacity`)

A simplified representation is:

``` cpp
class string {
    char* ptr;
    size_t size;
    size_t capacity;
};
```

This is **not** the real implementation, but it is useful for
understanding how strings work.

------------------------------------------------------------------------

## 3. Where the Characters Are Stored

Example:

``` cpp
string s = "Hello";
```

Conceptually:

    Stack
    +---------------------------+
    | ptr --------------------- |------+
    | size = 5                  |      |
    | capacity = 15             |      |
    +---------------------------+      |
                                       |
    Heap                               |
    +----------------------------------+
    | H | e | l | l | o | \0 |
    +----------------------------------+

The **string object** is stored where it is declared.

The **characters** are usually stored in dynamically allocated memory
(the heap).

> **Note:** Modern C++ implementations often use **Small String
> Optimisation (SSO)**. For short strings (such as `"Hello"`), the
> characters may be stored directly inside the string object instead of
> on the heap. This is an optimisation and depends on the compiler and
> standard library implementation.

------------------------------------------------------------------------

## 4. Why Strings Are Dynamic

Unlike arrays, strings can grow and shrink.

``` cpp
string s = "Hello";

s += " World";
```

If the current capacity is sufficient:

-   Characters are appended directly.

Otherwise:

1.  A larger block of memory is allocated.
2.  Existing characters are copied.
3.  New characters are appended.
4.  The old memory is released.

This is what makes `std::string` dynamic.

------------------------------------------------------------------------

## 5. What Happens With an Array of Strings?

Consider:

``` cpp
string arr[10];
```

This creates **10 string objects**, not 10 character arrays.

If one `std::string` object occupies 32 bytes on your system:

    10 × 32 = 320 bytes

That 320 bytes stores only the **10 string objects**.

The actual text may require additional heap memory.

Example:

``` cpp
arr[0] = "Hi";
arr[1] = "This is a very long string.";
```

Conceptually:

    Array (Stack)

    +----------+----------+----------+-----+
    | string0  | string1  | string2  | ... |
    +----------+----------+----------+-----+
         |           |
         |           |
         v           v

    Heap

    "Hi"

    "This is a very long string."

Each string object manages its own character storage independently.

------------------------------------------------------------------------

## 6. Comparing Arrays of Integers and Arrays of Strings

### Integer Array

``` cpp
int arr[10];
```

Memory used:

    10 × sizeof(int)

All data is stored directly inside the array.

------------------------------------------------------------------------

### String Array

``` cpp
string arr[10];
```

Memory used:

    10 × sizeof(string)

This accounts only for the string objects.

The characters themselves may require additional dynamically allocated
memory.

------------------------------------------------------------------------

## 7. Key Takeaways

-   Arrays have a fixed size because every element has the same known
    size.
-   Array elements are stored contiguously in memory.
-   `std::string` is a class, not a primitive type.
-   A string object stores metadata (pointer, size, capacity) and
    manages its characters.
-   Characters are usually stored dynamically (or inside the object
    using Small String Optimisation).
-   An array of strings stores string **objects**, while each object
    manages its own text separately.
