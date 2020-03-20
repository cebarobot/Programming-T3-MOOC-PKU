#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
    MyString(const MyString & bb) {
        if (bb.p) {
			p = new char[strlen(bb.p) + 1];
			strcpy(p, bb.p);
		} else {
            p = NULL;
        }
    }
    void Copy(const char * str) {
        if (p) {
            delete [] p;
        }
        p = NULL;
        if (str) {
			p = new char[strlen(str) + 1];
			strcpy(p, str);
		}
    }
    MyString & operator = (const MyString & bb) {
        if (this == &bb) {
            return *this;
        }
        if (p) {
            delete [] p;
        }
        if (bb.p) {
			p = new char[strlen(bb.p) + 1];
			strcpy(p, bb.p);
		} else {
            p = NULL;
        }
        return *this;
    }
    MyString & operator = (const char * str) {
        if (p) {
            delete [] p;
        }
        p == NULL;
        if (str) {
			p = new char[strlen(str) + 1];
			strcpy(p, str);
		} else {
            p = NULL;
        }
        return *this;
    }
    friend ostream & operator << (ostream & os, const MyString & aa) {
        if (aa.p) {
            os << aa.p;
        }
        return os;
    }
};

int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}