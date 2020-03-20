#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
    int arr[10][10];
    int x, y;
public:
    Array2() {}
    Array2 (int a, int b): x(a), y(b) {}
    int * operator [] (int index) {
        return arr[index];
    }
    int operator () (int a, int b) {
        return arr[a][b];
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}