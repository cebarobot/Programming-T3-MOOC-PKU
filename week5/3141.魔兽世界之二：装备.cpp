#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CAMP = 2;
const int MAX_WORRIER_KIND = 5;
const int MAX_WEAPON_KIND = 3;

#define RED     0
#define BLUE    1

#define DRAGON  0
#define NINJA   1
#define ICEMAN  2
#define LION    3
#define WOLF    4

#define SWORD   0
#define BOMB    1
#define ARROW   2

const string camp_name[MAX_WORRIER_KIND] = {"red", "blue"};
const string worrier_name[MAX_WORRIER_KIND] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const string weapon_name[3] = {"sword", "bomb", "arrow"};
const int worrier_make_list[MAX_CAMP][MAX_WORRIER_KIND] = {
    {ICEMAN, LION, WOLF, NINJA, DRAGON}, // red;
    {LION, DRAGON, NINJA, ICEMAN, WOLF}, // blue;
};

int worrier_health_point[MAX_WORRIER_KIND];

class Warrior {
private:
    int camp;
    int name;
    int id;
    int health_point;
public:
    Warrior(int camp, int name, int id, int num_in_stock):
        camp(camp), name(name), id(id), health_point(worrier_health_point[name]) {
        cout << camp_name[camp] << " " << worrier_name[name] << " " << id;
        cout << " born with strength " << health_point << "," << num_in_stock + 1 << " ";
        cout << worrier_name[name] << " in " << camp_name[camp] << " headquarter" << endl;
    }
};

class Dragon : public Warrior {
private:
    int weapon;
    double morale;
public:
    Dragon(int camp, int id, int num_in_stock, int left_health_point): 
        Warrior(camp, DRAGON, id, num_in_stock), weapon(id % 3), 
        morale((double) left_health_point / worrier_health_point[DRAGON]) {
        cout << "It has a " << weapon_name[weapon] << ",";
        cout << "and it's morale is " << fixed << setprecision(2) << morale << endl;
    }
};

class Ninja : public Warrior {
private:
    int weapon_0, weapon_1;
public:
    Ninja(int camp, int id, int num_in_stock):
        Warrior(camp, NINJA, id, num_in_stock), weapon_0(id % 3), weapon_1((id + 1) % 3) {
        cout << "It has a " << weapon_name[weapon_0] << " and a " << weapon_name[weapon_1] << endl;
    }
};

class Iceman: public Warrior {
private:
    int weapon;
public:
    Iceman(int camp, int id, int num_in_stock):
        Warrior(camp, ICEMAN, id, num_in_stock), weapon(id % 3) {
        cout << "It has a " << weapon_name[weapon] << endl;
    }
};

class Lion : public Warrior {
private:
    int loyalty;
public:
    Lion(int camp, int id, int num_in_stock, int left_health_point):
        Warrior(camp, LION, id, num_in_stock), loyalty(left_health_point) {
        cout << "It's loyalty is " << loyalty << endl;
    }
};

class Wolf : public Warrior {
public:
    Wolf(int camp, int id, int num_in_stock):
        Warrior(camp, WOLF, id, num_in_stock) {}
};

class Camp {
private:
    int camp;
    int left_health_point;
    int cnt_all_warriors;
    int next_worrier;
    int cnt_warrior[MAX_WORRIER_KIND];
    Warrior * warriors[10010];
    bool making_stoped;
    bool makeParticularWorrier(int worrier_kind) {
        if (worrier_kind < 0 || worrier_kind >= MAX_WORRIER_KIND) {
            cerr << "Error: wrong worrier_kind in makeParticularWorrier" << endl;
            return false;
        }
        left_health_point -= worrier_health_point[worrier_kind];
        if (worrier_kind == DRAGON) {
            warriors[cnt_all_warriors] = 
                new Dragon(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind], left_health_point);
        } else if (worrier_kind == NINJA) {
            warriors[cnt_all_warriors] = 
                new Ninja(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind]);
        } else if (worrier_kind == ICEMAN) {
            warriors[cnt_all_warriors] = 
                new Iceman(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind]);
        } else if (worrier_kind == LION) {
            warriors[cnt_all_warriors] = 
                new Lion(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind], left_health_point);
        } else if (worrier_kind == WOLF) {
            warriors[cnt_all_warriors] = 
                new Wolf(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind]);
        }
        cnt_all_warriors += 1;
        cnt_warrior[worrier_kind] += 1;
        return true;
    }
public:
    Camp(int camp, int left_health_point):
        camp(camp), left_health_point(left_health_point), cnt_all_warriors(0), making_stoped(false),
        next_worrier(0) {
        memset(cnt_warrior, 0, sizeof(cnt_warrior));
    }
    ~Camp() {
        for (int i = 0; i < cnt_all_warriors; i++) {
            delete warriors[i];
        }
    }
    bool makeWarrior() {
        bool have_made = false;
        for (int i = 0; i < MAX_WORRIER_KIND; i++) {
            int cur_worrier_kind = worrier_make_list[camp][(next_worrier + i) % MAX_WORRIER_KIND];
            if (left_health_point >= worrier_health_point[cur_worrier_kind]) {
                next_worrier = (next_worrier + i + 1) % MAX_WORRIER_KIND;
                makeParticularWorrier(cur_worrier_kind);
                have_made = true;
                break;
            }
            // cerr << "=====" << worrier_name[cur_worrier_kind] << " have not been made for ";
            // cerr << "left_health_point = " << left_health_point << " but worrier_health_point = ";
            // cerr << worrier_health_point[cur_worrier_kind] << endl;
        }
        if (!have_made) {
            making_stoped = true;
            cout << camp_name[camp] << " headquarter stops making warriors" << endl;
        }
    }
    bool isMakingStoped() {
        return making_stoped;
    }
};

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case:" << i << endl;
        int M;
        cin >> M;
        Camp red_camp(RED, M);
        Camp blue_camp(BLUE, M);
        for (int j = 0; j < MAX_WORRIER_KIND; j++) {
            cin >> worrier_health_point[j];
        }
        for (int time = 0; !red_camp.isMakingStoped() || !blue_camp.isMakingStoped(); time++) {
            if (!red_camp.isMakingStoped()) {
                cout << setfill('0') << setw(3) << time << " " << setw(0);
                red_camp.makeWarrior();
            }
            if (!blue_camp.isMakingStoped()) {
                cout << setfill('0') << setw(3) << time << " " << setw(0);
                blue_camp.makeWarrior();
            }
        }
    }
    return 0;
}