#include <iostream>
using namespace std;

// <-- Getters & Setters -->
/*
• Getters and setters are public functions used to access and modify private data members of a class safely.
• They are a core part of encapsulation.
| getter = function that makes a private attribute READABLE
| setter = function that makes a private attribute WRITABLE

Abstraction: hiding unnecessary data from outside a class
Encapsulation: keeping data safe inside a class.

Abstraction: What we show to the outside world.
Encapsulation: What we hide and protect inside the class.

>> Naming convention
• Getter: getVariableName()
• Setter: setVariableName()
This is standard practice.

### Basic example -
--------------------------------
    class Student {
    private:
        int age;

    public:
        // setter
        void setAge(int a) {
            if (a >= 0) {
                age = a;
            }
        }

        // getter
        int getAge() const {
            return age;
        }
    };

Usage:
    Student s;
    s.setAge(20);
    cout << s.getAge();
--------------------------------

### Getter marked const (important)
-----------------------------
    int getAge() const {
        return age;
    }
-----------------------------
const ensures:
• Getter does not modify object
• Can be called on const objects
If we try to modify an attribue inside a const getter, we would get error.
    error : assignment of member 'className::memberName' in read-only object

>> Key takeaways
    • Getters/setters enforce encapsulation
    • Setters can validate data
    • Getters are usually const
    • Preferred over public variables
*/

class Stove{
private:
    int temperature = 0;

public:
    // using setter function inside Constructor to set the private attribute
    Stove(int temperature) {
        setTemperature(temperature);
    }

    // getter
    int getTemperature() const{
        // temperature = 10;
        // error: assignment of member 'Stove::temperature' in read-only object
        return temperature;
    }

    // setter
    void setTemperature(int temperature) {
        // you can't set temperature less than zero or more than 10... min value is 0 and max is 10.
        if (temperature < 0) {
            this->temperature = 0;    
        }
        else if (temperature > 10) {
            this->temperature = 10;
        }
        else {
            this->temperature = temperature;
        }
    }
};

int main() {
    Stove stove(0);

    // stove.temperature;
    // error: 'int Stove::temperature' is private within this context
    // We can't access the temperature attribute directly as it's private and thus is not directly accessible outside the class

    // stove.temperature = 10;
    // We can't also set the temperature

    cout << "Stove's temperature : " << stove.getTemperature() << '\n';
    stove.setTemperature(1000);
    cout << "Stove's temperature : " << stove.getTemperature() << '\n';

    return 0;
} 