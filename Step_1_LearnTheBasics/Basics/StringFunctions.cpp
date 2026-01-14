#include <iostream>
#include <string>

using namespace std;

int main() {
    // C++ std::string Functions (from <string>) :- 
    // The std::string class provides methods to create, modify, search, and analyze strings.
    // These are member function and are used as string_name.function_name(arguments);

    /*
    🔹 1. Initialization / Basic Info
    a) size() / length() → number of characters currently in the string.

    b) empty() → true if string is empty i.e. if size == 0.

    c) capacity() → current allocated storage/memory size (may be larger than size()).

    d) resize(n) → resize(n) reduces or extends the string to n characters changing string size to n. 
    If n > string.size :- resize extends the size to n and capacity may also change. New chars default to \0.
    If n < string.size :- resize reduces the size to n. Only the first n characters are kept rest are discarded. 
    The capacity does not shrink automatically and capacity may remain the same as previous one.

    e) clear() → remove all characters (empties the string) but usually keeps the capacity intact.
    */
    string s = "Hello";
    cout << "Size : " << s.size() << endl;  // 5
    cout << "Is empty ? : " << s.empty() << endl; // false
    cout << "Capacity : " << s.capacity() << endl;
    s.resize(4);      // resize string, s becomes 'Hell'
    cout << "String s after resizing : " << s << endl;
    s.clear();        // now s = ""
    cout << "After clearing s becomes : " << s << "Is Empty ? : " << s.empty() << endl;

    /*
    🔹 2. Access Characters
    a) operator[] → access by index (no bounds check).
    b) at(i) → access by index (with bounds check).
    c) front() / back() → first and last character.
    */
    s = "World";
    cout << s.front() << s[1] << s.at(2) << s.at(3) << s.back() << endl; // World

    /*
    🔹 3. Modifiers
    a) append(str) / operator+= → add to string.
    b) push_back(ch) / pop_back() → add a new char at end / remove last char.
    c) insert(pos, str) → insert str at specified position.
    d) erase(pos, len) → erase some part of string of length 'len' starting from index position 'pos'.
    e) replace(pos, len, str) → replace string's content from 'pos' of length 'len' with new content str
    f) swap(str2) → swap contents.
    */
    s = "Hello";
    string t = " World";
    s.append(t);            // Hello World
    s += " !!";              // Hello World !!
    cout << s << endl;
    s.pop_back();           // Hello World !
    s.push_back('#');       // Hello World !#
    cout << s << endl;

    s.insert(0, "#! ");     // #! Hello World !#
    cout << s << endl;
    s.erase(0, 3);          // Hello World !#
    s.erase(11, 3);         // Hello World
    cout << s << endl;
    s.replace(6, 5, "Chat"); // Hello Chat
    cout << s << endl;
    s = "Hello"; t = "World";
    cout << "Before Swapping :- s : " << s << " __ t : " << t << endl;
    s.swap(t);
    cout << "After Swapping :- s : " << s << " __ t : " << t << endl;


    /*
    🔹 4. Substring Operations
    substr(pos, len) → extract substring strating from index 'pos' of length 'len'.
    
    substr function has this signature:- string substr(size_t pos = 0, size_t len = npos) const;
    pos → starting index (required), len → number of characters to extract (optional; default = string::npos)

    ✅ Key points:
    - Passing 1 parameter → substring from that index to the end of the string.
    - Passing 2 parameters → substring from pos of length len.
    - If pos > s.size() → throws out_of_range exception.
    */
    s = "OpenAI ChatGPT";
    string subs = s.substr(4, 7);
    cout << subs << endl; // AI Chat
    cout << s.substr(7) << endl; // ChatGPT 

    /*
    🔹 5. Search Operations
    a) find(str) → find is used to search for a substring or character inside a string. Returns first occurrence.
    b) rfind(str) → Works like find but searches from the end (reverse find). Returns last occurrence.
    c) find_first_of(chars) → finds first occurrence of any character in chars.
    d) find_last_of(chars) → same as find_first_of(chars) but from the end. finds last occurrence of any character in chars.
    e) find_first_not_of(chars) → Opposite of find_first_of — finds first character NOT in the given set.
    f) find_last_not_of(chars) → Opposite of find_last_of — finds last character NOT in the given set.

    ✅ Key points:
    - Use find when you need the position of a substring.
    - Compare with npos to check if it exists.
    - There are many variants (rfind, find_first_of, find_last_of, *_not_of) for flexibility.
    */

    /*
    🤔 What is size_t? 
    - size_t is an unsigned integer type used to represent sizes and counts.
    - It’s the type returned by sizeof(), string::size(), vector::size(), and other “size” functions.
    - Defined in <cstddef> (or indirectly via <string>, <vector>, etc.).
    --> Key characteristics
        | Property           | Description                                                 |
        | ------------------ | ----------------------------------------------------------- |
        | Signed/Unsigned    | Unsigned (cannot be negative)                               |
        | Typical usage      | Sizes, lengths, indices, counts                             |
        | Platform-dependent | Usually 32-bit on 32-bit systems, 64-bit on 64-bit systems  |
        | Maximum value      | Can hold the **largest possible object size** on the system |
    
    string::npos --> npos is a special constant representing “not found.”
    
    --> Why size_t instead of int?
        -- Strings, vectors, arrays can be very large.
        -- Using int (signed, usually 32-bit) may overflow for very big containers.
        -- size_t is guaranteed to be able to store any container’s size.
    */
    /*
    🤔 What is string::npos ?
    1. What is npos really?
    - In C++, std::string::npos is defined as :-  static const size_t npos = -1;
    - But size_t is unsigned, so how can it be -1?

    2. Unsigned integer behavior
    - In C++, assigning a negative number to an unsigned type wraps it around.
    - Specifically, for size_t (say 64-bit on your system): size_t x = -1;
    - So, Internally, x becomes: 2 ^ 64 − 1 = 18446744073709551615. 
    - That’s the largest possible value of size_t.

    3. Why is this useful for npos?
    - npos is used to indicate “not found.”
    - Since no valid index in a string/vector can be larger than size() - 1, 
    thus, using the largest possible size_t value is a safe “special value” for “not found.”
    - That’s why find() returns string::npos when it fails.

    4. Summary 
    | Concept                 | Why it works                                                    |
    | ----------------------- | --------------------------------------------------------------- |
    | `size_t npos = -1`      | Negative assigned to unsigned → wraps to max value              |
    | `find()` returns `npos` | Indicates “not found” using a value **no valid index can have** |
    | Comparison with `idx`   | Works naturally, because any valid index < npos                 |
 
    💡 Memory trick: You can think of npos as “all bits 1” in binary for size_t: 64-bit: 1111 1111 ... 1111
    That’s the largest possible size_t value.
    */


    s = "Hello World";
    size_t idx1 = s.find('o');        // 4 (first 'o')
    size_t idx2 = s.find('x');        // string::npos (not found)
    cout << "\'o\' found at index : " << idx1 << endl;
    cout << "\'x\' found at index : " << idx2 << endl;
    if (idx2 == string::npos) cout << "!! \'x\' does not exist in string s !!" << endl;
    cout << s.rfind('o') << endl;     // 7 (last 'o')
    cout << s.find_first_of("aeiou") << endl;  // finds first occurrence of any of characters from "aeiou" ... returns 1 ('e')
    cout << s.find_first_not_of(" ") << endl;  // returns 3 ('H') 


    /*
    🔹 6. Comparison Operations
    a) compare(str) → s1.compare(s2) will return 
    -- < 0 → s1 is lexicographically smaller than s2 
    -- 0 → s1 equals s2
    -- > 0 → s1 is lexicographically greater than s2
    analogically you can think of s1.compare(s2) as "s1 - s2".

    b) Relational operators (==, <, >, etc.) also work.
    */
    string s1 = "apple", s2 = "banana";
    cout << "\"apple\" compared to \"banana\" : " << s1.compare(s2) << endl; // negative (apple < banana)

    /*
    🔹 7. Conversion Functions
    a) stoi(str), stol(str), stod(str), etc. → convert to numbers.
    b) to_string(num) → number to string.
    */
    s = "123";
    int x = stoi(s);         // 123
    cout << x << endl;
    cout << to_string(45.6) << endl; // "45.600000"

    /*
    🔹 8. Iterators
    begin(), end() → forward iteration.
    rbegin(), rend() → reverse iteration.
    */
    s = "Hii, How are you ??";
    for (auto it = s.begin(); it != s.end(); it++)
        cout << *it;
    cout << endl;
}