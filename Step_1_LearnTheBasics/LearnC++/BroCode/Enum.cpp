#include <iostream>
using namespace std;

// enum (enumeration)
/*
| An enum (enumeration) is a user-defined type that assigns names to integer constants.

enum: user-defined data type that consists of paired named-integer constants.
The values assigned are constants and can't be changed later.

>> Basic Syntax 
enum enum_name { name1, name2, ..... };

• If custom values aren't assigned to the enum names, then by default the values are 0, 1, 2, ... 
Thus default values: name1 = 0, name2 = 1, ...

### Assign custom values
enum Status {
    SUCCESS = 1,
    FAILURE = 0,
    PENDING = -1
};

### Values continue automatically:
enum Num {
    A = 1,
    B,   // 2
    C    // 3
};

• We can also use the names defined in enum independently in the code. These names will correspond to their assigned values.  

### Why enums are used
✔ Readable code (no magic numbers)
✔ Fixed set of values
✔ Very common in switch cases and states
*/

enum Day {sunday, monday, tuesday, wednesday, thursday, friday, saturday};
// default values are implicitly assigned which are 0, 1, 2, ... and so on

enum Colors {Violet = 1, Indigo, Blue, Green, Yellow, Orange, Red};

int main() {
    
    Day today = thursday;

    // we can either use the names or the integer values for the switch-cases
    switch(today) {
        case sunday:
            cout << "It's Sunday! \n";
            break;
        case 1:
            cout << "It's Monday! \n";
            break;
        case 2:
            cout << "It's Tuesday! \n";
            break;
        case wednesday:
            cout << "It's Wednesday! \n";
            break;
        case 4:
            cout << "It's Thursday! \n";
            break;
        case friday:
            cout << "It's Friday! \n";
            break;
        case saturday:
            cout << "It's Saturday! \n";
            break;
    }

    cout << "\n-- Rainbow Colors Positions -- \n";
    cout << "VIOLET : " << Violet << '\n';
    cout << "INDIGO : " << Indigo << '\n';
    cout << "BLUE : " << Blue << '\n';
    cout << "GREEN : " << Green << '\n';
    cout << "YELLOW : " << Yellow << '\n';
    cout << "ORANGE : " << Orange << '\n';
    cout << "RED : " << Red << '\n';

    return 0;
}