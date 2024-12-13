#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <limits>

using namespace std;



class Spell {
    protected:
        int manaCost;
        string name;
        int category;
    public:
        Spell(string _name, int _manaCost) : 
        name(_name), manaCost(_manaCost) {}
        virtual void show() = 0;
        virtual void cast() = 0;
        virtual ~Spell() {}

        const string& getName() const { return name; }

        const int& getCategory() const { return category; }
};

class AttackingSpell : public Spell {
    protected:
        int damage;
        bool isSplash;
    public:
        AttackingSpell(string _name, int _manaCost, int _damage, bool _isSplash) : 
        Spell(_name, _manaCost), damage(_damage), isSplash(_isSplash) 
        {
            Spell::category = 1;
        }

        void show() override {
            cout << "Attacking spell: " << "'"+name+"'" <<" with " << damage << " damage, " << (isSplash ? "dealing splash damage." : "individually oriented.") << endl;
            cout << "Cost: " << manaCost << " mana." << endl;
        }
        void cast() override {
            cout << "Casting a " << name << "!" << endl;
        }
};

class BuffSpell : public Spell {
    protected:
        int armor;
        int spikeDamage;
    public:
        BuffSpell(string _name, int _manaCost, int _armor, int _spikeDamage) : 
        Spell(_name, _manaCost), armor(_armor), spikeDamage(_spikeDamage) 
        {
            Spell::category = 2;
        }

        void show() override {
            cout << "Buffing spell: " << "'"+name+"'," << " +" << armor << " armor, dealing " << spikeDamage << " damage with spikes." << endl;
            cout << "Cost: " << manaCost << " mana." << endl;
        }
        void cast() override {
            cout << "Casting a buffing spell!" << endl;
        }
};

class HealingSpell : public Spell {
    protected:
        int regen;
        int manaRegen;
    public:
        HealingSpell(string _name, int _manaCost, int _regen, int _manaRegen) :
        Spell(_name, _manaCost), regen(_regen), manaRegen(_manaRegen) 
        {
            Spell::category = 3;
        }

        void show() override {
            cout << "Healing spell: " << "'"+name+"'," << " restoring " << regen << " health and " << manaRegen << " mana." << endl;
            cout << "Cost: " << manaCost << " mana." << endl;
        }
        void cast() override {
            cout << "Casting a healing spell!" << endl;
        }
};




class AbstractSpellFactory {
    public:
        virtual shared_ptr<Spell> createAttackingSpell(string name, int manaCost, int damage, bool isSplash) = 0;
        virtual shared_ptr<Spell> createBuffingSpell(string name, int manaCost, int armor, int spikeDamage) = 0;
        virtual shared_ptr<Spell> createHealingSpell(string name, int manaCost, int regen, int manaRegen) = 0;
};

class SpellFactory : public AbstractSpellFactory {
    public:
        shared_ptr<Spell> createAttackingSpell(string name, int manaCost, int damage, bool isSplash) override {
            return make_shared<AttackingSpell>(name, manaCost, damage, isSplash);
        }
        shared_ptr<Spell> createBuffingSpell(string name, int manaCost, int armor, int spikeDamage) override {
            return make_shared<BuffSpell>(name, manaCost, armor, spikeDamage);
        }
        shared_ptr<Spell> createHealingSpell(string name, int manaCost, int regen, int manaRegen) override {
            return make_shared<HealingSpell>(name, manaCost, regen, manaRegen);
        }
};




class DuplicateSpellException : public runtime_error {
public:
    explicit DuplicateSpellException(const string& message) : runtime_error(message) {}
};



class SpellBook {
    private:
        unordered_map<string, shared_ptr<Spell>> spells;
        string name;
    public:
        SpellBook(string _name) : name(_name) {}
        void addSpell(shared_ptr<Spell> spell) {
            auto [it, inserted] = spells.try_emplace(spell->getName(), move(spell));
            if (!inserted) {
                throw DuplicateSpellException("This spell already exists in the book.");
            }
        }

        string getName() {
            return name;
        }

        void displaySpells() {
            
            vector<shared_ptr<Spell>> attackingSpells;
            vector<shared_ptr<Spell>> buffingSpells;
            vector<shared_ptr<Spell>> healingSpells;

            for (const auto& [name, spell] : spells) {
                switch (spell->getCategory()) {
                    case 1:
                        attackingSpells.push_back(spell);
                        break;
                    case 2:
                        buffingSpells.push_back(spell);
                        break;
                    case 3:
                        healingSpells.push_back(spell);
                        break;
                }
            }

            if (!attackingSpells.empty()) {
                cout << "\n--- Attacking ---" << endl;
                for (const auto& spell : attackingSpells) {
                    spell->show();
                }
            }

            if (!buffingSpells.empty()) {
                cout << "\n--- Buffs ---" << endl;
                for (const auto& spell : buffingSpells) {
                    spell->show();
                }
            }

            if (!healingSpells.empty()) {
                cout << "\n--- Healing ---" << endl;
                for (const auto& spell : healingSpells) {
                    spell->show();
                }
            }
        }

        void viewSpellInfo(const string &name) {
            auto it = spells.find(name);
            if (it != spells.end()) {
                it->second->show();
            } else {
                cout << "Spell not found." << endl;
            }
        }

        void useSpellByName(const string &name) {
            auto it = spells.find(name);
            if (it != spells.end()) {
                it->second->cast();
            } else {
                cout << "Spell not found." << endl;
            }
        }
};


shared_ptr<Spell> createNewSpell(AbstractSpellFactory &factory) {
    int choice;
    do {
        cout << "Choose spell type:" << endl;
        cout << "1. Attacking Spell" << endl;
        cout << "2. Buffing Spell" << endl;
        cout << "3. Healing Spell" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 3);

    string name;
    cout << "Enter spell name: ";
    cin.ignore();
    getline(cin, name);

    switch (choice) {

    case 1: {
        int manaCost, damage;
        bool isSplash;

        cout << "Enter mana cost: ";
        if (!(cin >> manaCost)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Enter damage: ";
        if (!(cin >> damage)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Is it splash damage? (y/n): ";
        char answer;
        cin >> answer;
        isSplash = (answer == 'y' || answer == 'Y');
        return factory.createAttackingSpell(name, manaCost, damage, isSplash);
    }

    case 2: {
        int manaCost, armor, spikeDamage;
        cout << "Enter mana cost: ";
        if (!(cin >> manaCost)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Enter armor bonus: ";
        if (!(cin >> armor)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Enter spike damage: ";
        if (!(cin >> spikeDamage)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        return factory.createBuffingSpell(name, manaCost, armor, spikeDamage);
    }

    case 3: {
        int manaCost, regen, manaRegen;
        cout << "Enter mana cost: ";
        if (!(cin >> manaCost)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Enter health regeneration: ";
        if (!(cin >> regen)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        cout << "Enter mana regeneration: ";
        if (!(cin >> manaRegen)) {
            cerr << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nullptr;
        }

        return factory.createHealingSpell(name, manaCost, regen, manaRegen);
    }
    default:
        return nullptr;
    }
}

template<typename T>
struct Mage {
    string name;
    T* spell_book;

    Mage(const string& _name, T* _spell_book) : name(_name), spell_book(_spell_book) {}

    void castSpell() const {
        if (spell_book != nullptr) {
            cout << "Mage " << name << " uses his book \"" << spell_book->getName() << "\"" << endl;
        } else {
            cout << "Mage " << name << " has no spell books." << endl;
        }
    }
};

int main() {
    SpellFactory factory;
    SpellBook book = {"BOOK"};

    Mage<SpellBook> mage("Gandalf", &book);

    mage.castSpell();

    while (true) {
        try {
            int action;
            cout << "Select an action:" << endl;
            cout << "1. Add a new spell" << endl;
            cout << "2. View all spells" << endl;
            cout << "3. View spell info by name" << endl;
            cout << "4. Cast spell by name" << endl;
            cout << "5. Exit" << endl;
            

            if (!(cin >> action)) { // Проверка успешного ввода числа
                cerr << "Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (action) {

            case 1: {
                shared_ptr<Spell> newSpell = createNewSpell(factory);
                if (newSpell) {
                    book.addSpell(move(newSpell));
                }
                break;
            }

            case 2:
                book.displaySpells();
                break;

            case 3: {
                string spellName;
                cout << "Enter spell name: ";
                cin.ignore();
                getline(cin, spellName);
                book.viewSpellInfo(spellName);
                break;
            }

            case 4: {
                string spellName;
                cout << "Enter spell name: ";
                cin.ignore();
                getline(cin, spellName);
                book.useSpellByName(spellName);
                break;
            }

            case 5:
                return 0;

            default:
                cout << "Invalid option. Try again." << endl;
                break;
            }
        } catch (DuplicateSpellException &e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}