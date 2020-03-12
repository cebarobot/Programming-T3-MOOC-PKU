#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

char name[5][8] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int seq[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
int bld[5];

class com{
	public:
		int strth;
		int time;
		int all;
		bool stop;
		int peo;
		int rb;
		int num[5];
		com(int strth, int rb): strth(strth), rb(rb) {
			time = 0;
			all = 0;
			stop = false;
			peo = -1;
			for(int i = 0; i < 5; i++) {
				num[i] = 0;
			}
		}
		void ddd() {
			stop = true;
			for(int i = 1; i <= 5; i++) {
				if(strth >= bld[seq[rb][(peo + i) % 5]]) {
					stop = false;
					strth -= bld[seq[rb][(peo + i) % 5]];
					peo = (peo + i) % 5;
					break;
				}
			}
			if(stop) {
				printf("%03d ", time++);
				printf("%s ", rb == 0? "red" : "blue");
				printf("headquarter stops making warriors\n");
			} else {
				printf("%03d ", time++);
				printf("%s ", rb == 0? "red" : "blue");
				printf("%s ", name[seq[rb][peo]]);
				printf("%d born ", ++all);
				printf("with strength %d,", bld[seq[rb][peo]]);
				printf("%d ", ++num[seq[rb][peo]]);
				printf("%s ", name[seq[rb][peo]]);
				printf("in %s headquarter\n", rb == 0? "red" : "blue");
			}

		}
};

int main() {
	int n;
	cin >> n;
	for(int ccc = 1; ccc <= n; ccc++){
		printf("Case:%d\n", ccc);
		int xxx;
		cin >> xxx;
		com red(xxx, 0), blue(xxx, 1);
		for(int i = 0; i < 5; i++) {
			cin >> bld[i];
		}
		while(!(red.stop && blue.stop)) {
			if(!red.stop) red.ddd();
			if(!blue.stop) blue.ddd();
		}
	}
	return 0;
}