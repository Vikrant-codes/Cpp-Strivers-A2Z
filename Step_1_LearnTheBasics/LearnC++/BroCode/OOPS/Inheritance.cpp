#include <iostream>
using namespace std;

// <-- Inheritance -->
/*
Inheritance allows one class (derived / child) to reuse and extend another class (base / parent).
It supports code reuse and OOP design.

### Basic syntax
---------------------------------------
    class Parent {
    public:
        int x;
    };

    class Child : public Parent {
    public:
        int y;
    };

Usage:
    Child c;
    c.x = 10;   // inherited
    c.y = 20;
---------------------------------------

### Types of inheritance (C++)
    1. Single
    2. Multilevel
    3. Multiple
    4. Hierarchical
    5. Hybrid

1️⃣ Single Inheritance
Definition: A derived class inherits from one base class only.
--> Example - 
---------------------------------------------------
    class A { public: int x; };
    class B : public A {};  // B inherits from A
---------------------------------------------------

--> Inheritance Structure
---------
    A
    |
    B
---------
• Simple hierarchy
• Example: Car → Vehicle

2️⃣ Multilevel Inheritance
Definition: A class is derived from a derived class, forming a chain of inheritance.
--> Example - 
-----------------------------------------------------------------------
    class A {};
    class B : public A {};
    class C : public B {};  // C inherits from B → indirectly from A
-----------------------------------------------------------------------

--> Inheritance Structure
---------
    A
    |
    B
    |
    C
---------
• Forms a “chain”
• Example: Animal → Mammal → Dog

3️⃣ Multiple Inheritance
Definition: A class inherits from more than one base class.
--> Example - 
-----------------------------------------------------------------
    class A {};
    class B {};
    class C : public A, public B {};  // inherits both A and B
-----------------------------------------------------------------

--> Inheritance Structure
-------------
    A   B
     \ /
      C
-------------
• Can lead to diamond problem
• Example: FlyingCar inherits Car and Airplane .... Car + Airplane → FlyingCar

4️⃣ Hierarchical Inheritance
Definition: Multiple classes inherit from the same base class.
--> Example - 
--------------------------------------------------------
    class A {};
    class B : public A {};
    class C : public A {};  // both B and C inherit A
--------------------------------------------------------

--> Inheritance Structure
-------------
      A
     / \
    B   C
-------------
• Tree-like structure
• Example: Shape → Circle, Rectangle, Triangle

5️⃣ Hybrid Inheritance
Definition: Combination of multiple types of inheritance (two or more types of inheritance in one program).
--> Example - 
----------------------------------------------------------------------------------------------
    class A {};
    class B : public A {};
    class C : public A {};
    class D : public B, public C {};  // combines multiple + hierarchical → diamond problem
----------------------------------------------------------------------------------------------

--> Inheritance Structure
-------------
      A
     / \
    B   C
     \ /
      D
-------------
• Most complex inheritance .. The example combines hierarchical + multiple inheritance
• Example: FlyingCar inheriting Car and Airplane, with both inheriting Vehicle .. Vehicle → Car + Airplane → FlyingCar

>> Five types of inheritance:
    1. Single → one base, one derived
    2. Multilevel → chain of inheritance
    3. Multiple → one derived, multiple bases
    4. Hierarchical → one base, multiple derived
    5. Hybrid → combination of two or more types
*/

// <-- Diamond Problem -->
/*
The diamond problem occurs in multiple inheritance when:
1. A class 'A' is inherited by two classes 'B' and 'C'.
2. A class 'D' inherits from both 'B' and 'C'.

The inheritance structure looks like a diamond:
-------------
      A
     / \
    B   C
     \ /
      D
-------------
Problem:
• Class D now has two copies of A (one via B and one via C)
• If A has a member or function, D is ambiguous — compiler doesn’t know which A to use.

Example:-
-----------------------------------------
    class A {
    public:
        int x;
    };

    class B : public A {};
    class C : public A {};

    class D : public B, public C {};

    D d;
    d.x = 10;  // ❌ Error: ambiguous
-----------------------------------------

Solution: Use virtual inheritance:-
-----------------------------------------
    class B : virtual public A {};
    class C : virtual public A {};
-----------------------------------------
Now D has only one shared copy of A, solving the diamond problem.
*/

// <-- Access specifiers in inheritance, Constructor & destructor order, Method overriding -->
/*
### Access specifiers in inheritance
------------------------------------
    class Child : public Parent
------------------------------------
| Inheritance type | Parent public | Parent protected |
| ---------------- | ------------- | ---------------- |
| public           | public        | protected        |
| protected        | protected     | protected        |
| private          | private       | private          |
👉 Private members of parent are never directly accessible.

### Constructor & destructor order (important)
------------------------------------
    class A {
    public:
        A() { cout << "A"; }
        ~A() { cout << "~A"; }
    };

    class B : public A {
    public:
        B() { cout << "B"; }
        ~B() { cout << "~B"; }
    };

Output:
    AB~B~A
------------------------------------
• Constructors → base first
• Destructors → derived first

### Method overriding
-------------------------------
    class A {
    public:
        void show() {
            cout << "A";
        }
    };

    class B : public A {
    public:
        void show() {
            cout << "B";
        }
    };
-------------------------------
*/

class Animal {
public:
    string name = "";
    bool alive = true;

    void eat() {
        cout << name << " eats food ... NOM NOM NOM...\n";
    }
};

class Dog : public Animal {
public:
    Dog(string n) {
        name = n;
    }
    void bark() {
        cout << "The dog goes woof...\n";
    }
};

class Cat : public Animal {
public:
    Cat(string n) {
        name = n;
    }
    void meow() {
        cout << "The cat goes meow...\n";
    }
};


class Shape {
public:
    double area;
    double volume;
};

class Cube : public Shape {
public:
    double side;

    Cube(double side) {
        this->side = side;
        this->area = 6 * side * side;
        this->volume = side * side * side;
    }
};

class Sphere : public Shape {
public:
    double radius;

    Sphere(double radius) {
        this->radius = radius;
        this->area = 4 * 3.14 * radius * radius;
        this->volume = (4/3.0) * 3.14 * radius * radius * radius;
    }
};

int main() {
    /*
    Inheritance = A class can recieve attributes & methods from another class.
    Children classes inherit from a parent class.
    Helps to reuse similar code found within multiple classes
    */

    Dog dog("Bruno");
    cout << "name : " << dog.name << '\n';
    cout << "alive : " << dog.alive << '\n';
    dog.eat();
    dog.bark();
    /*
    Why does eat() print the child’s name?
    
    1. Inheritance copies members
        • Dog inherits all public and protected members from Animal.
        • So Dog has its own name member, inherited from Animal.
    
    2. Child constructor modifies inherited member
        Dog(string n) { name = n; }
        • This modifies the inherited name variable inside the Dog object.
        • There is no separate name in Dog; it’s the same as Animal::name in this object.
    
    3. eat() is inherited
        • Dog doesn’t define eat(), so Animal::eat() is used.
        • When eat() accesses name, it uses the name of the current object (this->name).
        • Since the constructor already set name = "Buddy", it prints "Buddy eats food...".
    
    Key concept -
     • Every Dog object contains all members of Animal (like name, alive).
     • Member functions of the parent class always operate on the object’s own data (this->name).
     • If a child changes inherited members, parent functions see the updated values.
    
    Visual analogy
        Animal object layout: [name | alive]
        Dog inherits Animal: [name | alive]
        Constructor sets name = "Buddy"
        eat() prints this->name → "Buddy"
    */

    Cat cat("Leo");
    cout << "name : " << cat.name << '\n';
    cout << "alive : " << cat.alive << '\n';
    cat.eat();
    cat.meow();

    cout << "\n\n";

    Cube cube(10);
    Sphere sphere(10);

    cout << "Cube --> Area = " << cube.area << " sq. units __ Volume = " << cube.volume << " cubic units" << '\n';
    cout << "Sphere --> Area = " << sphere.area << " sq. units __ Volume = " << sphere.volume << " cubic units" << '\n';

    return 0;
}