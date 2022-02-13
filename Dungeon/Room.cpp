#include "Room.h"

Room::Room() {
}

Room::Room(bool _isExit, int _index, vector<Object*> _objects): isExit(_isExit), index(_index), objects(_objects){
}

bool Room::popObject(Object* obj) {
    for(int i = 0, tmp = objects.size(); i < tmp; i++) {
        if(objects[i] == obj) {
            objects.erase(objects.begin()+i);
            // swap(objects[i], objects[tmp-1]);
            // objects.pop_back();
            break;
        }
    }
    
    // for(auto x: objects) {
    //     if(x == obj) {
    //         swap(x, *(objects.end()-1));
    //         objects.pop_back();
    //         break;
    //     }
    // }

    // for(auto it = objects.begin(); it != objects.end(); ++it)
    //     if(*it == obj)
    //         objects.erase(it);
    return 1;
}

void Room::setUpRoom(Room* _room) {
    upRoom = _room;
}
void Room::setDownRoom(Room* _room) {
    downRoom = _room;
}
void Room::setLeftRoom(Room* _room) {
    leftRoom = _room;
}
void Room::setRightRoom(Room* _room) {
    rightRoom = _room;
}
void Room::setFrontRoom(Room* _room) {
    FrontRoom = _room;
}
void Room::setBackRoom(Room* _room) {
    BackRoom = _room;
}

void Room::setIsExit(bool _isExit) {
    isExit = _isExit;
}
void Room::setIndex(int _index) {
    index = _index;
}
void Room::setObjects(vector<Object*> _objects) {
    objects = _objects;
}

bool Room::getIsExit() {
    return isExit;
}
int Room::getIndex() {
    return index;
}
vector<Object*>& Room::getObjects() {
    return objects;
}

Room* Room::getUpRoom() {
    return upRoom;
}
Room* Room::getDownRoom() {
    return downRoom;
}
Room* Room::getLeftRoom() {
    return leftRoom;
}
Room* Room::getRightRoom() {
    return rightRoom;
}
Room* Room::getFrontRoom() {
    return FrontRoom;
}
Room* Room::getBackRoom() {
    return BackRoom;
}