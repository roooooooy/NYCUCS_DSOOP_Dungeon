#include "Player.h"

Player::Player(): GameCharacter("Player"){
}

Player::Player(string _name, int _health, int _attack, int _defense, int _coin): GameCharacter(_name, "Player", _health, _attack, _defense), coin(_coin) {
}

Player::Player(string _name, int _health1, int _health2, int _attack, int _defense, int _coin): GameCharacter(_name, "Player", _health1, _health2, _attack, _defense), coin(_coin) {
}

void Player::addItem(Item item) {
    inventory.push_back(item);
}

void Player::increaseStates(int _health, int _attack, int _defense) {
    setMaxHealth(getMaxHealth() + _health);
    setCurrentHealth(getCurrentHealth() + _health);
    setAttack(getAttack() + _attack);
    setDefense(getDefense() + _defense);
}
void Player::changeRoom(Room* _room) {
    setPreviousRoom(getCurrentRoom());
    setCurrentRoom(_room);
}

/* Virtual function that you need to complete   */
/* In Player, this function should show the     */
/* status of player.                            */
bool Player::triggerEvent(Object* p) {
    GameCharacter *gameCharacter = dynamic_cast<GameCharacter*>(p);
    cout << "Your status are:\n";
    cout << "Current room: " << currentRoom->getIndex() << '\n';
    if(previousRoom == nullptr) cout << "No previous room.\n";
    else cout << "previous room: " << previousRoom->getIndex() << '\n';
    cout << "(Enter anything to continue...)\n";
    string s; getline(cin, s);
    cout << "Max health: " << gameCharacter->getMaxHealth() << '\n';
    cout << "Current health: " << gameCharacter->getCurrentHealth() << '\n';
    cout << "Attack: " << gameCharacter->getAttack() << '\n';
    cout << "Defense: " << gameCharacter->getDefense() << '\n';
    cout << "Coin: " << coin << "\n";
    cout << "(Enter anything to continue...)\n";
    getline(cin, s);
    if(inventory.size()) cout << "You have the following items:\n\n";
    else cout << "You have no items in your backpack now. \n";
    for(Item x: inventory) {
        x.output(""); cout << '\n';
    }
    // cout << '\n';
    return 1;
}

void Player::showStatistic(Object *p) {
    GameCharacter *gameCharacter = dynamic_cast<GameCharacter*>(p);
    cout << "Your status are:\n";
    cout << "Max health: " << gameCharacter->getMaxHealth() << '\n';
    cout << "Current health: " << gameCharacter->getCurrentHealth() << '\n';
    cout << "Attack: " << gameCharacter->getAttack() << '\n';
    cout << "Defense: " << gameCharacter->getDefense() << '\n';
}

/* Set & Get function*/
void Player::setCurrentRoom(Room* _room) {
    currentRoom = _room;
}
void Player::setPreviousRoom(Room* _room) {
    previousRoom = _room;
}
void Player::setInventory(vector<Item> _inventory) {
    inventory = _inventory;
}

Room* Player::getCurrentRoom() {
    return currentRoom;
}
Room* Player::getPreviousRoom() {
    return previousRoom;
}
vector<Item> Player::getInventory() {
    return inventory;
}