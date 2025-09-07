#include<iostream>
#include<vector>
using namespace std;

vector<int> lcmAndGcd(int a, int b) {
    // code here
    vector<int> v;
    int gcd;
    long long mul = 1LL * a * b;
    while(a>0 && b>0){
        if(a>b) a = a%b;
        else b = b%a;
    }
    if(a == 0) gcd = b;
    else gcd = a;
    v.push_back(mul/gcd);
    v.push_back(gcd);
    return v;
}

int main(){
    vector<int> ans = lcmAndGcd(10,16);
    cout << "LCM : " << ans[0] << endl;
    cout << "HCF / GCD : " << ans[1];
}