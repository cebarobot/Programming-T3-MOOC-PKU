#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
    for(; s[i]; ++i);
    return i;
}
void strcpy(char * d,const char * s)
{
    int i = 0;
    for(i = 0; s[i]; ++i)
        d[i] = s[i];
    d[i] = 0;
        
}
int strcmp(const char * s1,const char * s2)
{
    for(int i = 0; s1[i] && s2[i] ; ++i) {
        if(s1[i] < s2[i])
            return -1;
        else if(s1[i] > s2[i])
            return 1;
    }
    return 0;
}
void strcat(char * d,const char * s)
{
    int len = strlen(d);
    strcpy(d+len,s);
}
class MyString {
private:
    char *str;
    int len;
public:
    MyString(const char * s) {
        len = strlen(s);
        str = new char[len+1];
        strcpy(str, s);
    }
    MyString() {
        len = 1;
        str = new char[1];
        str[0] = '\0';
    }
    MyString(const MyString & a) {
        len = a.len;
        str = new char[len+1];
        strcpy(str, a.str);
    }
    friend ostream& operator << (ostream& o,const MyString& a) {
        o<<a.str;
        return o;
    }
    void operator +=(const char * a) {
        int l = len;
        char *b = new char[l+1];
        strcpy(b, str);
        delete str;
        len = l + strlen(a);
        str = new char[len+1];
        strcpy(str, b);
        int j;
        for(j = l; j <= len-1; j++)
            str[j] = a[j-l];
        str[j] = '\0';
    }
    MyString &operator = (const MyString & b) {
        if(str == b.str)
        {
            return *this;
        }
        if(str)
            delete str;
        len = strlen(b.str);
        str = new char[len+1];
        strcpy(str, b.str);
        return *this;
    }
    friend MyString operator +(const MyString & a, const MyString & b) {
        int l = a.len + b.len;
        char *p = new char[l+1];
        strcpy(p, a.str);
        int i;
        for(i = a.len; i <= l-1; i++)
        {
            p[i] = b.str[i-a.len];
        }
        p[i] = '\0';
        return MyString(p);
    }
    char& operator[](int i) {
        return str[i];
    }
    friend bool operator <(const MyString &a, const MyString &b) {
        if(strcmp(a.str, b.str) == -1)
            return true;
        else
            return false;
    }
    friend bool operator == (const MyString &a, const MyString &b) {
        if(strcmp(a.str, b.str) == 0)
            return true;
        else
            return false;
    }
    friend bool operator > (const MyString &a, const MyString &b) {
        if(strcmp(a.str, b.str) == 1)
            return true;
        else
            return false;
    }
     char * operator()(int a, int b) {
        char *res = new char[b+1];
        int i, j = a;
        for(i = 1; i <= b; i++, j++)
        {
            res[i-1] = str[j];
        }
        return res;
    }
};


int CompareString(const void * e1, const void * e2)
{
    MyString * s1 = (MyString *) e1;
    MyString * s2 = (MyString *) e2;
    if(* s1 < *s2)
    return -1;
    else if(*s1 == *s2)
    return 0;
    else if(*s1 > *s2)
    return 1;
}
int main()
{
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray,4,sizeof(MyString),CompareString);
    for(int i = 0;i < 4;i ++)
    cout << SArray[i] << endl;
    cout << s1(0,4) << endl;
    cout << s1(5,10) << endl;
    return 0;
}
