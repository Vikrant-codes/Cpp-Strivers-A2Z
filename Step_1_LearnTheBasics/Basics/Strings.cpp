#include <iostream>
#include <sstream>  // required for ostringstream, istringstream & stringstream
#include <iomanip> // required for setprecision
#include <vector>
using namespace std;

int main() {
    // <-- Strings -->

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


    // ostringstream : Comes from the <sstream> header. It stands for output string stream.
    // Think of it as a "stream" (like cout) but instead of sending output to the console, it writes into a string buffer.
    ostringstream oss; // Create an output string stream object
    // conversion of numeric data type to string directly using ostringstream
    oss << pi; // Insert float pi into the stream
    string pi_string = oss.str(); // Extract the string from the stream
    cout << "String representation of pi using ostringstream: " << pi_string << endl;       // pi_string = "3.14159"
    // using ostringstream for float doesn't limit to 6 decimal places like to_string() does. ex- pi = 3.14159 doesn't become "3.141590"

    // You can use ostringstream to build complex strings with multiple data types
    int age = 21;
    oss.str(""); // Clear the stream's content
    oss << "I am " << age << " years old." << endl;
    string myage = oss.str();
    cout << myage;

    oss.str(""); // Clear the stream's content
    // Formatting floating-point numbers to a specific precision using ostringstream & setprecision 
    // setprecision(n) sets the total number of significant digits displayed in the output to n. #include<iomanip> is required
    double pi_long = 3.1415926535;
    oss << fixed << setprecision(3) << pi_long;
    string s = oss.str();
    cout << s;   // Output: 3.142
    /*
    🔹 Difference :- ostringstream vs to_string()
    Feature	                                                to_string()	                     ostringstream
    Simple conversion	                                    ✅ Yes	                        ✅ Yes
    Concatenate multiple values	                            ❌ (need +)	                    ✅ directly with <<
    Control formatting (precision, fixed, scientific, etc.)	❌ No control	                ✅ Full control
    Performance	                                            Faster for single conversions	  Slightly heavier but more powerful
    */


    // istringstream : Stands for input string stream. Lets you extract values from a string as if you were reading from cin.
    // Parse integers from a string
    istringstream iss;
    string input = "100 200 300";
    iss >> input; // Initialize the stream with the input string
    int a, b, c;
    iss >> a >> b >> c; // Extract integers from the stream
    cout << "\nExtracted integers using istringstream: " << a << " " << b << " " << c << endl;
    // Parse mixed data types from a string
    istringstream iss2("21 3.14 Hello");
    int z;
    float f;
    string word;
    iss2 >> z >> f >> word; // Extracts 21, 3.14, and "Hello"
    cout << "Extracted using istringstream: " << z << " " << f << " " << word << endl;
    // Loop through all words in a sentence using istringstream
    string sentence = "I love C++ programming";
    istringstream iss3(sentence);
    while (iss3 >> word) {
        cout << word << endl;
    }

    // stringstream : Comes from <sstream>. It’s a bidirectional string stream → can read (>>) and write (<<) into the same buffer.
    // Think of it as cin + cout, but working on a string instead of the console.
    stringstream ss;

    // Example 1 : Build + Parse with the Same Stream
    // Write into the stream
    ss << 42 << " " << 3.14 << " Hello";
    // Read back from the same stream
    int x;
    double piee;
    ss >> x >> piee >> word;
    cout << x << " | " << piee << " | " << word;              // Output: 42 | 3.14 | Hello

    // Example 2: Split a String into Words (very common in CP!)
    sentence = "I love competitive programming";
    ss.str(sentence); // Initialize with the input string
    vector<string> words;
    while (ss >> word) { // Extract words one by one
        words.push_back(word);
    }
    for (string w : words) {
        cout << w << " ";
    }
    cout << endl;

    // Example 3: Convert Number ↔ String (flexible version of to_string / stoi)
    num = 1234;
    // Number → String
    ss.clear(); // reset stream state
    ss << num;
    string str = ss.str();
    cout << "String: " << str << endl;  // Output: "1234"
    // String → Number
    ss.clear();        // reset stream state
    ss.str("5678");    // load new string
    ss >> x;
    cout << "Number: " << x << endl;    // Output: 5678

    /*
    🔄 Summary: sstream Family
    ostringstream → output to string (build strings).
    istringstream → input from string (parse strings).
    stringstream → can do both.
    */
    
    return 0;
}