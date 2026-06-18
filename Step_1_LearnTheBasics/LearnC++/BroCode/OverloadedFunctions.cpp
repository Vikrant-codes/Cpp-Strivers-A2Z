#include <iostream>
using namespace std;

/*
Overloaded functions (C++)
Function overloading means having multiple fns with the same name in the same scope, but with different parameter lists. 
The compiler decides which function to call based on the arguments used.

Function signature
A function signature is what the compiler uses to uniquely identify a function.
It consists of:
• Function name
• Number of parameters
• Types of parameters
• Order of parameters
⚠️ Return type is NOT part of the function signature.

Example :-
void func(int x);
void func(double x);   // different signature → valid overloading

Invalid overloading:
int func(int x);
double func(int x);    // same signature → error
*/

void bakePizza();                                       // fn declaration
void bakePizza(string topping1);
void bakePizza(string topping1, string topping2);

int main() {
    bakePizza();
    bakePizza("Onion");
    bakePizza("Tomato", "Capsicum");

    return 0;
}

// fn definitions
void bakePizza() {
    cout << "Here is your pizza !!\n";
}

void bakePizza(string topping1) {
    cout << "Here is your " << topping1 << " pizza !!\n";
}

void bakePizza(string topping1, string topping2) {
    cout << "Here is your " << topping1 << " and " << topping2 << " pizza !!\n";
}