#include <iostream>
using namespace std;

int main() {
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