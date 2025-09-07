#include <iostream>
#include <vector>
using namespace std;

int max1s(vector<int> arr){
    int n = arr.size();
    int cnt = 0, ans = 0;
    for(int i=0; i<n; i++){
        if(arr[i] == 1){
            cnt++;
            ans = max(ans, cnt);
        }
        else cnt = 0;
    }
    return ans;
}

int main() {
    vector<int> arr = {1,1,0,1,0,0,1,1,1,0,1,0,0};
    int res = max1s(arr);
    cout << "Maximum Consecutive 1s are : " << res;
    return 0;
}