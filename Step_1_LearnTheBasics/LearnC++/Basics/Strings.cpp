#include <iostream>
using namespace std;

int main() {
    // <-- Strings -->
    
    // General Constructor :- string variable_name(length, character);
    string new_str(10, '|');        // creates a string of size 10 filled with '|' characters

    // string s1,s2,s3;
    // cout << "Input s1 (A B): ";
    // /*cin >> reads input until it encounters whitespace (like spaces, tabs, or newlines).*/
    // cin >> s1;          // Input "A B", s1 will store only "A"
    // cout << "s1 : " << s1;
    // cout << "\nInput (C D) : ";
    // cin >> s1 >> s2 >> s3;    // Input "C D"
    // cout << "s1 : " << s1 << " s2 : " << s2 << " s3 : " << s3 << endl;      // s1 : B  s2 : C  s3 : D

    // // getline() reads input until a newline character is encountered, allowing it to capture entire lines of text, including spaces.
    // /*
    // getline() is used to read an entire line of text into a std::string. It’s part of <string> and <iostream> utilities.
    // Syntax : std::getline(input_stream, destination_string);
    // -- input_stream → usually cin, but can be any input stream (like ifstream for files).
    // -- destination_string → the std::string where the line will be stored.

    // Variant with custom delimiter: By default, getline stops at newline \n, but you can specify another delimiter: ex code --
    // string s;
    // getline(cin, s, ','); // reads until a comma is found

    // ⚡ Common issue: If you mix cin >> something; and then use getline(), the leftover newline from the first input might be read immediately.
    // Solution: clear the buffer with an extra cin.ignore(); before getline().
    // */
    // // If you use cin before getline(), add cin.ignore() to discard the leftover newline.
    // // cin.ignore() is used to ignore or clear one or more characters from the input buffer.
    // // Without cin.ignore(), getline() may skip input because of the leftover \n from cin
    
    // int x;
    // string str;
    // cout << "Enter an integer: ";
    // cin >> x;             // Takes an integer
    // cout << "Enter a sentence: ";
    // cin.ignore();         // Discards the '\n' left in the buffer
    // getline(cin, str);      // Now takes the full line
    // cout << "You entered: " << str << endl;


    // string s = "wizard";
    // int len1 = s.size();
    // int len2 = s.length();
    // // length(): Emphasizes the concept of string length, making code more intuitive for readability.
    // // size(): More generic and consistent with other container classes like vector, list, etc.
    // cout << len1 << '\t' << len2 << '\n';
    
    // for(int i = 0; i < len1; i++) {
    //     cout << s[i];
    // }

    // s[0] = 'W';
    // cout << '\n' << "s = " << s;

    // reserve() : It is used to request that the capacity of the string be at least enough to contain n characters. Used for both vectors & strings.
    /*
    By default, when you keep appending (+=) to a string, it sometimes runs out of space in memory.
    When that happens, the string allocates a bigger block of memory and copies all the characters over — this costs extra time.
    reserve(n) tells the string : “I know I’ll need space for at least n characters. Allocate that memory now.”
    Both std::string and std::vector grow dynamically — when they run out of capacity, they allocate a bigger block 
    (often about double the previous size), copy the old elements, and continue.
    reserve() just avoids those repeated reallocations when you already have a good idea of the final size.

    ⚡ Important notes:
    -- reserve() only affects capacity, not the actual size (length).
    -- The length (res.size()) is still 0 at the start, even after reserving.
    -- If you try to access res[i] before appending, that’s still invalid.
    */
    // capacity() : It tells how many elements the container can currently hold without reallocating. Used for both vectors & strings.
    // size() → actual number of characters stored (length). __ capacity() → total allocated space (≥ size).
    string str2;
    str2.reserve(100); // Pre-allocates memory for at least 100 characters
    cout << "\nCapacity after reserve(100): " << str2.capacity() << "\nSize after reserve(100): " << str2.size() << endl;

    /*
    What is String Concatenation Overhead ?
    In C++, when we use concatenation operator repeatedly inside a loop, the string may reallocate memory as it grows.
    Example, consider this code for copying the chars from a string to a sentence :- 
    string s = "";  for (char c : sentence) s += c;
    - Initially, s might have space for a few characters.
    - When it runs out of space, it allocates a bigger buffer, copies the old characters into it, and then adds the new one.
    - This reallocation + copying is the overhead.
    So, even though appending a single character is amortized O(1), multiple reallocations cause small extra cost overall.
    This is known as string concatenation overhead.

    | Term                   | Meaning                                               | Fix (if needed)         | Impact                          |
    | ---------------------- | ----------------------------------------------------- | ----------------------- | ------------------------------- |
    | Concatenation overhead | Cost from repeated resizing & copying when using `+=` | `ans.reserve(s.size())` | Very small — usually negligible |
    */

    // to_string(value) : a utility function that converts numeric values into a string representation. 
    // value → can be an int, long, long long, float, double, etc.
    int num = 73;
    float pi = 3.14159;
    string str_num = to_string(num); // Converts integer 73 to string "73"
    string str_pi = to_string(pi);   
    // Converts float 3.14159 to string "3.141590" -- By default, floating-point values are converted with 6 digits after the decimal.
    cout << "String representation of num: " << str_num << endl; // Outputs: String representation of num: 73
    cout << "String representation of pi: " << str_pi << endl;   // Outputs: String representation of pi: 3.141590
    
    return 0;
}