#include <iostream>
#include <sstream>  // required for ostringstream, istringstream & stringstream
#include <iomanip>  // required for setprecision
#include <vector>
using namespace std;

// Streams: A stream is a flow of data between a program and a source/destination.
// Input Stream: Used to read data into the program. Example: cin (keyboard input)
// Output Stream: Used to send data out of the program. Example: cout (console output)
// String Streams (<sstream>): They work with strings instead of keyboard/console.

int main() {
    // <----------- Output String Stream (OSS) ----------->

    // ostringstream : Comes from the <sstream> header. It stands for output string stream.
    cout << "<----------- Output String Stream (OSS) ----------->\n\n";
    float pi = 3.14159;

    // Think of it as a "stream" (like cout) but instead of sending output to the console, it writes into a string buffer.
    ostringstream oss; // Create an output string stream object

    // conversion of numeric data type to string directly using ostringstream
    oss << pi; // Insert float pi into the stream
    string pi_string = oss.str(); // Extract the string from the stream
    cout << "String representation of pi using ostringstream: " << pi_string << endl;       // pi_string = "3.14159"
    // using ostringstream for float doesn't limit to 6 decimal places like to_string() does. 
    // ex- pi = 3.14159 doesn't become "3.141590"

    // You can use ostringstream to build complex strings with multiple data types
    int age = 21;
    oss.str(""); // Clear the stream's content
    oss << "I am " << age << " years old." << endl;
    string myage = oss.str();
    cout << myage;

    oss.str("");

    // Formatting floating-point numbers to a specific precision using ostringstream & setprecision & fixed
    /*
    The std::setprecision manipulator in C++
    Key Concepts
    • Header Required: You must include <iomanip> to use setprecision.
    • Syntax: Use it with the stream insertion operator (<<) as std::cout << std::setprecision(n) << value;,
      where n is an integer specifying the precision.
    • Behavior (Default): By default, setprecision(n) sets the total number of significant digits to be displayed, 
      counting both before and after the decimal point.
    • Behavior with std::fixed: When used in conjunction with the fixed manipulator, 
      setprecision(n) sets the exact number of digits to appear after the decimal point. 
      This is the most common use case for formatting currencies or specific scientific data.
    • Persistence: Once set, the precision setting affects all subsequent floating-point outputs on that stream 
      until it is changed again.
    • Rounding: setprecision performs rounding of the value to fit the specified precision.
    • Does not affect integers: The manipulator only affects floating-point numbers (float, double, etc.). 
    */

    double pi_long = 3.1415926535;
    oss << fixed << setprecision(3) << pi_long;
    string s = oss.str();
    cout << "Pi upto 3 decimal places (using setprecision & fixed) : "  << s << '\n';   // Output: 3.142
    /*
    🔹 Difference :- ostringstream vs to_string()
    Feature	                                                to_string()	                     ostringstream
    Simple conversion	                                    ✅ Yes	                        ✅ Yes
    Concatenate multiple values	                            ❌ (need +)	                    ✅ directly with <<
    Control formatting (precision, fixed, scientific, etc.)	❌ No control	                ✅ Full control
    Performance	                                            Faster for single conversions	  Slightly heavier but more powerful
    */

    // <----------- Input String Stream (ISS) ----------->

    // istringstream : Stands for input string stream. Lets you extract values from a string as if you were reading from cin.
    cout << "\n<----------- Input String Stream (ISS) ----------->\n\n";

    // Parse integers from a string
    istringstream iss("2 3 5");         // Initialize istringstream with "2 3 5"
    int a, b, c;
    iss >> a >> b >> c; // Extract integers from the stream
    cout << "Extracted integers using istringstream -> a : " << a << ", b : " << b << ", c : " << c << endl;

    // Parse mixed data types from a string
    // clear for reuse
    iss.clear();      // clears eof, fail, bad flags
    iss.str("");      // clears the buffer

    string input = "19 3.14 Wizard";
    iss.str(input);            // Initialize stream content with input string's content

    int z;
    float f;
    string word;
    iss >> z >> f >> word; // Extracts 21, 3.14, and "Hello"
    cout << "Extracted using istringstream -> z : " << z << ", f : " << f << ", word : " << word << endl;

    // Loop through all words in a sentence using istringstream
    string sentence = "I love C++ programming";
    istringstream iss3(sentence);
    while (iss3 >> word) {
        cout << word << '\n';
    }

    // <----------- String Stream (SS) ----------->

    // It’s a bidirectional string stream → can read (>>) and write (<<) into the same buffer.
    cout << "\n<----------- String Stream (SS) ----------->\n\n";

    // Think of it as cin + cout, but working on a string instead of the console.
    stringstream ss;

    // Example 1 : Build + Parse with the Same Stream
    // Write into the stream
    ss << 7 << " " << 3.14 << " Hello";
    // Read back from the same stream
    int x;
    double piee;
    ss >> x >> piee >> word;
    cout << x << " | " << piee << " | " << word << '\n';              // Output: 7 | 3.14 | Hello

    // Example 2: Split a String into Words (very common in CP !)
    ss.clear();     // clears eof, fail, bad flags
    ss.str("");     // clears the buffer
    
    cout << "Extracting words from a sentence into a vector --> ";

    sentence = "I love competitive programming";
    ss.str(sentence); // Initialize with the input string

    vector<string> words;
    // Extract words one by one
    while (ss >> word)
        words.push_back(word);
    // Now the words vector contains all the words from the sentence

    for (string& w : words)
        cout << w << " ";
    cout << '\n';

    // Example 3: Convert Number ↔ String (flexible version of to_string / stoi)
    int num = 1234;
    // Number → String
    ss.clear();     // reset stream state
    ss.str("");     // clears the buffer
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