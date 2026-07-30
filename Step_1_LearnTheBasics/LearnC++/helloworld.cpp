#include <iostream>
// iostream is a header file that contains functions for basic input & output operations

int main() {
    // This is a comment
    /*
        This 
        is
        a
        multi-line
        comment
    */

    std::cout << "Hello World!!" << std::endl;
    std::cout << "C++ is love 🩵" << '\n';
    // std::endl is for newline .... same as '\n', but, std::endl flushes the output buffer

    /*
    endl : Inserts a newline (\n) & Flushes the output buffer
    Flushing the output buffer = forcing all pending output to be written immediately to the screen (or file).
    What is an output buffer?
        - When you do cout << "Hello";, C++ does not print instantly.
        - It stores "Hello" in a buffer (temporary memory).
        - The buffer is printed later for efficiency
    */
    // using endl for newline is thus not efficient as flushing takes some time. Use endl only when you need immediate output

    /*
    What can go wrong if endl is NOT used?
    1️⃣ Interactive programs (most important case)
    If the judge/program is waiting for your output before responding, buffered output can break the logic.
    ❌ Without flush:
        cout << "1\n";   // stays in buffer
        // judge never sees "1" → program hangs
        cin >> x;
    ✅ With endl or flush:
        cout << "1" << endl;  // flushed immediately
        cin >> x;

    2️⃣ Program crashes before buffer flush
    Buffered output may never appear.
    ❌
        cout << "Before crash\n";
        // segmentation fault here
    You might see nothing printed.
    ✅
        cout << "Before crash" << endl; // flushed
    Useful during debugging.

    3️⃣ Output must appear before input prompt
    If output isn’t flushed, user won’t see the prompt.

    When DO you need endl?
    Use it only when at least one is true:
    ✔ Interactive problem
    ✔ Prompt must appear immediately
    ✔ Debugging crashes
    ✔ Explicitly need flush behavior

    When you should NOT use endl 🚫
    - Normal competitive programming
    - Inside loops
    - Printing large output
    - Any performance-sensitive code
    */
    
    return 0;
}