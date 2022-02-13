#include "NPC.h"

NPC::NPC(): GameCharacter("NPC") {
}

NPC::NPC(string _name, string _script, vector<Item> _commodity): GameCharacter(_name, "NPC", 1, 1, 1), script(_script), commodity(_commodity) {
}

void NPC::listCommodity() { /*print all the Item in this NPC*/
    int cnt = 0;
    for(auto x: commodity) {
        cout << cnt++ << ": "; x.output("");
        cout << "Price: " << x.coin << "\n\n";
    }
}

/* Virtual function that you need to complete   */
/* In NPC, this function should deal with the   */
/* transaction in easy implementation           */
bool NPC::triggerEvent(Object* obj) {
    Player *player = dynamic_cast<Player*>(obj);
    cout << script;
    cout << "(Enter anything to continue...)\n";
    string s; getline(cin, s);
    cout << "-----------------------------------------------\n";
    cout << "You have " << player->coin << " coins.\n";
    if(commodity.size()) cout << "You can buy the following item:\n\n";
    else cout << "You have nothing to buy.\n\n";
    listCommodity();
    cout << commodity.size() << ": Leave.\n";

    // cout << "Please enter a commodity index: ";
    string str;
    while(1) {
        getline(cin, str);
        cout << '\n';
        if(str.length() == 0) {
            cout << "Invalid! Please choose an index: ";
            continue;
        }
        if(str.length() > 1) {
            cout << "Invalid! Please input only one charater: ";
            continue;
        }
        if(str[0] >= commodity.size()+1 + '0' || str[0] < '0') {
            cout << "Invalid! Please choose a valid index: ";
            continue;
        }
        break;
    }
    int choose = str[0] - '0';

    if(choose == commodity.size()) {
        cout << "Good bye!\n\n";
        return 0;
    }
    // cout << commodity[choose].coin << '\n';
    if(player->coin >= commodity[choose].coin) {
       cout << "-----------------------------------------------\n";
        cout << "You have successfully bought " << commodity[choose].getName() << "!\n\n";
        // cout << "(Enter anything to continue...)\n";
        // string s; getline(cin, s);
        player->coin -= commodity[choose].coin;
        player->increaseStates(commodity[choose].getHealth(), commodity[choose].getAttack(), commodity[choose].getDefense());
        player->addItem(commodity[choose]);
        // player->showStatistic(player);
        // cout << '\n';
        // if(player->getInventory().size()) cout << "You have the following items:\n\n";
        // else cout << "You have no item in your backpack now.\n";
        // for(auto x: player->getInventory()) {
        //     x.output(""); cout << '\n';
        // }
        // cout << '\n';
    }
    else {
        cout << "You do not have enough money!!! Get out of here!!!\n\n";
    }
    return 0;
}

/* Set & Get function*/
void NPC::setScript(string _script) {
    script = _script;
}
void NPC::setCommodity(vector<Item> _commodity) {
    commodity = _commodity;
}
string NPC::getScript() {
    return script;
}
vector<Item> NPC::getCommodity() {
    return commodity;
}