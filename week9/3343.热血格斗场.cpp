#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

map<int, int> mapp;

int main() {
    int nn;
    mapp[1000000000] = 1;
    cin >> nn;
    map<int, int>::iterator it;
    while (nn--) {
        int id, power;
        cin >> id >> power;
        it = mapp.lower_bound(power);
        int old_id = 0;
        int old_d_power;
        if (it != mapp.end()) {
            old_id = it->second;
            old_d_power = abs(it->first - power);
        }
        if (it != mapp.begin()) {
            it--;
            if (!old_id) {
                old_id = it->second;
                old_d_power = abs(it->first - power);
            } else if (abs(it->first - power) < old_d_power) {
                old_id = it->second;
                old_d_power = abs(it->first - power);
            } else if (abs(it->first - power) == old_d_power && it->first < power) {
                old_id = it->second;
                old_d_power = abs(it->first - power);
            }
        }
        cout << id << " " << old_id << endl;
        mapp[power] = id;
    }
    return 0;
}