#include <iostream>
#include <vector>

using namespace std;

class Veterinar;

class Animal {
    private:
        string sound;
        int age;
        string name;
        string breed;
        int health;
        friend class Veterinar;
    public:
        Animal(string t_name, string t_breed, int t_age, string t_sound): name{t_name}, breed{t_breed}, age{t_age}, sound{t_sound}
        {
            health = 100;    
        }

        virtual void makeSound() {
            cout << sound << endl;
        }

        void getAge() {
            cout << "Age: " << age << endl;
        }

        void getName() {
            cout << "Name: " << name << endl;
        }

        void getBreed() {
            cout << "Breed: " << breed << endl;
        }

        void showInfo() {
            getName();
            getAge();
            getBreed();
        }
};

class Dog : public Animal {
    public:
        Dog(string t_name, string t_breed, int t_age, string t_sound = "WOOF!!!"): Animal("dog " + t_name, t_breed, t_age, t_sound)
        { }

        void makeSound() {
            Animal::makeSound();
        }

        void showInfo() {
            Animal::getName();
            Animal::getAge();
            Animal::getBreed();
        }
};

class Cat : public Animal {
    public:
        Cat(string t_name, string t_breed, int t_age, string t_sound = "MEOW!!!"): Animal("cat " + t_name, t_breed, t_age, t_sound)
        { }

        void makeSound() {
            Animal::makeSound();
        }

        void showInfo() {
            Animal::getName();
            Animal::getAge();
            Animal::getBreed();
        }
};

class Owner {
    struct fio {string surname; string name; string otchestvo;};
    vector<Cat*> cats;
    vector<Dog*> dogs;
    vector<Animal*> pets;

    private:
        struct fio hoz;
        int age;
        int pet_num;
        friend class Veterinar;
    public:
        Owner(const string &t_sur, const string &t_nam, const string &t_otch, int t_age, int t_pet_num): 
        hoz{fio{t_sur, t_nam, t_otch}}, age{t_age}, pet_num{t_pet_num}
        { }

        int getPetNum() {
            return pet_num;
        }

        vector<Animal*> t_pets;

        void showInfo() {
            cout << "Hi, my name is " << hoz.surname << " " << hoz.name << " " << hoz.otchestvo << ", I'm " << age << " years old." << endl;
        }

        void addCat(Cat* cat) {
            cats.push_back(cat);
        }

        void addDog(Dog* dog) {
            dogs.push_back(dog);
        }

        void displayPets() {
            int i = 1;
            for (auto &pet : pets) {
                cout << i << ". ";
                pet->showInfo();
                pet->makeSound();
                i++;
            }
        }

        void petList() {
            int i = 1;
            for (auto &pet : pets) {
                cout << i << ". ";
                pet->getName();
                i++;
            }
        }

        void createPets() {
            for (int i = 0; i < pet_num; i++) {
                cout << "Pick a number: dog (1) or cat (2) \n";
                int action = 0;
                cin >> action;

                if (action != 1 && action != 2) {
                    cerr << "Invalid choice. Please choose either 1 (dog) or 2 (cat).\n";
                    --i;
                    continue;
                }

                string t_name, t_breed;
                int t_age;

                cin.ignore();
                cout << "Enter name: ";
                getline(cin, t_name);
                cout << "Enter breed: ";
                getline(cin, t_breed);
                cout << "Enter age: ";
                cin >> t_age;

                if (t_age <= 0) {
                    cerr << "Age must be positive.\n";
                    --i;
                    continue;
                }

                Dog* t_dog = nullptr;
                Cat* t_cat = nullptr;

                switch (action) {
                    case 1:
                        t_dog = new Dog(t_name, t_breed, t_age);
                        addDog(t_dog);
                        pets.push_back(t_dog);
                        t_pets.push_back(t_dog);
                        break;
                    case 2:
                        t_cat = new Cat(t_name, t_breed, t_age);
                        addCat(t_cat);
                        pets.push_back(t_cat);
                        t_pets.push_back(t_cat);
                        break;
                }
            }
        }
};


class Veterinar {
    struct fio {string surname; string name; string otchestvo;};

    private:
        struct fio doc;
        int age;
    public:
        Veterinar(const string &t_sur, const string &t_nam, const string &t_otch, int t_age):
        doc{fio{t_sur, t_nam, t_otch}}, age{t_age}
        {}

        void Osmotr(Animal *pet) {
            cout << "Let's look at " << pet->name << "." << endl;
            cout << "Health: " << pet->health << endl;
        }

        void Treat(Animal *pet) {
            cout << "Treating " << pet->name << "." << endl;
            pet->health += 10;
            cout << "Health: " << pet->health << endl;
        }

        void talkTo(Owner *chel) {
            chel->showInfo();
            cout << "Hi, " << chel->hoz.name << ", nice to meet you! " << "My name is " << doc.surname + " " + doc.name + " " + doc.otchestvo << endl;
        }
};





int main() {
// EXAMPLES
//    Dog Nugget("Nugget", "Golden Retriever", 10);
//    Cat Scratchy("Scratchy", "Oriental", 5);
    
    string t_sur, t_nam, t_otch;
    int t_age, t_pet_num;
    cout << "Enter owner's surname: ";
    getline(cin, t_sur);
    cout << "Enter owner's name: ";
    getline(cin, t_nam);
    cout << "Enter owner's otchestvo: ";
    getline(cin, t_otch);
    cout << "Enter owner's age: ";
    cin >> t_age;
    cout << "Enter number of pets: ";
    cin >> t_pet_num;


    Owner boris(t_sur, t_nam, t_otch, t_age, t_pet_num);
    boris.createPets();

    cout << "\nPlease, meet:" << endl;
    boris.displayPets();
    cout << "" << endl;
    
    Veterinar vet("Ivanov", "Ivan", "Ivanovich", 40);

    int action;
    cout << "What to do with the veterinarian? (pick number)" << endl;
    cout << "1. Examine your pet\n" << "2. Treat your animal\n" << "3. Talk with him" << endl;
    cin >> action;

    int picked;
    switch (action) {
        case 1:
            cout << "Who would you like to examine? (number)" << endl;
            boris.petList();
            cin >> picked;
            picked--;
            vet.Osmotr(boris.t_pets[picked]);
            break;
        case 2:
            cout << "Who would you like to treat? (number)" << endl;
            boris.petList();
            cin >> picked;
            picked--;
            vet.Treat(boris.t_pets[picked]);
            break;
        case 3:
            vet.talkTo(&boris);
            break;
        default:
            cerr << "Wrong action!";
            break;
    }

    return 0;
}