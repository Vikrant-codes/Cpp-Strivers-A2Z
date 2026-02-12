#include <iostream>
using namespace std;

// <-- Constructor -->
/*
| A constructor is a special member function of a class that is automatically called when an object is created.

• It is a special method that is automatically called when an object is instantiated (represented as or by an instance).
• Useful for assigning values to attributes as arguments.

### Key properties of constructors
    • Same name as the class
    • No return type (not even void)
    • Used to initialize data members
    • Called once per object

--------------------------------------------------
1. Default constructor
Called when no arguments are passed.

    class Student {
    public:
        int id;

        Student() {
            id = 0;
        }
    };

    Student s;   // default constructor called

2. Parameterized constructor
Used when values are passed at object creation.

    class Student {
    public:
        int id;
    
        Student(int x) {
            id = x;
        }
    };
    
    Student s(10);
--------------------------------------------------

### Constructor Initializer List (IMPORTANT)

Syntax:
    Constructor(parameters) : member1(value1), member2(value2) {}

Example:
    Student(int id, string name)
        : id(id), name(name) {}


>> What is this syntax?

The part after ':' is called the **initializer list**.
It initializes data members directly when the object is created, before the constructor body executes.

>> How it works internally

Without initializer list:
    Student(int id) {
        this->id = id;
    }

Steps:
    1. id is first default-initialized
    2. then assigned a new value

With initializer list:
    Student(int id) : id(id) {}

Steps:
    1. id is directly initialized with value

So initialization happens only once.


>> Why initializer list is more efficient

• Avoids extra default initialization + assignment
• Direct construction of members
• Required for:
    - const data members
    - reference members
    - objects without default constructors

Example:
    const int id;   // must use initializer list


>> Difference from constructor delegation

Initializer list:
    Student(int x) : id(x) {}
    --> initializes members

Constructor delegation:
    Student(int x) : Student(x, "Unknown") {}
    --> calls another constructor

>> Key takeaway
Initializer list = direct member initialization
Constructor body assignment = initialize then assign

--------------------------------------------------
>> Why constructors are important
• Prevent uninitialized variables
• Guarantee object starts in a valid state
• Centralize initialization logic

--------------------------------------------------
<-- The `this` keyword -->
| this is a pointer to the current object that called the member function.

>> Why `this` is needed
When data members and parameters have the same name.
------------------------------
    class Student {
    public:
        int id;

        Student(int id) {
            this->id = id;
        }
    };
------------------------------

Without `this`:
    id = id;   // ❌ both refer to parameter

With `this`:
    this->id = id;   // ✅ object member = parameter

>> What `this` actually is
• Type: Student* ... (pointer to object)
• Points to the current object in memory

>> Constructor without `this`
If names are different:
-------------------------
    Student(int x) {
        id = x;
    }
-------------------------
`this` is optional here.

### Key takeaways
    • Constructor initializes an object
    • Automatically called at object creation
    • this points to the calling object
    • Used to resolve name conflicts and for method chaining
*/

class Student{
public:
    int id;
    string name;
    int age;
    char gender;        // 'M' for Male, 'F' for female

    // Constructor
    Student( int id, string name, int age, char gender) {
        // `this` keyword used when parameters and attributes have same name
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
    }
};

class Car{
public:
    string maker;
    string model;
    int year;
    string color;

    // Constructor initializer list
    Car(string mk, string md, int y, string c) : maker(mk), model(md), year(y), color(c) {
        // constructor body can be empty
        // members already initialized
    }

};

int main() {
    Student s1(1, "Alice", 21, 'M');
    Student s2(2, "Blake", 20, 'F');

    cout << s1.name << " -> id : " << s1.id << " _ age : " << s1.age << " _ gender : " << s1.gender << '\n';
    cout << s2.name << " -> id : " << s2.id << " _ age : " << s2.age << " _ gender : " << s2.gender << '\n';

    Car car1("Porsche", "911 GT3", 2021, "Blue");
    Car car2("BMW", "M8 Competition", 2025, "Green");

    cout << car1.maker << " " << car1.model << " _ year : " << car1.year << " _ color : " << car1.color << '\n';
    cout << car2.maker << " " << car2.model << " _ year : " << car2.year << " _ color : " << car2.color << '\n';

    return 0;
}