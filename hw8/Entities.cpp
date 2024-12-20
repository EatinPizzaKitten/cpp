#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>


using namespace std;

class Entity { // Base entity class, parent for mages and creatures
    private:
        string name;
        int health;
    public:
        Entity(string _name, int _health) : name(_name), health(_health) {}

        string getName() {
            return name;
        }

        int getHealth() {
            return health;
        }

        void takeDamage(int damage) { // Method that damages entity (mage, creature)
            health -= damage;
            if (health < 0) {
                health = 0;
            }
        }

        virtual void doAttack(string attackName, shared_ptr<Entity> target) = 0;
};


class Spell { // Base Class for spells
    private:
        int damage;
        int bonusDamage;
        string name;
    public:
        Spell(string _name, int _dmg, int _bonusDmg) 
        : name(_name), damage(_dmg), bonusDamage(_bonusDmg) {}

        string getName() {
            return name;
        }

        int getTotalDamage() {
            return (damage+bonusDamage);
        }
};

class Attack { // Base Class for evil attacks >:)
    private:
        int damage;
        int bonusDamage;
        string name;
    public:
        Attack(string _name, int _dmg, int _bonusDmg) : name(_name), damage(_dmg), bonusDamage(_bonusDmg) {}
        
        string getName() {
            return name;
        }

        int getTotalDamage() {
            return (damage+bonusDamage);
        }
};

// Template of Base class for books
template<typename T>
class BookBase {
    protected:
        string name;
        unordered_map<string, shared_ptr<T>> items;
    
    public:
        BookBase(string _name) : name(_name) {}

        string getName() const {
            return name;
        }

        void addItem(shared_ptr<T> item) {
            items[item->getName()] = item; // Add items
        }

        bool hasItem(const string& itemName) const {
            return items.find(itemName) != items.end(); // Check for items
        }

        shared_ptr<T> getItem(const string& itemName) { // Getting by name
            if (hasItem(itemName)) {
                return items.at(itemName);
            } else {
                return nullptr;
            }
        }

        void displayItems() const { // Showing all items
            cout << "Book: " << name << endl;
            for (const auto& [key, value] : items) {
                cout << "> " << key << ", damage: " << value->getTotalDamage() << endl;
            }
        }
};

class SpellBook : public BookBase<Spell> { // Spell book
    public:
        using BookBase<Spell>::BookBase;
};

class AttackBook : public BookBase<Attack> { // Attack book
    public:
        using BookBase<Attack>::BookBase;
};


// MAGE CLASS
class Mage : public Entity {
    private:
        shared_ptr<SpellBook> spellBook;
    
    public:
        Mage(string _name, int _health, shared_ptr<SpellBook> _spellBook) 
        : Entity(_name, _health), spellBook(_spellBook) {}

        void doAttack(string spellName, shared_ptr<Entity> target) override {
            if (spellBook->hasItem(spellName)) {
                shared_ptr<Spell> spell = spellBook->getItem(spellName);
                int totalDamage = spell->getTotalDamage();
                cout << this->getName() << " casts a spell " << spellName << " against " << target->getName() << "." << endl;
                cout << totalDamage << " damage is done." << endl;
                target->takeDamage(totalDamage);
                cout << target->getName() << "'s remaining health: " << target->getHealth() << endl;
            } else {
                cout << "Such spell does not exist!" << endl;
            }
        }

        void displaySpells() {
            spellBook->displayItems();
        }
};



// EVIL CREATURE CLASS
class Creature : public Entity {
    private:
        shared_ptr<AttackBook> attackBook;
    
    public:
        Creature(string _name, int _health, shared_ptr<AttackBook> _attackBook) 
        : Entity(_name, _health), attackBook(_attackBook) {}

        void doAttack(string attackName, shared_ptr<Entity> target) override {
            if (attackBook->hasItem(attackName)) {
                shared_ptr<Attack> attack = attackBook->getItem(attackName);
                int totalDamage = attack->getTotalDamage();
                cout << this->getName() << " uses " << attackName << " against " << target->getName() << "." << endl;
                cout << totalDamage << " damage is done." << endl;
                target->takeDamage(totalDamage);
                cout << target->getName() << "'s remaining health: " << target->getHealth() << endl;
            } else {
                cout << this->getName() << " does not know this attack!" << endl;
            }
        }

        void displayAttacks() {
            attackBook->displayItems();
        }
};
