#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;

list<int> * arr[10010];

int main() {
    int N;
    string ord;
    int tt, pp;
    cin >> N;
    while (N--) {
        cin >> ord;
        if (ord == "new") {
            cin >> tt;
            arr[tt] = new list<int>;
        } else if (ord == "add") {
            cin >> tt >> pp;
            arr[tt]->push_back(pp);
        } else if (ord == "merge") {
            cin >> tt >> pp;
            arr[tt]->merge(*arr[pp]);
        } else if (ord == "unique") {
            cin >> tt;
            arr[tt]->sort();
            arr[tt]->unique();
        } else if (ord == "out") {
            cin >> tt;
            arr[tt]->sort();
            for (list<int>::iterator i = arr[tt]->begin(); i != arr[tt]->end(); i++) {
                cout << *i << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}