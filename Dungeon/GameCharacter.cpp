#include "GameCharacter.h"

GameCharacter::GameCharacter(): Object("GameCharter") {
}

GameCharacter::GameCharacter(string _tag): Object(_tag) {
}

GameCharacter::GameCharacter(string _name, string _tag, int _health, int _attack, int _defense): Object(_name, _tag), maxHealth(_health), currentHealth(_health), attack(_attack), defense(_defense) {
}

GameCharacter::GameCharacter(string _name, string _tag, int _health1, int _health2, int _attack, int _defense): Object(_name, _tag), maxHealth(_health1), currentHealth(_health2), attack(_attack), defense(_defense) {
}

bool GameCharacter::checkIsDead() {
    if(currentHealth <= 0) return 1;
    return 0;
}
int GameCharacter::takeDamage(int demage) {
    if(demage > defense) currentHealth -= demage - defense;
    return 0;
}

// void GameCharacter::showStatistic( *p) {
//     GameCharacter *gameCharacter = dynamic_cast<GameCharacter*>(p);
//     cout << "Max health: " << gameCharacter->getMaxHealth() << '\n';
//     cout << "Current health: " << gameCharacter->getCurrentHealth() << '\n';
//     cout << "Attack: " << gameCharacter->getAttack() << '\n';
//     cout << "Defense: " << gameCharacter->getDefense() << '\n';
// }

/* Set & Get function*/
void GameCharacter::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
void GameCharacter::setCurrentHealth(int _currentHealth) {
    currentHealth = _currentHealth;
}
void GameCharacter::setAttack(int _attack) {
    attack = _attack;
}
void GameCharacter::setDefense(int _defense) {
    defense = _defense;
}

int GameCharacter::getMaxHealth() {
    return maxHealth;
}
int GameCharacter::getCurrentHealth() {
    return currentHealth;
}
int GameCharacter::getAttack() {
    return attack;
}
int GameCharacter::getDefense() {
    return defense;
}