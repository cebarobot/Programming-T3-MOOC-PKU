#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int
    x) {
        val = x;
    }
    A() {
        val = 123;
    }
    A(const A & xx) {
        val = xx.val;
    }
    A & GetObj() {
        return *this;
    }
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}