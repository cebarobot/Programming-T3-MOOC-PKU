#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

int M, N, K, T;

const int MAX_CAMP = 2;
const int MAX_WORRIER_KIND = 5;
const int MAX_WEAPON_KIND = 3;
const int MAX_CITY = 20;

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
#define ARROW_B 3


void printHour(int hour, const char * minute) {
    cout << setfill('0') << setw(3) << hour << setw(0);
    cout << ":";
    cout << minute << " ";
}

const string camp_name[MAX_WORRIER_KIND] = {"red", "blue"};
const string worrier_name[MAX_WORRIER_KIND] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const string weapon_name[4] = {"sword", "bomb", "arrow", "arrow_b"};
const int worrier_make_list[MAX_CAMP][MAX_WORRIER_KIND] = {
    {ICEMAN, LION, WOLF, NINJA, DRAGON}, // red;
    {LION, DRAGON, NINJA, ICEMAN, WOLF}, // blue;
};

int worrier_health_point[MAX_WORRIER_KIND];
int worrier_attack[MAX_WORRIER_KIND];

class Warrior {
private:
    int camp;
    int name;
    int id;
    int place;
    int health_point;
    int weapons[10];
    int cnt_weapon;
public:
    Warrior(int camp, int name, int id, int num_in_stock):
        camp(camp), name(name), id(id), health_point(worrier_health_point[name]) {
        cout << camp_name[camp] << " " << worrier_name[name] << " " << id;
        cout << " born with strength " << health_point << "," << num_in_stock + 1 << " ";
        cout << worrier_name[name] << " in " << camp_name[camp] << " headquarter" << endl;
    }
    void getWeapon(int weapon) {
        weapons[cnt_weapon++] = weapon;
    }
    void removeWeapon(int id) {
        for (int i = id + 1; i < cnt_weapon; i++) {
            weapons[i - 1] = weapons[i];
        }
        cnt_weapon -= 1;
    }
    int useWeapon() {
        if (weapons[0] == SWORD) {
            return SWORD;
        } else if (weapons[0] == BOMB) {
            removeWeapon(0);
            return BOMB;
        } else if (weapons[0] == ARROW) {
            weapons[0] = ARROW_B;
            return ARROW;
        } else if (weapons[0] == ARROW_B) {
            removeWeapon(0);
            return ARROW;
        }
    }
};

bool fightCmp(int weapon_a, int weapon_b) {
    if (weapon_a == 2) {
        weapon_a = 3;
    } else if (weapon_a == 3) {
        weapon_a = 2;
    }
    if (weapon_b == 2) {
        weapon_b = 3;
    } else if (weapon_b == 3) {
        weapon_b = 2;
    }
    return weapon_a < weapon_b;
}

class Dragon : public Warrior {
private:
public:
    Dragon(int camp, int id, int num_in_stock): 
        Warrior(camp, DRAGON, id, num_in_stock) {
        getWeapon(id % 3);
    }
};

class Ninja : public Warrior {
private:
public:
    Ninja(int camp, int id, int num_in_stock):
        Warrior(camp, NINJA, id, num_in_stock) {
        getWeapon(id % 3);
        getWeapon((id + 1) % 3);
    }
};

class Iceman: public Warrior {
private:
public:
    Iceman(int camp, int id, int num_in_stock):
        Warrior(camp, ICEMAN, id, num_in_stock) {
        getWeapon(id % 3);
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
                new Dragon(camp, cnt_all_warriors + 1, cnt_warrior[worrier_kind]);
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
    bool makeWarrior(int hour) {
        if (making_stoped) {
            return false;
        }
        int cur_worrier_kind = worrier_make_list[camp][(cnt_all_warriors) % MAX_WORRIER_KIND];
        if (left_health_point >= worrier_health_point[cur_worrier_kind]) {
            printHour(hour, "00");
            makeParticularWorrier(cur_worrier_kind);
            return true;
        } else {
            making_stoped = true;
            return false;
        }
    }
    bool isMakingStoped() {
        return making_stoped;
    }
    int elements() {
        return left_health_point;
    }
};


int main() {
    int tt;
    cin >> tt;
    for (int i = 1; i <= tt; i++) {
        cout << "Case:" << i << endl;
        cin >> M >> N >> K >> T;
        Camp red_camp(RED, M);
        Camp blue_camp(BLUE, M);
        for (int j = 0; j < MAX_WORRIER_KIND; j++) {
            cin >> worrier_health_point[j];
        }
        for (int j = 0; j < MAX_WORRIER_KIND; j++) {
            cin >> worrier_attack[j];
        }
        for (int hour = 0; hour * 60 <= T; hour++) {
            red_camp.makeWarrior(hour);
            blue_camp.makeWarrior(hour);
            printHour(hour, "50");
            cout << red_camp.elements() << " elements in red headquarter" << endl;
            printHour(hour, "50");
            cout << blue_camp.elements() << " elements in blue headquarter" << endl;
        }
    }
    return 0;
}