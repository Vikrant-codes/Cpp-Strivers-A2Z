#include <iostream>
#include <vector>
using namespace std;

vector<int> getDivisors(int n) {
    vector<int> v;
    int pos = 0;
    for(int i=1; i*i <= n; i++) {
        if (n % i == 0) {
            v.insert(v.begin()+pos, i);
            pos++;
            if (n/i != i) {
                v.insert(v.begin()+pos, n/i);
            }
        }
    }
    return v;
}

int main() {
    vector<int> div = getDivisors(36);
    for (auto it : div) cout << it << " ";
    return 0;
}