#include <iostream>
#include <map>

using namespace std;

int main(){
    // Multimap is similar to map but it can stores duplicate / multiple keys
    // only multimap[key] can't be used ... rest other functions are same

    multimap<int,int> mmp;
    mmp.emplace(1,2);
    mmp.emplace(2,4);
    mmp.emplace(3,6);
    mmp.emplace(1,3);
    for (auto x : mmp) cout << x.first << " : " << x.second << "\t";    // 1 : 2   1 : 3   2 : 4   3 : 6 --> keys stored in sorted order
    auto it = mmp.find(1);
    cout << endl << it->first << " " << it->second;
    
}