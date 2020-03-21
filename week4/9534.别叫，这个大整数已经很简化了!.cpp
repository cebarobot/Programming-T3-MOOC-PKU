#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
private:
    int digits[MAX];
    int size;
public:
    void calcSize() {
        if (size == 0) {
            size = 1;
        }
        while (size > 1 && !digits[size - 1]) {
            size -= 1;
        }
    }
    CHugeInt() {
        memset(digits, 0, sizeof(digits));
    }
    CHugeInt(int n) {
        memset(digits, 0, sizeof(digits));
        size = 0;
        while (n) {
            digits[size++] = n % 10000;
            n /= 10000;
        }
        calcSize();
    }
    CHugeInt(const char * str) {
        memset(digits, 0, sizeof(digits));
        size = 0;
        if (!str) {
            return;
        }
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            int i_rev = len - i - 1;
            digits[i_rev / 4] = digits[i_rev / 4] * 10 + str[i] - '0';
        }
        size = len / 4 + 1;
        calcSize();
    }
    CHugeInt(const CHugeInt & xx): size(xx.size) {
        memcpy(digits, xx.digits, sizeof(digits));
    }
    friend ostream & operator << (ostream & os, const CHugeInt & xx) {
        char tmp[5];
        for (int i = xx.size - 1; i >= 0; i--) {
            // printf("====== digits[%d] = %d;\n", i, xx.digits[i]);
            if (i == xx.size - 1) {
                sprintf(tmp, "%d", xx.digits[i]);
            } else {
                sprintf(tmp, "%04d", xx.digits[i]);
            }
            os << tmp;
        }
        return os;
    }
    CHugeInt operator + (const CHugeInt & yy) const {
        CHugeInt xx = *this;
        int carry_io = 0;
        xx.size = max(xx.size, yy.size);
        for (int i = 0; i < xx.size; i++) {
            int res = xx.digits[i] + yy.digits[i] + carry_io;
            carry_io = res / 10000;
            xx.digits[i] = res % 10000;
        }
        xx.digits[xx.size++] = carry_io;
        xx.calcSize();
        return xx;
    }
    friend CHugeInt operator + (int xx, const CHugeInt & yy) {
        return CHugeInt(xx) + yy;
    }
    CHugeInt & operator += (const CHugeInt & yy) {
        *this = *this + yy;
        return *this;
    }
    CHugeInt operator ++ () {
        *this = *this + 1;
        return *this;
    }
    CHugeInt operator ++ (int x) {
        CHugeInt res = *this;
        *this = *this + 1;
        return res;
    }
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		// cout << a << endl;
		cout << b << endl;
	}
	return 0;
}