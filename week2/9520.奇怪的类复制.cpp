#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    Sample() {
    }
    Sample(int x) {
        v = x;
    }
    Sample(const Sample & ss) {
        v = ss.v + 2;
    }
    void operator = (const Sample & ss) {
        v = ss.v;
    }
    void operator = (int x) {
        v = x;
    }
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}