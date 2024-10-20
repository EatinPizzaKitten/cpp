#include <iostream>
#include <stdexcept>

using namespace std;

class Student {
private:
    const string name, surname;
    string group;
    unsigned int age;
    unsigned int HP, XP;
    unsigned int money;
    &studentTime (int hours, int min, int sec);
    &Time (int H, int M, int S);
public:
    unsigned short int grade;
    float wage;

    Student(string p_name = "John", string p_surname = "Doe", int p_age = 19, string p_group = "", unsigned int p_hp = 100, unsigned int p_money = 100, int p_xp = 0, unsigned int p_grade = 10, float p_wage = 10):
        name(p_name), surname(p_surname), age(p_age), group(p_group), HP(p_hp), money(p_money), XP(p_xp), grade(p_grade), wage(p_wage)
    {
        resetTime();
    }

// Работа со временем
    void resetTime() {
        studentTime.hours = 0;
        studentTime.min = 0;
        studentTime.sec = 0;
    }

    void addTime(unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        studentTime.hours += t_h;
        studentTime.min += t_m;
        studentTime.sec += t_s;
        while (studentTime.sec >= 60) {
            studentTime.min++;
            studentTime.sec -= 60;
        }
        while (studentTime.min >= 60) {
            studentTime.hours++;
            studentTime.min -= 60;
        }
    }

    void addDayTime(unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        Time.H += t_h;
        Time.M += t_m;
        Time.S += t_s;
        while (Time.S >= 60) {
            Time.M++;
            Time.S -= 60;
        }
        while (Time.M >= 60) {
            Time.H++;
            Time.M -= 60;
        }
        if (Time.H >= 24) {
            Time.H = Time.H % 24;
        }
    }


// Действия
    // Еда: 1-гречка, 2-шаверма, 3-поход в столовую
    void Poel(unsigned short int act){

        if (act == 1 && money < 50 || act == 2 && money < 200 || act == 3 && money < 300){
            cout << "Not enough money!";
            return;
        }

        switch (act) {
            case 1:
                money -= 50;
                HP += 10;
                addTime(0,30,0);
                addDayTime(0,30,0);
                break;
            
            case 2:
                money -= 200;
                HP += 30;
                addTime(0,30,0);
                addDayTime(0,30,0);
                break;

            case 3:
                money -= 300;
                HP += 50;
                addTime(0,30,0);
                addDayTime(0,30,0);
                break;
            
            default:
                break;
        }
    }

    // Учимся
    void Study(unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        unsigned short int damage = 20;
        addTime(t_h, t_m, t_s);
        addDayTime(t_h, t_m, t_s);

        wage += 0.1 * (t_h + (t_m/60) + (t_s/3600)); // ЗП зависит от кол-ва знаний

        XP += 10 * (t_h + (t_m/60) + (t_s/3600));

        if (studentTime.hours >= 24) {
            damage *= 3;
        }

        if (Time.H <= 6) {
            damage *= 1.5; // Наказываем ночной бот
        }

        HP -= damage;
    }

    // Работаем
    void Work(unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        unsigned short int damage = 20;
        addTime(t_h, t_m, t_s);
        addDayTime(t_h, t_m, t_s);

        money += wage * (t_h + (t_m/60) + (t_s/3600));

        if (studentTime.hours >= 24) {
            damage *= 3;
        }

        if (Time.H <= 6) {
            damage *= 1.5; // Наказываем ночные смены
        }

        HP -= damage;
    }

    // Спим
    void Sleep(unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        unsigned short int heal = 10;

        if ((t_h + (t_m/60) + (t_s/3600)) >= 6) {
            resetTime();
        }

        HP += heal * (t_h + (t_m/60) + (t_s/3600));
        addTime(t_h, t_m, t_s);
        addDayTime(t_h, t_m, t_s);
    }
    
    // Развлекаемся: 1-алкоголизм, 2-муз. репетиция, 3-свидание, 4-скролл ленты
    void Entertain(unsigned short int act, unsigned int t_h, unsigned int t_m, unsigned int t_s) {
        unsigned short int heal;

        if (act == 1 && money < 200 || act == 2 && money < 100 || act == 3 && money < 300){
            cout << "Poor!";
            return;
        }

        addTime(t_h, t_m, t_s);
        addDayTime(t_h, t_m, t_s);

        switch (act) {
            case 1:
                heal = 10;
                if (studentTime.hours >= 24) {
                    heal /= 3;
                }

                money -= 200;
                HP += heal * (t_h + (t_m/60) + (t_s/3600));
                break;
            
            case 2:
                heal = 20;
                if (studentTime.hours >= 24) {
                    heal /= 3;
                }

                money -= 100;
                HP += 30
                break;

            case 3:
                heal = 30;
                if (studentTime.hours >= 24) {
                    heal /= 3;
                }

                money -= 300;
                HP += heal * (t_h + (t_m/60) + (t_s/3600));
                break;
            
            case 4:
                heal = 10;
                if (studentTime.hours >= 24) {
                    heal /= 3;
                }

                HP += heal * (t_h + (t_m/60) + (t_s/3600));
                break;            

            default:
                break;
        }
    }


// Информация
    int getHP() {
        return HP;
    }

    int getMoney() {
        return money;
    }

    void getTimeLeft() {
        cout << 24 - (Time.H) << " hours, " << 60 - Time.M << " minutes, " << 60 - Time.S << " seconds left.";
    }

    void printInfo() {
        cout << "Name: " << name << ", Surname: " << surname << endl;
        cout << "Group number: " << group << endl;
        cout << "Age: " << age << endl;
        cout << "Health level: " << HP << endl;
        cout << "Money left: " << money << endl;
        cout << "Gained Experience: " << XP << endl;
        cout << "Semester grade: " << grade << endl;
        cout << "Current time: " << Time.H << ":" << Time.M << ":" << Time.S << endl;
        cout << "Time since last GOOD sleep: " << studentTime.hours << ":" << studentTime.min << ":" << studentTime.sec << endl;
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
    Student bublik("Ryan", "Gosling", 19, "B04-304", 100, 100, 0, 10);
    bublik.printInfo();


}