#include <iostream>
using namespace std;

/*
<-- Function Templates -->
Function Templates describes what a function look like. 
• | A function template lets us write one function that works with different data types.

• Instead of writing the same function again for int, float, double, etc., 
   we write it once and C++ generates the needed versions automatically.

• Basic Syntax
-------------------------------------
template <typename T>
return_type function_name(parameters)
-------------------------------------
T → a placeholder type. C++ replaces it at compile time.

• It is a common naming convention to use uppercase characters like T, U, V etc for template typenames

>> Why do we need it?

- Without templates 👎
-------------------------------------
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}
-------------------------------------

- With templates 👍
-------------------------------------
template <typename T>
T add(T a, T b) {
    return a + b;
}
-------------------------------------
One function. Multiple types.

>> Templates with References (important for DSA)
-------------------------------------
template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}
-------------------------------------

Key Points to Remember
• Templates are compile-time features
• No runtime overhead
• Promotes code reuse
• Used extensively in STL (sort, vector, map)
*/

// These are 3 overloaded functions which return max of 2 values for different data-types (int, double & char)
int max_value(int x, int y) {
    return (x > y) ? x : y;
}

double max_value(double x, double y) {
    return (x > y) ? x : y;
}

char max_value(char x, char y) {
    return (x > y) ? x : y;
}

template <typename T>
T max1(T x, T y) {
    return (x > y) ? x : y;
}
// this max1 function will work for all data_types int, double, char etc but the two variables must be of the same type.
// If the two variables aren't of the same data_type, it will raise error

template <typename U, typename V>
auto max2(U x, V y) {
    return (x > y) ? x : y;
}


int main() {
    cout << max_value(13, 21) << '\n';
    cout << max_value(8.64, 5.67) << '\n';
    cout << max_value('a', 'A') << '\n';

    cout << "Using Function Templates -- \n ";
    cout << max1(13, 21) << '\n';
    cout << max1(8.64, 5.67) << '\n';
    cout << max1('a', 'A') << '\n';

    cout << "Comparing different data-types using function templates -- \n";
    cout << max2(13, 21.67) << '\n';
    cout << max2('a', 65) << '\n';
    cout << max2('a', 98.7) << '\n';

    return 0;
}