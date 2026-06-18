#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Generate a random number b/w 1 to 100. Guess the number and tell how many tries it took to guess the number

int main() {
    srand(time(0));

    int num = rand() % 100 + 1;
    int guess, tries = 0;
    do {
        cout << "Enter your guess (1 - 100): ";
        cin >> guess;
        tries++;

        if (guess > num)
            cout << "Wrong Guess !! (Hint : try a smaller number) \n";
        else if (guess < num) 
            cout << "Wrong Guess !! (Hint : try a bigger number) \n";
        else
            cout << "Yayy, You guessed it !! \n";
        
    } while (guess != num);

    cout << "You guessed the random number in " << tries+1 << " attempt";


    return 0;
}