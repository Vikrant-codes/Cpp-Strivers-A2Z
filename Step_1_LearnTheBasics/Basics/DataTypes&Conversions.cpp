#include<iostream>
using namespace std;

int main(){
    // Numbers : Integers & Floats
    /*
    <-- Integer Types -->
    Data Type	                        Size (bytes)	  Range (Signed)                                                Range (Unsigned)
    short / short int	                2	              -32,768 to 32,767	                                            0 to 65,535
    int	                                4	              -2,147,483,648 to 2,147,483,647	                            0 to 4,294,967,295 
    long / long int 	                4/8 (32 bits on Windows & 64 bits on Linux/MacOS 64-bit)            
    long long/long long int           	8                 -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807	    0 to 18,446,744,073,709,551,615
    
    <-- Floating-Point Types -->
    Data Type	            Size (bytes)	        Range	                                            Precision (decimal digits)
    float	                4	                    ±3.4e−38 to ±3.4e+38	                            6-7 digits
    double	                8	                    ±1.7e−308 to ±1.7e+308	                            15-16 digits
    long double	            16 (or 12)	            ±3.4e−4932 to ±1.1e+4932 (varies by compiler)	    18-19 digits      
    */

    // <-- Integers and Floats -->
    short sh = 32767;        // same as, short int s = 32767
    int i = 2147483647;
    long l = 2147483647L;
    long long ll = 9223372036854775807LL;
    /*
    --> long k = 1000L;              The 'l'/'L' suffix explicitly tells the compiler that 1000 is a long integer.
    --> long long k = 10000000LL;    The 'll'/'LL' suffix explicitly tells the compiler that 1000 is a long long integer.
    Integer literal defaults :- An integer literal like 123 is: int, if it fits, otherwise long, then long long.
    So, using suffix like 'L' or 'LL' can explicitly forces the compiler to make the literal long or long long.
    */

    float f = 3.14f;
    double d = 3.1415926535;
    long double ld = 3.141592653589793238;
    /*
    --> float k = 3.14f;      The 'f'/'F' suffix explicitly tells the compiler that 3.14 is a float literal.
    The value is stored directly as a 32-bit floating-point number without any conversion.
    --> float k = 3.14;       3.14 is a double literal by default (64-bit).
    The compiler implicitly converts the double to a float, which may involve a small performance cost and potential precision loss.
    */
   
    // <-- Char -->
    char ch = 'X';
    char ch2;
    cout << ch << '\n' << "Input for char datatype : ";
    // When you enter a space (' ') or any whitespace character after using cin >> x, 
    // it skips or ignores leading whitespaces, including space, tab, and newline.
    // Use cin.get(x) instead of cin >> x to read a single character, as it doesn't ignore whitespaces.
    // cin.get(x) : It reads a single character, including whitespaces, and doesn't skip them.
    cin.get(ch2);
    cout << ch2 << endl;

    int char_int = 'a';         // 97 .. the char value is automatically typecasted to the corresponding integer ASCII value
    cout << char_int << endl;

    // <-- Boolean -->
    bool bt = true;
    bool bf = false;

    // <-- String (objects that represents a sequence of text) --> 
    string s = "This is a string.";
    cout << s << endl;

    /*
    type conversion : conversion of a value of one data-type to another
    Implicit : automatic 
    Explicit : precede value with new data type, like - (int) / (float)
    */

    int x = 3.14;       // x is implicitly converted to integer data type even though 3.14 is a decimal number
    cout << x << endl;          // 3

    double x2 = (int) 3.14;         // 3.14 is explicitly converted to '3' which is then assigned to x2 variable
    cout << x2 << endl;

    char c = 97;                    // 97 is implicitly converted to char which is 'a' in ASCII
    cout << c << " & " << (char) 122 << endl;
    // (char) explicitly converts 122 to 'char'. 122 corrseponds to the character 'z' 

    int marks = 47;
    int total = 50;
    double perc = marks/total * 100;        // perc = 0
    // since marks & total are both integers, thus marks/total (= 0.98) also gets implicitly converted to integer (= 0)
    cout << "Percentage : " << perc << endl;

    double perc2 = marks/(double)total * 100;
    // explicitly convert total to double data type so that the result remains double and is not imoplicitly converted to int
    cout << "Percentage : " << perc2 << endl;

    return 0;
}