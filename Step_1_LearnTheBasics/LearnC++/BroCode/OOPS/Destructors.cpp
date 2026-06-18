#include <iostream>
using namespace std;

// <-- Destructor -->
/*
| A destructor is a special member function of a class that is automatically called when an object is destroyed.
• It is mainly used to free resources.

>> Key properties -
    • Name is same as class, prefixed with ~
    • No parameters
    • No return type
    • Only one destructor per class (cannot be overloaded)

Example - 
----------------------------------
    class Student {
    public:
        ~Student() {
            cout << "Destroyed";
        }
    };
----------------------------------

### When is a destructor called?

1. Stack object
---------------------------------------
    void func() {
        Student s;
    }   // destructor called here
---------------------------------------
Called when object goes out of scope.

2. Heap object
---------------------------------------
    Student* s = new Student();
    delete s;   // destructor called
---------------------------------------
If delete is not used → memory leak.

3. Program termination
All remaining objects are destroyed automatically.

>> Why destructors are important
    • Release dynamic memory
    • Close files
    • Free resources (network, locks, etc.)
    • Prevent memory leaks

Example with dynamic memory -
---------------------------------------
    class Array {
        int* arr;
    public:
        Array(int n) {
            arr = new int[n];
        }

        ~Array() {
            delete[] arr;
        }
    };
---------------------------------------

Destructor order (important) -
---------------------------------------
    class A {
    public:
        ~A() { cout << "A"; }
    };

    class B {
        A a;
    public:
        ~B() { cout << "B"; }
    };

    Output:
    BA
---------------------------------------
➡ Class destructor runs first, then its members.

### Destructor vs constructor
| Constructor           | Destructor           |
| --------------------- | -------------------- |
| Creates object        | Destroys object      |
| Initializes resources | Releases resources   |
| Can be overloaded     | Cannot be overloaded |

>> Key takeaways
    • Destructor cleans up resources
    • Automatically called
    • One per class
    • Critical when using new

### If we don't create destructors, then the memory is not released?
Short answer: No.

>> What does get released automatically
If you don’t write a destructor, C++ still:
    • Destroys the object
    • Releases stack memory
    • Calls destructors of member objects automatically
So this is safe:
-------------------------------------------
    class A {
        int x;
    };

    void f() {
        A a;   
    } // memory is released automatically
-------------------------------------------

>> What does NOT get released automatically
C++ does NOT free memory you allocated manually with new.
--------------------------------
    class A {
    public:
        int* p;
        A() {
            p = new int(10);
        }
    };
--------------------------------
If you don’t write a destructor:
--------------------------------
~A() {
    delete p;
}
--------------------------------
👉 p causes a memory leak.

>> Key rule (very important)
• Stack memory → auto released
• Heap memory (new) → YOU must release (delete)
Destructor is where you do that.

❌ No destructor ≠ no memory release
✅ No destructor + no new → totally fine
❌ No destructor + new → memory leak

| We need to write a destructor only when our class owns dynamic resources, most commonly memory allocated with new.

Precise rule
❌ No `new` in class → no destructor needed
✅ new / dynamic resource → destructor required

| Destructor = cleanup for resources the class manually owns
*/

class Student {
public:
    int id;
    string name;

    // Destructor
    ~Student() {
        cout << "Student object Destroyed ! \n";
        // no need to delete anything as no dynamic variable exists..
    }
};

class XYZ {
public:
    int *p;
    XYZ() {
        p = new int(100);
    }

    ~XYZ() {
        cout << "XYZ object Destroyed ! \n";
        delete p;       // need to delete the dynamically alloted space 
    }
};

int main() {
    Student s;
    XYZ xyz;
    
    return 0;
}