#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
        friend ostream & operator<< (ostream & os, const Point & pp) {
            os << pp.x << "," << pp.y;
            return os;
        }
        friend istream & operator>> (istream & is, Point & pp) {
            is >> pp.x >> pp.y;
            return is;
        }
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}