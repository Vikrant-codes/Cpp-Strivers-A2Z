#include<iostream>
#include<cmath>         // includes functions like : log10 , pow(base, exp), abs()
using namespace std;

bool isArmstrong(int n){
    int ct_d = (int)(log10(n) + 1);            // count of digits
    int sum = 0;
    int temp = n;
    while(temp!=0){
        int d = temp % 10;
        sum += pow(d, ct_d);
        temp /= 10;
    }
    return sum == n;
}

int main() {
    cout << "Armstrong Numbers upto 10000" << endl;
    for(int i=1; i<10000; i++){
        if (isArmstrong(i)) cout << i << "  ";
    }

    return 0;
}