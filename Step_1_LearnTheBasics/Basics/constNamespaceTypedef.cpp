#include <iostream>
#include <vector>
// using namespace std;  
using std::cout;
using std::endl;

// std is a standard namespace which has lots of entities like cout & string.
// using namespace std; :- helps to direcyly use the 'std' entities without using std::entity-name

// we can use some selected entity from a certain namespace with the statement using namespace-name::entity-name
// ex- using std::cout; using std::string;

/*
<-- Namespace -->
It provides a solution for preventing name conflicts in large projects. 
Each entity needs a unique name.
Namespace allows for identically named entities as long as the namespaces are different.
*/

namespace first{
    int x = 1;
}

namespace second{
    int x = 2;
}

/*
<-- typedef -->
A reserved keyword used to create an additional name (alias) for another data-type.
It is a new identifier for an existing type.
Helps with readability and reduce typos.
-- Common naming convention for typedef alias is to use '_t' at the end of identifier alias. --
'typedef' is now less preferred over 'using' becuase 'using' works better with templates.
*/
typedef std::string str_t;
// we can also use 'using alias-name = data-type' for alias
// 'using' is preferred over 'typedef' 
using ch_t = char;

int main() {
    int x = 0;
    cout << "x : " << x << endl;
    cout << "first-namespace x (first::x) : " << first::x << endl;
    cout << "second-namespace x (second::x) : " << second::x << endl;

    std::string s1 = "A normal string";
    str_t s2 = "String initialized with typedef alias str_t for std::string";
    cout << s1 << endl;
    cout << s2 << endl;

    ch_t c = 'X';
    cout << c << endl;

    /*
    The 'const' keyword specifies that a variable's value is constant. 
    It tells the compiler to prevent anything from modifying it. (read-only)
    -- Common naming convention for const is to use all uppercase letters for variable names -- 
    */
    const double PI = 3.14159;
    // PI = 3.14; 
    // changing a const variable's value raises error : "error : assignment of read-only variable 'PI'"

    cout << "Circumference : " << 2*PI*10 << endl;
    const int LIGHT_SPEED = 299792458;

    return 0;
}