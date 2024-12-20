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



unordered_map<string, shared_ptr<Spell>> predefSpells = { // Available spells
    {"frb", make_shared<Spell>("Fire ball", 30, 10)},
    {"ice", make_shared<Spell>("Ice blast", 25, 5)},
    {"spk", make_shared<Spell>("Spiked sphere", 35, 12)},
    {"spit", make_shared<Spell>("Soul spit", 10, 10)},
    {"fear", make_shared<Spell>("Internal pain", 0, 30)},
    {"pip", make_shared<Spell>("Magic metal pipe", 40, 0)}
};

unordered_map<string, shared_ptr<Attack>> predefAttacks = { // Alailable attacks
    {"axe", make_shared<Attack>("Axe", 30, 10)},
    {"psn", make_shared<Attack>("Poisonous blast", 5, 25)},
    {"kick", make_shared<Attack>("Kick", 15, 12)},
    {"pip", make_shared<Attack>("Metal pipe", 40, 0)},
    {"bit", make_shared<Attack>("Bite", 15, 20)},
    {"spr", make_shared<Attack>("Spear", 25, 15)},
    {"fire", make_shared<Attack>("Infernal fire", 5, 40)}
};

void duel(shared_ptr<Entity> mage, shared_ptr<Entity> creature) {
    cout << "Duel starts now!" << endl;
    cout << "Mage: " << mage->getName() << ", health: " << mage->getHealth() << endl;
    cout << "Creature: " << creature->getName() << ", health: " << creature->getHealth() << endl;

    // Showing all spells and attacks
    dynamic_pointer_cast<Mage>(mage)->displaySpells();
    dynamic_pointer_cast<Creature>(creature)->displayAttacks();

    while (mage->getHealth() > 0 && creature->getHealth() > 0) { // duel cycle
        string spellName;
        cout << mage->getName() << ", enter your spell: ";
        getline(cin, spellName);
        mage->doAttack(spellName, creature);

        if (creature->getHealth() <= 0) { // if creature dies, mage wins
            break;
        }

        string attackName;
        cout << creature->getName() << ", enter your attack: ";
        getline(cin, attackName);
        creature->doAttack(attackName, mage);
    }

    if (mage->getHealth() <= 0 && creature->getHealth() <= 0) {
        cout << "Both participants DIED." << endl;
    } else if (mage->getHealth() <= 0) {
        cout << "Evil creature won." << endl;
    } else {
        cout << "Mage won." << endl;
    }

    
}


// Removing dead entities from vectors
template<typename T>
void removeDead(vector<shared_ptr<T>>& participants) {
    for (auto it = participants.begin(); it != participants.end(); ) {
        if ((*it)->getHealth() <= 0) {
            it = participants.erase(it);
        } else {
            ++it;
        }
    }
}


// Reading MAGES
vector<shared_ptr<Mage>> readMagesFromFile(const string& filename) {
    vector<shared_ptr<Mage>> mages;
    ifstream file(filename); // Opening file
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, spell1, spell2, spell3; // Format: name-spell-spell-spell-health
            int health;
            
            iss >> name >> spell1 >> spell2 >> spell3 >> health;

            // Creating spellbook
            shared_ptr<SpellBook> spellBook = make_shared<SpellBook>(name + "'s Spellbook");
            spellBook->addItem(predefSpells[spell1]);
            spellBook->addItem(predefSpells[spell2]);
            spellBook->addItem(predefSpells[spell3]);

            // Creating mage
            shared_ptr<Mage> mage = make_shared<Mage>(name, health, spellBook);
            mages.push_back(mage);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return mages;
}


vector<shared_ptr<Creature>> readCreaturesFromFile(const string& filename) {
    vector<shared_ptr<Creature>> creatures;
    ifstream file(filename); // Opening file
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, attack1, attack2, attack3; // Format: name-attacksx3-health
            int health;
            
            iss >> name >> attack1 >> attack2 >> attack3 >> health;

            // Creating attack book
            shared_ptr<AttackBook> attackBook = make_shared<AttackBook>(name + "'s Attack Book");
            attackBook->addItem(predefAttacks[attack1]);
            attackBook->addItem(predefAttacks[attack2]);
            attackBook->addItem(predefAttacks[attack3]);

            // Creating creature
            shared_ptr<Creature> creature = make_shared<Creature>(name, health, attackBook);
            creatures.push_back(creature);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return creatures;
}

