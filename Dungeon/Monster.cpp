#include "Monster.h"

Monster::Monster(): GameCharacter("Monster") {
}

Monster::Monster(string _name, int _health, int _attack, int _defense, int _coin): GameCharacter(_name, "Monster", _health, _attack, _defense), coin(_coin){
}

Monster::Monster(string _name, int _health1, int _health2, int _attack, int _defense, int _coin): GameCharacter(_name, "Monster", _health1, _health2, _attack, _defense), coin(_coin){
}

bool checkplayer(GameCharacter *player) {
    return player->getCurrentHealth() > 0;
}
bool checkmonster(GameCharacter *monster) {
    return monster->getCurrentHealth() > 0;
}

void Monster::output(string s) {
    GameCharacter *monster = this;
    cout << s << "Health: " << monster->getCurrentHealth() << '\n';
    cout << s << "Attack: " << monster->getAttack() << '\n';
    cout << s << "Defense: " << monster->getDefense() << '\n';
    cout << s << "Coin: " << coin << '\n';
}
/* Virtual function that you need to complete   */
/* In Monster, this function should deal with   */
/* the combat system.                           */
bool Monster::triggerEvent(Object* obj) {
    GameCharacter *player = dynamic_cast<GameCharacter*>(obj);
    GameCharacter *monster = this;
    cout << "You are facing with: " << monster->getName() << ".\n";
    cout << "Here are " << monster->getName() << "'s information: " << '\n';
    this->output("");
    cout << '\n';
    Player *_player = dynamic_cast<Player*>(player);
    // cout << "Here are your information: \n";
    _player->showStatistic(obj);
    cout << '\n';
    while(1) {
        cout << "It's your turn:\n";
        string s; 
        // getline(cin, s);
        cout << "You attack monster by " << max(0, player->getAttack() - monster->getDefense()) << ".\n";
        monster->setCurrentHealth(monster->getCurrentHealth() - max(0, player->getAttack() - monster->getDefense()));
        // cout << "Enter anything to continue...\n";
        // getline(cin, s);
        if(!checkmonster(monster)) {
            cout << "You win! You defeated " << monster->getName() << "!\n";
            cout << "You get " << coin << " coin.\n";
            _player->coin += coin;
            cout << "(Enter anything to continue...)\n";
            getline(cin, s);
            return 1;
        }
        cout << monster->getName() << " still has " << monster->getCurrentHealth() << " points of health.\n";
        cout << "(Enter anything to continue...)\n";
        getline(cin, s);
        cout << "It's " << monster->getName() << "'s turn:\n";
        cout << monster->getName() << " attack you by " << max(0, monster->getAttack() - player->getDefense()) << ".\n";
        player->setCurrentHealth(player->getCurrentHealth() - max(0, monster->getAttack() - player->getDefense()));
        // cout << "Enter anything to continue...\n";
        // getline(cin, s);
        if(!checkplayer(player)) {
            cout << "\nYou lose! " << monster->getName() << " defeated you!\n\n";
            monster->setCurrentHealth(monster->getMaxHealth());
            return 0;
        }
        cout << "You still have " << player->getCurrentHealth() << " points of health.\n";
        cout << "(Enter anything to continue...)\n";
        getline(cin, s);

        // cout << "Do you wnat to run away? [1/0]\n";
        cout << "Input \"retreat\" to retreat from " << monster->getName() << ", otherwise, keep fighting.\n";
        getline(cin, s);
        if(s == "retreat") {
            monster->setCurrentHealth(monster->getMaxHealth());
            cout << "You retreat!\n\n";
            return 0;
        }
    }
    return 1;
}
