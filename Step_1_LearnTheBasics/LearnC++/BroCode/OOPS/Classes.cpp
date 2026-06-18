#include <iostream>
using namespace std;

// <-- Class -->
/*
• | A class is a user-defined data type that groups data (variables) and functions (methods) together.
• It’s the core concept of OOP (Object-Oriented Programming).

• Attributes : class attributes (also called data members) are variables that store data about an object's state.
• Methods : class methods (also called member functions) are functions that define an object's behavior and manipulate its data. 
Both attributes & methods collectively referred to as class members and are core components of OOP.

Similar to structs, the members of a class can be accessed using the dot operator (.) & arrow operator (->) (in case of pointers)

### Basic syntax
class className {
    attribute1;
    attribute2;
    ...
    method1;
    method2;
    ...
};

• The attributes are declared inside the class. By initializing the attributes, we can set default values for them.

Example - 
---------------------------------------------
class Student {
public:
    int id;
    string name;

    void print() {
        cout << id << " " << name << endl;
    }
};
---------------------------------------------
*/

// <-- Access specifiers -->
/*
>> What are access specifiers?
| Access specifiers control who can access class members (variables & functions).

In C++, there are three:-
1. public → Accessible from anywhere
2. private → Accessible only inside the class
3. protected → Used in inheritance

1. public
• Accessible from anywhere
• Used for interface (what the outside world can use)
----------------------------
    class Student {
    public:
        int roll;
        void display() {
            cout << roll;
        }
    };
----------------------------
✔ Accessible from main()
✔ Accessible by other classes

2. private
• Accessible only inside the same class
• Used to hide implementation details
------------------------
    class Student {
    private:
        int marks;
    };
------------------------
❌ NOT accessible from main()
❌ NOT accessible by derived classes
👉 Default access specifier in C++ classes is private

3. protected
• Accessible:
    - Inside the same class
    - Inside derived (child) classes
• NOT accessible from outside
------------------------
    class Student {
    protected:
        int age;
    };
------------------------
✔ Accessible in child classes
❌ Not accessible from main()

>> Real-world analogy
Think of a company:
- private → Internal documents (HR only)
- protected → Managers + company staff
- public → Company website info

### Using MULTIPLE access specifiers in ONE class

Rule (very important):
| All members declared after an access specifier belong to that specifier until another specifier appears.

Example:-
------------------------
    class Demo {
    private:
        int a;
        int b;

    public:
        int c;
        void show();

    protected:
        int d;

    public:
        void print();
    };
------------------------
How to read this:-
• a, b → private
• c, show() → public
• d → protected
• print() → public
👉 Access specifier does not apply to a single line,
👉 it applies to everything below it until changed.

Visual mapping (easy to remember)
------------------------------------------------
    class Example {
        int x;        // private (default)

    public:
        int y;        // public

    protected:
        int z;        // protected

    private:
        int w;        // private again
    };
------------------------------------------------
*/

class Human {
    public:
        // attributes - name & age
        string name;
        int age;
        // methods - eat(), work() & sleep()
        void eat() {
            cout << name << " is eating. \n";
        }
        void work() {
            cout << name << " is working. \n";
        }
        void sleep() {
            cout << name << " is sleeping. \n";
        }
};

int main() {
    /*
    Object = A collection of attributes and methods.
    They can have characteristics and could perform actions.

    • Attributes are characteristics of an object.
    • Methods are functions that an object can perform.

    Can be used to mimic real world items (ex Phone, Book, Dog).
    Objects are created from a class which acts as a "blue-print".

    Classes are blue-prints and objects are real-world instances (instance = an example or case (of something)) of objects.
    */

    Human p1;
    p1.name = "Alice";
    p1.age = 21;

    cout << p1.name << " is " << p1.age << " years old.\n";

    p1.eat();
    p1.work();
    p1.sleep();

    return 0;
}