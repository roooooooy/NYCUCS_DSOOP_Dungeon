#include "Item.h"

Item::Item(): Object("Item") {
}

Item::Item(string _name, int _health, int _attack, int _defense, int _coin): Object(_name, "Item"), health(_health), attack(_attack), defense(_defense), coin(_coin) {
}

bool Item::triggerEvent(Object* obj) {
    GameCharacter *_player = dynamic_cast<GameCharacter*>(obj);
    Player *player = dynamic_cast<Player*>(_player);
    cout << "You picked up an " << getName() << ".\n";
    player->addItem(Item(this->getName(), this->getHealth(), this->getAttack(), this->getDefense(), this->coin));
    player->increaseStates(this->getHealth(), this->getAttack(), this->getDefense());
    cout << '\n';
    return 1;
}

int Item::getHealth() {
    return health;
}
int Item::getAttack() {
    return attack;
}
int Item::getDefense() {
    return defense;
}
void Item::setHealth(int _health) {
    health = _health;
}
void Item::setAttack(int _attack) {
    attack = _attack;
}
void Item::setDefense(int _defense) {
    defense = _defense;
}

// ostream& operator<< (ostream &out, const &Item, item) {
// }
void Item::output(string s) {
    Object *obj = this;
    cout << s << obj->getName() << '\n';
    cout << s << "Health: " << health << '\n';
    cout << s << "Attack: " << attack << '\n';
    cout << s << "Defense: " << defense << '\n';
    // return out;
}