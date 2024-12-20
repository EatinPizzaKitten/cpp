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

#include "Entities.cpp"
#include "func.cpp"


int main() {
    vector<shared_ptr<Mage>> mages = readMagesFromFile("mglist.txt");
    vector<shared_ptr<Creature>> creatures = readCreaturesFromFile("evillist.txt");

    while (true) {
        if (!mages.empty() && !creatures.empty()) {
            shared_ptr<Mage> chosenMage = mages[0];
            shared_ptr<Creature> chosenCreature = creatures[0];

            duel(chosenMage, chosenCreature);
        } else if (!mages.empty() && creatures.empty()){
            cout << "All creatures are dead. Mages won!" << endl;
            break;
        } else if (mages.empty() && !creatures.empty()){
            cout << "All mages are dead. Creatures won!" << endl;
            break;
        } else {
            cout << "The battlefield is full of dead bodies. There is nothing to do but to grief about the fallen. There are no winners in this battle" << endl;
            break;
        }

        removeDead(mages);
        removeDead(creatures);
    }
    return 0;
}