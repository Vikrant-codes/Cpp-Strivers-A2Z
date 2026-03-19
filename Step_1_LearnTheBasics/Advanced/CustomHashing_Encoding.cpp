#include <bits/stdc++.h>
using namespace std;

// Hash Function and hash<int>
/*
🧠 What is a hash function?
A hash function converts a value into a number (called a hash) so it can be stored in a hash table.
    hash<int>()(5)  // gives some number
For basic types (like int, string, char, etc.), C++ already provides this. 
We can use the built-in 'hash' function to get the hash key of these basic data types .
But for data structures like:
- pair<int,int>
- vector<int>
👉 C++ says: “I don’t know how to convert this into a hash key
So we must tell it how to convert such data into hash-keys. (Using a custom hash function)

>> hash<int>()(5) : It is the built-in hash function for 'int' data types.

🔍 Break it into parts
1. hash<int>: It is a class (functor) from STL:    std::hash<int>
2. hash<int>(): This creates an object of the 'hash' class. 
    hash<int> obj;    is same as:    hash<int>()
3. This hash<int> is a functor so it contains an operator() method which gives us the 'hash-key' for a passed integer.
4. This operator allows the class to behave like functions and thus if 'obj' is an object of the 'hash' class 
    we can call the hash functor for some integer 'n' using obj(n)

    hash<int> obj;
    cout << obj(5);         // calls the 'operator' method of the class which returns the hash key generated
Same as:
    cout << hash<int>()(5);

>> 🔥 Why this works (important concept)
This works because std::hash is a functor (👉 A class that behaves like a function)

It overloads operator():
    size_t operator()(int x) const {
        return // some hash logic;
    }

So we can call it like: obj(5)

>> 🧩 In simple terms
| Code             | Meaning            |
| ---------------- | ------------------ |
| `hash<int>`      | hash function type |
| `hash<int>()`    | create hash object |
| `hash<int>()(5)` | hash value of 5    |

>>💡 Important note
We don’t care what exact number it returns
We only care that:
    Same input → same hash
    Different inputs → usually different hash

🚀 One-line intuition : hash<int>()(x) = “convert x into a hash-friendly number”

>> The internal implementation of hash class is somewhat like this (This is only the simplified version)
    template<>
    struct hash<int> {
        size_t operator()(int x) const {
            return static_cast<size_t>(x);
        }
    };

    🔍 Meaning
    - It’s a template specialization for int
    - It defines operator() → makes it callable like a function. Thus, we can do hash<int>() (integer_num)
    - For int, it basically just returns the value itself (converted to size_t)

- std::hash<T> = a class that knows how to hash type T. For int it is hash<int>, for char it is hash<char>
- operator() = the actual hash function, this function is called when we do hash<T>()(t_variable), where T is any data type
- For int → usually just returns the number (or slightly mixed)
*/

// Custom hash functions
/*
⚙️ Goal of a custom hash
Convert something like: {x, y} into one number (hash key)

✅ Simple custom hash for pair<int,int>
    struct pair_hash {
        size_t operator()(const pair<int,int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

🔍 Break it down
1. hash<int>()(p.first) : Converts p.first → hash number = a (say)
2. hash<int>()(p.second) : Converts p.second → hash number = b (say)
3. Combine them: a ^ (b << 1)
    << 1 → shift bits (to avoid overlap)
    ^ → XOR (mix values)
    👉 This creates a single unique-ish number

📦 Why combining is needed?
If we had done something like return a + b to combine them and get the hash key for the pair then, 
this would have created collision problems for us.
Example case - consider pairs {1, 2} and {2, 1}.
Assume we had done return a + b, then
    For {1, 2} : hash key = hash(1) + hash(2) = 1 + 2 = 3
    For {2, 1} : hash key = hash(2) + hash(1) = 2 + 1 = 3
This would have caused ❌ collisions, which is a sign of bad hashing (bad hashing = slow performance).

So, we need to combine them such that different pairs give different numbers.
*/


// ### Custom hash function use in STL (with unordered_map / unordered_set)
/*
This custom pair hash function can be used to hash pairs and thus help in using 
unordered_set / unordered_map of 'pair' data types.

Since, C++ don't have any default functions for hashing 'pairs', 
we can't directly use unordered_set / unordered_map having pair elements.
Because such data structures (like unordered_set / unordered_map) needs a hash function.

Thus, statements like 
    unordered_set<pair<int, int>> ❌
    unordered_map<pair<int, int>, int> ❌ 
are invalid. This is because C++ don't have any default hash function for pairs and 
unordered_set / unordered_map needs the hash function for its elements.

Thus, if we want to use pair as elements of unordered_set / unordered_map, 
we need to pass the custom hash function for the pair elements.
Thus, we need to use 
    unordered_set<pair<int, int>, pair_hash> ✅
    unordered_map<pair<int, int>, int, pair_hash> ✅
Now, this would work fine as we have passed the custom hash function which enables the map/set to hash pair elements.

If we were using set / map instead of unordered_set / unordered_map, we would have had no need for the custom pair hash fn.
This is because set/map don't need hash function for their elements
- set/map uses balanced BST (Red-Black Tree) → needs ordering (<)
- unordered_set/unordered_map uses hash table → needs hash function

Thus, Data structures like 'set' and 'map' works fine with pairs or vectors, i.e.,

    set<vector<int>> points; ✅
    set<pair<int,int>> points; ✅
    map<pair<int,int>, int> mp; ✅
    map<vector<int>, int> mp; ✅

These works fine because 'map' and 'set' uses ordering (<), not hashing.

But if we use 'unordered_set' or 'unordered_map', these are troublesome, since
unordered_set / unordered_map needs a hash function, 
and pair<int,int> / vector<int> doesn’t have a default hash in standard C++.
So, 
    unordered_set<vector<int>> points; ❌
    unordered_set<pair<int,int>> points; ❌
    unordered_map<pair<int,int>, int> mp; ❌
    unordered_map<vector<int>, int> mp; ❌
These gives error, as pair<int, int> and vector<int> doesn't have a default hash function.
Why Eror?
- unordered_set / unordered_map → uses hashing
- pair<int,int> / vector<int> → no built-in hash
So, to make it work this way, we need to use a custom hash function.

*/

struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        int a = p.first, b = p.second;      // get the pair elements
        auto hash_a = hash<int>()(a);       // get the corresponding hash key for the pair elements
        auto hash_b = hash<int>()(b);

        return hash_a ^ (hash_b << 1);      // Combine them in efficient manner
    }
};

struct vector_hash {
    size_t operator()(const vector<int>& v) const {
        size_t h = 0;
        for (int x : v) {
            h ^= hash<int>()(x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
/*
Goal of the custom vector hash fn -> Convert: {a, b, c} into a single number (h) such that:
- Order matters
- Collisions are minimized

Step 1: Start with base : size_t h = 0;
👉 Initial hash = 0

Step 2: Loop through vector -> For each element x, we update h

Step 3: Core formula: h ^= hash<int>()(x) + 0x9e3779b9 + (h << 6) + (h >> 2);

🧩 Each part explained
1. hash<int>()(x) 👉 Converts element x into a number
For int, usually: hash<int>()(x) ≈ x

2. 0x9e3779b9 = decimal (2654435769) = 2^32/ϕ, where ϕ is the golden ratio (👉 φ (golden ratio) ≈ 1.618) .
👉 It is a magic constant used to improve randomness
- Derived from golden ratio (ϕ)
- Helps in spreading values uniformly
- Prevents patterns

| "Magic Constants" : magic constants like 2654435769 etc. are used because 
| They are somehow unique, and look random.
| They can take part in algebraic operations repeatedly; 
| i.e. even after applying some specific operation (say multiplication or exponentiation) many times, 
| the "magic" value is still able to generate new values.

3. (h << 6) 👉 Left shift (multiply roughly by 64)
- Makes previous hash influence strongly 
- Adds order sensitivity

4. (h >> 2) 👉 Right shift
- Mixes higher bits into lower bits
- Avoids losing information

5. Whole inner expression : hash(x) + constant + shifted h
👉 This creates a mixed value using: current element & previous hash

6. XOR with h : h ^= ... 👉 Combines old hash with new mixed value

🧠 Big Picture
Each step does: h = mix(previous_hash, current_element)
So:
For {a, b, c}:
h = mix(0, a)
h = mix(h, b)
h = mix(h, c)
👉 Final h depends on: all elements & their order.

⚡ Why this works well
✔️ Order matters
{1,2} ≠ {2,1}
Because h keeps changing step by step.

✔️ Less collisions
Uses shifting + constant
Prevents simple cancellations like XOR-only
*/


// Encoding
/*
Encoding means:
| Convert multiple values (like a pair or vector) into a single number

So instead of storing pair<int, int> or vector<int> as set/map elements, we encode the pair/vector into a single number, 
and then using this resultant no. for hashing purposes. 
In this way, we can completely avoid creating and using custom hash functions.

✅ Basic idea (for pair)

Convert: (x, y) into: key = x * N + y

⚙️ Example
int x = 3, y = 7;
long long key = 1LL * x * 1000000000 + y;
Now, (3,7) → 3000000007

🔥 Why this works
Because: x * N + y
👉 ensures unique mapping if: 0 ≤ y < N
⚠️ Important condition
We must choose N such that: y < N

❌ Wrong example
    key = x * 10 + y
Then:
    (1,23) → 33
    (3,3)  → 33   ❌ collision

✅ Correct approach
Choose large N:
    long long key = 1LL * x * 1e9 + y;
👉 Safe if:
    y < 1e9

🔄 How to decode back?
    long long key = ...;

    int x = key / N;
    int y = key % N;

⚡ Why encoding is better than hashing
| Feature      | Encoding               | Custom Hash        |
| ------------ | ---------------------- | ------------------ |
| Simplicity   | ✅ Easy                 | ❌ Complex          |
| Performance  | ✅ Fast                 | ⚠️ Slight overhead |
| Collisions   | ❌ None (if done right) | ⚠️ Possible        |
| CP usability | ✅ Best                 | ⚠️ Secondary       |

⚠️ Limitation
Can overflow if:
- too many values
- or large constraints

Encoding = pack multiple values into one number using base multiplication
*/

int main() {
    hash<int> h;            // this creates a struct object for the struct 'hash<int>'
    cout << h(5);           // calls the operator function of the hash<int> struct taking parameter '5'
    
    cout << hash<int>() (5) << '\n';        // equivalent to firstly creating the object then calling the operator function

    pair<int, int> p = {1, 2};
    cout << pair_hash()(p) << '\n';
    cout << pair_hash()({2, 3}) << '\n';
    cout << pair_hash()({1, 3}) << '\n';

    vector<int> v = {1, 2, 3, 4, 5};
    cout << vector_hash()(v) << '\n';
    
    return 0;
}