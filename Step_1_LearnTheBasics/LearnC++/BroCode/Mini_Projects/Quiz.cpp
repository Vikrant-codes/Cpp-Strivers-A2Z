#include<iostream>
using namespace std;

int main() {
    string questions[10] = {
                                "1. Who is the founder of C++?",
                                "2. Which symbol is used for single-line comments in C++?",
                                "3. What is the correct header file for using cout and cin?",
                                "4. What is the size of int in C++ (most commonly on 64-bit systems)?",
                                "5. What is the output of the following code? \n\t int x = 10; \n\t cout << x++;",
                                "6. Which keyword is used to prevent modification of a variable?",
                                "7. Which of the following correctly represents pass-by-reference?",
                                "8. What does the 'new' keyword do in C++?",
                                "9. Which concept allows same function name to behave differently based on parameters?",
                                "10. What will be the output of the following code? \n\t int a = 5; \n\t int &b = a; \n\t b = 10; \n\t cout << a;"                                
                           };
    
    string options[10][4] = {
                                {"A) Dennis Ritchie", "B) James Gosling", "C) Bjarne Stroustrup", "D) Guido van Rossum"},
                                {"A) /* */", "B) #", "C) <!-- -->", "D) //"},
                                {"A) <stdio,h>", "B) <conio.h>", "C) <iostream>", "D) <stdlib.h>"},
                                {"A) 2 bytes", "B) 4 bytes", "C) 8 bytes", "D) Compiler dependent"},
                                {"A) 10", "B) 11", "C) Garbage Value", "D) Compilation error"},
                                {"A) static", "B) final", "C) volatile", "D) const"},
                                {"A) void func(int &a)", "B) void func(int *a)", "C) void func(int a)", "D) void func(const int a)"},
                                {"A) Allocates memory on stack", "B) Allocates memeory on heap", "C) Delete memory", "D) Copies objects"},
                                {"A) Inheritance", "B) Encapsulation", "C) Function Overloading", "D) Abstraction"},
                                {"A) 5", "B) 10", "C) Garbage Value", "D) Compilation Error"},
                            };
    
    char answers[10] = {'C', 'D', 'C', 'B', 'A', 'D', 'A', 'B', 'C', 'B'};

    cout << "------------------------------------------\n";
    cout << "*******            QUIZ            *******\n";
    cout << "------------------------------------------\n\n";
    
    char ans;
    int score = 0;
    for (int i = 0; i < 10; i++) {
        // Display Question 
        cout << "Que " << questions[i] << '\n';
        // Display Options
        for (int j = 0; j < 4; j++)
            cout << options[i][j] << '\n';
        // Ask for answer
        cout << "\nEnter your answer : ";
        cin >> ans;
        ans = toupper(ans);
        // Check answer
        if (ans == answers[i]) {
            cout << "Correct Answer ^_^ \n\n";
            score++;
        }
        else
            cout << "Wrong Answer !! \nCorrect Answer: " << answers[i] << "\n\n";
    }
    cout << "Quiz Completed ...\n";
    cout << "------------------------------------------\n";
    cout << "*******           RESULT           *******\n";
    cout << "------------------------------------------\n";
    cout << "Your Score : " << score << " / 10\n";

    return 0;
}