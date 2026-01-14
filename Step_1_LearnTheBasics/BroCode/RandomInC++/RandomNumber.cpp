#include<iostream>
#include <cstdlib> // Required for srand, rand
#include <ctime>   // Required for time
using namespace std;

int main() {
    // pseudo-random = NOT truly random (but close)

    // srand() is the random number generator. It needs a 'seed' to work. 
    srand(time(NULL));
    // Programmers generally pass time as seed (because time changes, so it helps generate different random numbers)
    // the function call time(NULL) (or time(NULL) or time(nullptr)) returns the current calendar time as a time_t value, 
    // which is typically the number of seconds since the Unix epoch (January 1, 1970, 00:00:00 UTC).
    
    int num = rand();       // this will now generate random numbers between 0 to 32,767
    
    // Suppose we want to simulate a die throw, i.e. we want to generate 6 random numbers (1-6).
    // To do so, we do rand() % 6 as this will generate only 6 numbers (0, 1, 2, 3, 4 or 5) depending on the random number
    int n = rand() % 6;
    // but we want the random numbers to be in range [1, 6] not [0, 5] so we add 1 to get random number in required range.
    n = n + 1;

    cout << "Die is thrown..... Number generated is : " << n;

    return 0;
}