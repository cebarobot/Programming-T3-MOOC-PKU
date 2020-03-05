#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
    char name[110];
    int age, id;
    int s1, s2, s3, s4;
    double ans;
public:
    void input() {
        char ch = getchar();
        int cnt = 0;
        while(ch!=',') {
            name[cnt++] = ch;
            ch = getchar();
        }
        name[cnt] = 0;
        scanf("%d,%d,%d,%d,%d,%d", &age, &id, &s1, &s2, &s3, &s4);
    }
    void calculate(){
        ans = (s1 + s2 + s3 + s4)/4.0;
    }
    void output(){
        printf("%s,%d,%d,", name, age, id);
        cout << ans << endl;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}