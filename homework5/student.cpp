#include <iostream>
#include <stdexcept>

using namespace std;

class Student {
private:
    const string name = "Ryan";
    const string surname = "Gosling";
    string group;
    int age;
    int HP, XP;
    int money;
    float studentTime;
    float Time;
public:
    short int grade;
    float wage = 10;

    Student (string p_group, int p_age, int p_HP, int p_XP, int p_money, float p_studentTime, float p_Time) {
        group = p_group;
        age = p_age;
        HP = p_HP;
        XP = p_XP;
        money = p_money;
        studentTime = p_studentTime;
        Time = p_Time;
    }

// Time managing
    void resetTime() {
        studentTime = 0;
    }

    void addTime(int t_h) {
        studentTime += t_h;
    }

    void addDayTime(int t_h) {
        Time += t_h;
        while (Time >= 24) {
            Time = Time - 24;
        }
    }


// ACTIONS
    // Еда: 1-гречка, 2-шаверма, 3-поход в столовую
    void Poel(int act){

        if (act == 1 && money < 50 || act == 2 && money < 200 || act == 3 && money < 300){
            cout << "Not enough money!";
            return;
        }

        switch (act) {
            case 1:
                money -= 50;
                HP += 10;
                addTime(0.5);
                addDayTime(0.5);
                cout << "You ate grecha.";
                break;
            
            case 2:
                money -= 200;
                HP += 30;
                addTime(0.5);
                addDayTime(0.5);
                cout << "You ate shawarma.";
                break;

            case 3:
                money -= 300;
                HP += 50;
                addTime(0.5);
                addDayTime(0.5);
                cout << "You went to cafeteria.";
                break;
            
            default:
                break;
        }
    }

    // STUDYING
    void Study(int t_h) {
        int damage = 20;
        addTime(t_h);
        addDayTime(t_h);

        wage += 0.1 * (t_h); // More knowledge - more wage

        XP += 10 * (t_h);

        if (studentTime >= 24) {
            damage *= 3;
        }

        if (Time <= 6) {
            damage *= 2; // Restrict nighttime study
        }

        HP -= damage;
    }

    // WORKING
    void Work(int t_h) {
        int damage = 20;
        addTime(t_h);
        addDayTime(t_h);

        money += wage * (t_h);

        if (studentTime >= 24) {
            damage *= 3;
        }

        if (Time <= 6) {
            damage *= 2; // Restrict nighttime work
        }

        HP -= damage;
    }

    // SLEEP
    void Sleep(int t_h) {
        int heal = 10;

        HP += heal * (t_h);
        addTime(t_h);
        addDayTime(t_h);
        if ((t_h) >= 6) {
            resetTime();
        }
    }
    
    // Entertainment: 1 - acloholism, 2 - music session, 3 - dating, 4 - scrolling
    void Entertain(int act, int t_h) {
        int heal;

        if (act == 1 && money < 200 || act == 2 && money < 100 || act == 3 && money < 300){
            cout << "Poor!";
            return;
        }

        addTime(t_h);
        addDayTime(t_h);

        switch (act) {
            case 1:
                heal = 10;
                if (studentTime >= 24) {
                    heal /= 3;
                }

                money -= 200;
                HP += heal * (t_h);
                break;
            
            case 2:
                heal = 20;
                if (studentTime >= 24) {
                    heal /= 3;
                }

                money -= 100;
                HP += heal * t_h;
                break;

            case 3:
                heal = 30;
                if (studentTime >= 24) {
                    heal /= 3;
                }

                money -= 300;
                HP += heal * (t_h);
                break;
            
            case 4:
                heal = 10;
                if (studentTime >= 24) {
                    heal /= 3;
                }

                HP += heal * (t_h);
                break;            

            default:
                break;
        }
    }


// INFO
    int getHP() {
        return HP;
    }

    int getMoney() {
        return money;
    }

    float getStudentTime() {
        return studentTime;
    }

    float getDayTime() {
        return Time;
    }

    void getTimeLeft() {
        cout << 24 - (Time) << " hours left in day.";
    }

    int getXP() {
        return XP;
    }

    void printInfo() {
        cout << "Name: " << name << ", Surname: " << surname << endl;
        cout << "Group number: " << group << endl;
        cout << "Age: " << age << endl;
        cout << "Health level: " << HP << endl;
        cout << "Money left: " << money << endl;
        cout << "Gained Experience: " << XP << endl;
        cout << "Semester grade: " << 10 << endl;
        cout << "Current time: " << Time << endl;
        cout << "Time since last GOOD sleep: " << studentTime << endl;
    }



    bool isDead() {
        return HP <= 0;
    }

    void sdox() {
        if (isDead()) {
            cout << "Ушел в академ...";
        }
    }
};


int main() {
    Student bublik("B04-304", 19, 100, 0, 100, 0, 0);
    bool flag = 0;
    float Time = bublik.getDayTime();
    float XP = bublik.getXP();
    float prev_time = 0;

    while (not flag){
        if (prev_time > Time) {
            cout << "Another miserable day passed...\n";
            bublik.printInfo();
        }

        prev_time = Time;
        cout << "Choose your action:\n1. Eat \n2. Work \n3. Study \n4. Sleep \n5. Entertainment \n6. Get info \n";
        int act;
        int t_h;
        cin >> act;
        switch (act) {
            case 1:
                cout << "Pick your food: \n1.Grecha \n2.Shawarma \n3.Go to cafeteria \n";
                int eda;
                cin >> eda;
                bublik.Poel(eda);
                break;
            case 2:
                cout << "How many hours will you work for? \n";
                cin >> t_h;
                bublik.Work(t_h);
                break;
            case 3:
                cout << "How many hours will you study for? \n";
                cin >> t_h;
                bublik.Study(t_h);
                break;
            case 4:
                cout << "How much time will you sleep for? \n";
                cin >> t_h;
                bublik.Sleep(t_h);
                break;
            case 5:
                cout << "Choose your entertainment (number): \n1. Alcoholism \n2. Play music \n3. Go on a date \n4. Scroll through your phone \n";
                int ent;
                cin >> ent;
                cout << "Number of hours: \n";
                cin >> t_h;
                bublik.Entertain(ent, t_h);
                break;
            case 6:
                bublik.printInfo();
                break;
        }

        bool flag = bublik.isDead();
        if (flag) {
            break;
        }
    }

    if (bublik.isDead()) {
        bublik.sdox();
    }

    return 0;
}