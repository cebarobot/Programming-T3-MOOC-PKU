#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

set<int> ss;
multiset<int> ms;

int main() {
    int N;
    string ord;
    int tt, pp;
    cin >> N;
    while (N--) {
        cin >> ord;
        if (ord == "add") {
            cin >> tt;
            ss.insert(tt);
            ms.insert(tt);
            cout << ms.count(tt) << endl;
        } else if (ord == "del") {
            cin >> tt;
            cout << ms.count(tt) << endl;
            ms.erase(ms.lower_bound(tt), ms.upper_bound(tt));
        } else if (ord == "ask") {
            cin >> tt;
            cout << ss.count(tt) << " " << ms.count(tt) << endl;
        }
    }
    return 0;
}