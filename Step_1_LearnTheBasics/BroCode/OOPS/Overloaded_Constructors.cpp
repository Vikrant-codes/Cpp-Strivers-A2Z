#include <iostream>
using namespace std;

// <-- Overloaded Constructors -->
/*
| Overloaded constructors mean having multiple constructors in the same class with different parameter lists.
The compiler chooses which constructor to call based on the arguments passed while creating the object.

Overloaded constructors = multiple constructors with same name but different parameters 
It allows for varying arguments when instantiating an object.

Overloaded constructors allows for multiple objects of same class with varying number of attributes.

Example - 
-----------------------------------------------------------
class Student {
public:
    int id;
    string name;

    Student() {
        id = 0;
        name = "NA";
    }

    Student(int i) {
        id = i;
        name = "NA";
    }

    Student(int i, string n) {
        id = i;
        name = n;
    }
};

Student s1;                 // calls Student()
Student s2(10);             // calls Student(int)
Student s3(10, "Rahul");    // calls Student(int, string)
-----------------------------------------------------------

### Constructor delegation (C++11)
- One constructor can call another constructor of the same class.
---------------------------------------------
class Student {
public:
    Student() : Student(0, "NA") {}

    Student(int i) : Student(i, "NA") {}

    Student(int i, string n) {
        id = i;
        name = n;
    }

private:
    int id;
    string name;
};
---------------------------------------------

>> Why overloaded constructors are useful
    • Different ways to create objects
    • Avoid uninitialized data
    • Cleaner object creation
    • Improves usability of the class

>> Rules to remember
    • Constructors can be overloaded
    • They must differ in number or type of parameters
    • Return type is not considered
    • Only one constructor runs per object

>> Key takeaway
    • Overloaded constructors = multiple ways to initialize objects
    • Compiler decides based on arguments
    • Constructor delegation keeps code clean
*/

class Pizza{
public:
    string topping1;
    string topping2;

    Pizza() {

    }
    Pizza(string tp) {
        topping1 = tp;
    }
    Pizza(string tp1, string tp2) {
        topping1 = tp1;
        topping2 = tp2;
    }
};

int main() {
    Pizza my_pizza1;                            // Pizza with no toppings
    Pizza my_pizza2("Onion");                   // Pizza with 1 topping
    Pizza my_pizza3("Tomato", "Capsicum");      // Pizza with 2 toppings

    cout << "my_pizza1 toppings : " << my_pizza1.topping1 << " & " << my_pizza1.topping2 << '\n';
    cout << "my_pizza2 toppings : " << my_pizza2.topping1 << " & " << my_pizza2.topping2 << '\n';
    cout << "my_pizza3 toppings : " << my_pizza3.topping1 << " & " << my_pizza3.topping2 << '\n';

    return 0;
}