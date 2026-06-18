#include <iostream>
#include <sstream>  // required for ostringstream, istringstream & stringstream
#include <iomanip>  // required for setprecision
#include <vector>
using namespace std;

/*
Streams: A stream is a flow of data between a program and a source/destination.
Input Stream: Used to read data into the program. Example: cin (keyboard input)
Output Stream: Used to send data out of the program. Example: cout (console output)
String Streams (<sstream>): They work with strings instead of keyboard/console.

--------------------------------------------------------------------------------------------------------------------------
In C++, a stringstream is a class that allows you to treat a string as a stream. 
This means you can use the same input/output operators—like >> (extraction) and << (insertion)—that you normally use with 
cin and cout, but the data is read from or written to an internal string buffer instead of the console.
It is defined in the <sstream> header and is a bidirectional stream, meaning it supports both reading and writing.
--------------------------------------------------------------------------------------------------------------------------

>> Key Types of String Streams
There are three main variations depending on your needs:
1. std::istringstream: For input operations (reading from a string).
2. std::ostringstream: For output operations (writing to a string to build it).
3. std::stringstream: For both input and output.

>> How to use stringstreams ? 
To use stringstreams, we firstly need to create an object.
Ex- stringstream ss;      or      istringstream iss;          or        ostringstream oss;

-> What Happens Under the Hood when we do something like stringstream ss to create its object? 
• Instantiation: You instantiate a class to create an object, named ss in this case.
• Constructor Execution: The compiler automatically calls the default constructor for std::stringstream.
• Buffer Initialization: This constructor allocates and initializes an empty, private internal string buffer inside the 
  ss object to store your data.

>> Common Use Cases
• Data Conversion: It is a standard way to convert numbers to strings and vice-versa. 
  For example, inserting an int into a stringstream with << converts it to text.
• String Parsing: You can easily "tokenize" a sentence. By default, the >> operator extracts data separated by whitespace, 
  making it simple to split a sentence into individual words.
• Complex Formatting: It allows you to build a single string by combining multiple data types 
  (e.g., mixing strings, integers, and floats) into one buffer before final use.
*/

// ### Main methods/functions of stringstream, istringstream, and ostringstream
/*
1. str() : Get or set the internal string.
• str(): Returns a copy of the underlying string.
• str(new_string): Sets the content of the internal buffer to new_string.

  stringstream ss;
  ss << "hello";
  cout << ss.str(); // hello, ss.str() gives us the copy of string lying in the stream 
  ss.str("world");  // this will set the content of the internal buffer to "world"
  cout << ss.str(); // world

2. clear() : Resets the stream's error state (flags) (fail, eof, etc.) so you can reuse it.
Commonly used before reusing the stream.
  ss.clear();

3. << (insertion operator) : Writes data into stream. Used with stringstream & ostringstream.

  stringstream ss;
  ss << 10 << " " << 20;
  cout << ss.str(); // 10 20

4. >> (extraction operator) : Reads formatted data from stream. Used with stringstream & istringstream.

  stringstream ss("10 20");
  int a, b;
  ss >> a >> b;
  cout << a << " " << b;

5. getline() : Reads an entire line from stream.

  stringstream ss("hello world");
  string s;
  getline(ss, s);
  cout << s;

6. good() : Checks whether stream is usable.
  if (ss.good()) cout << "OK";

7. fail() : Checks whether last operation failed.
  if (ss.fail()) cout << "Failed";

8. eof() : Checks if end of stream reached.
  if (ss.eof()) cout << "End reached";

9. ignore() : Skips characters.
  ss.ignore(1); // skip one character
Very useful after reading numbers before getline.

10. peek() : Returns next character without removing it.
  char ch = ss.peek();

11. put() / get() : Character-level operations.
  ss.put('A');
  char ch;
  ss.get(ch);

12. seekg() / seekp() : Move read/write positions.
  ss.seekg(0); // move reading pointer to beginning
  ss.seekp(0); // move writing pointer to beginning

13. tellg() / tellp() : Get current read/write position.
  cout << ss.tellg();
  cout << ss.tellp();
*/

int main() {
    // <----------- Output String Stream (OSS) ----------->

    // ostringstream : Comes from the <sstream> header. It stands for output string stream.
    cout << "<----------- Output String Stream (OSS) ----------->\n\n";
    float pi = 3.14159;

    // Think of it as a "stream" (like cout) but instead of sending output to the console, it writes into a string buffer.
    ostringstream oss; // Create an output string stream object

    // UseCases --
    // 1. Conversion: Numeric Data → string
    oss << pi;                    // Insert float pi into the stream
    string pi_string = oss.str(); // Extract the string from the stream
    cout << "String representation of pi using ostringstream: " << pi_string << endl;       // pi_string = "3.14159"
    // using ostringstream for float doesn't limit to 6 decimal places like to_string() does.
    // ex- pi = 3.14159 doesn't become "3.141590"

    // 2. Build Complex Strings: ostringstream can be used to build complex strings with multiple data types.
    int age = 21;
    oss.str("");                  // Clear the stream's content ... reset the stream text.
    oss << "I am " << age << " years old." << endl;
    string myage = oss.str();
    cout << myage;                // "I am 21 years old."

    oss.str("");

    // Formatting floating-point numbers to a specific precision using ostringstream & setprecision & fixed
    /*
    The std::setprecision manipulator in C++
    Key Concepts
    • Header Required: must include <iomanip> to use setprecision.
    • Syntax: Used with stream insertion operator (<<) as 
      std::cout << std::setprecision(n) << value;, where n is an integer specifying the precision.
    • Behavior (Default): By default, setprecision(n) sets the total number of significant digits to be displayed, 
      counting both before and after the decimal point. 
      Ex- setprecision(5) means total five digits both before & after decimal.
    • Behavior with std::fixed: When used in conjunction with the fixed manipulator, 
      setprecision(n) sets the exact number of digits to appear after the decimal point. 
      This is the most common use case for formatting currencies or specific scientific data.
    • Rounding: setprecision performs rounding of the value to fit the specified precision.
      Ex -> cout << fixed << setprecision(3) << 3.14159;      // will print 3.142
    • Persistence: Once set, the precision setting affects all subsequent floating-point outputs on that stream 
      until it is changed again.
    • Does not affect integers: The manipulator only affects floating-point numbers (float, double, etc.). 
    */

    double pi_long = 3.1415926535;
    oss << fixed << setprecision(3) << pi_long;
    string s = oss.str();
    cout << "Pi upto 3 decimal places (using setprecision & fixed) : "  << s << '\n';   // Output: 3.142
    /*
    🔹 Difference :- ostringstream vs to_string()
    Feature	                                      |to_string()	                   |ostringstream
    Simple conversion	                            |✅ Yes	                        |✅ Yes
    Concatenate multiple values	                  |❌ (need +)	                    |✅ directly with <<
    Control formatting (precision, fixed , etc.)	|❌ No control	                  |✅ Full control
    Performance	                                  |Faster for single conversions 	 |Slightly heavier but more powerful
    */

    // <----------- Input String Stream (ISS) ----------->

    // istringstream : Stands for input string stream. Lets you extract values from a string as if you were reading from cin.
    cout << "\n<----------- Input String Stream (ISS) ----------->\n\n";

    // UseCases -- 
    // 1. Parse Data from the string : Extraction operator (>>) can be used to extract data from the string stream.
    // Parse integers from a string
    istringstream iss("2 3 5");         // Initialize istringstream with "2 3 5"
    int a, b, c;
    iss >> a >> b >> c; // Extract integers from the stream
    cout << "Extracted integers using istringstream -> a : " << a << ", b : " << b << ", c : " << c << endl;

    // Parse mixed data types from a string
    // clear for reuse : In last use-case, we had reached eof while extracting integers, so we need to use clear before re-use
    cout << "has reached eof : " << iss.eof() << '\n'; 
    iss.clear();      // clears eof, fail, bad flags
    iss.str("");      // resets the buffer content.. in this case, it initializes it to empty string thus clearing all data.

    string input = "19 3.14 Wizard";
    iss.str(input);            // Initialize stream content with input string's content

    int z;
    float f;
    string word;
    iss >> z >> f >> word; // Extracts 21, 3.14, and "Hello"
    cout << "Extracted using istringstream -> z : " << z << ", f : " << f << ", word : " << word << endl;

    // 2. Loop through all words in a sentence using istringstream
    string sentence = "I love C++ programming";
    istringstream iss3(sentence);
    while (iss3 >> word) {
        cout << word << '\n';
    }

    // <----------- String Stream (SS) ----------->

    // It’s a bidirectional string stream → can read (>>) and write (<<) into the same buffer.
    // Think of it as cin + cout, but working on a string instead of the console.
    cout << "\n<----------- String Stream (SS) ----------->\n\n";

    stringstream ss;

    // Example 1 : Build + Parse with the Same Stream
    // Write into the stream
    ss << 7 << " " << 3.14 << " Hello";
    // Read back from the same stream
    int x;
    double piee;
    ss >> x >> piee >> word;
    cout << x << " | " << piee << " | " << word << '\n';              // Output: 7 | 3.14 | Hello

    // Example 2: Split a String into Words (very common in CP!)
    ss.clear();
    ss.str("");
    
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