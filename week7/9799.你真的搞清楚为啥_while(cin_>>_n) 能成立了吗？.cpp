#include <iostream>
using namespace std;
class MyCin
{
private:
    bool status;
public:
    MyCin():status(true){}
    MyCin & operator >> (int & n) {
        if (!status) return *this;
        cin >> n;
        if (n == -1) status = false;
        return *this;
    }
    operator bool()  { return status; }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}