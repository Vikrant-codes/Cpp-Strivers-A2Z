#include <iostream>
using namespace std;

/*
Local Variables: 
• Declared inside a function or block {}
• Accessible only within that block
• Gets destroyed when the block/function ends

Global Variables: 
• Declared outside all functions
• Accessible throughout the program
• Exists for the entire program lifetime

Scope Resolution Operator (::)
Used to access a global variable when a local variable has the same name, or to access class members, namespaces, etc.

Key Points
• Local variables override global variables inside their scope
• :: explicitly refers to the global scope
• Syntax: ::variableName

<- We should try to avoid using global variables as these pollutes the global namespace and are less secure (can be modified) ->
*/

int myNum = 1;              // global variable

void printNum() {
    int myNum = 2;          // local variable of printNum fn
    cout << "myNum : " << myNum << '\n';

    cout << "Global myNum : " << ::myNum << '\n';
    // :: is the scope resolution operator, which is used to access the global variable 
    // to avoid confusion due to local variable having same name
}

int main() {
    cout << "Global myNum : " << myNum << '\n';
    // since the main fn doesn't have any myNum variable defined yet,
    // so using myNum means we will be using the global myNum variable

    int myNum = 3;          // local variable of main fn
    // this local variable has same name as global one, so inside this block the local one will have more priority 
    // and thus using myNum means we are accessing the local variable unless we use (::) operator to access global one.
    cout << "myNum : " << myNum << '\n';

    printNum();

    return 0;
}