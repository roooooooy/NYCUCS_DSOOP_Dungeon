#include "Record.h"

Record::Record(){
}

void Record::savePlayer(Player* player, ofstream& out) {
    out << player->getName() << '\n';
    out << player->getMaxHealth() << ' ';
    out << player->getCurrentHealth() << ' ';
    out << player->getAttack() << ' ';
    out << player->getDefense() << ' ';
    out << player->coin << '\n';
    out << player->getCurrentRoom()->getIndex() << ' ';
    if(player->getPreviousRoom() == nullptr) out << -1 << '\n';
    else out << player->getPreviousRoom()->getIndex() << '\n';
    out << player->getInventory().size() << '\n';
    for(auto x: player->getInventory()) {
        out << x.getName() << '\n';
        out << x.getHealth() << ' ';
        out << x.getAttack() << ' ';
        out << x.getDefense() << '\n';
    }
}
void Record::saveRooms(vector<Room>& rooms, ofstream& out) {
    out << rooms.size() << '\n';
    for(int i = 0; i < rooms.size(); i++) {
        if(rooms[i].getUpRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getUpRoom()->getIndex() << ' ';
        if(rooms[i].getDownRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getDownRoom()->getIndex() << ' ';
        if(rooms[i].getLeftRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getLeftRoom()->getIndex() << ' ';
        if(rooms[i].getRightRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getRightRoom()->getIndex() << ' ';
        if(rooms[i].getFrontRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getFrontRoom()->getIndex() << ' ';
        if(rooms[i].getBackRoom() == nullptr) out << -1 << ' ';
        else out << rooms[i].getBackRoom()->getIndex() << ' ';
        out << rooms[i].getIsExit() << '\n';
        // int item = 0, npc = 0, monster = 0;
        vector<Object*> item, npc, monster;
        for(auto x: rooms[i].getObjects()) {
            if(x->getTag() == "Item") item.push_back(x);
            if(x->getTag() == "NPC") npc.push_back(x);
            if(x->getTag() == "Monster") monster.push_back(x);
        }
        // item
        out << item.size() << '\n';
        for(auto x: item) {
            out << x->getName() << '\n';
            Item *_item = dynamic_cast<Item*>(x);
            out << _item->getHealth() << ' ';
            out << _item->getAttack() << ' ';
            out << _item->getDefense() << '\n';
        }
        // npc
        out << npc.size() << '\n';
        for(auto x: npc) {
            out << x->getName() << '\n';
            NPC *_npc = dynamic_cast<NPC*>(x);
            out << _npc->getScript();
            out << "-asdfghjkl-\n";
            out << _npc->getCommodity().size() << '\n';
            for(auto y: _npc->getCommodity()) {
                out << y.getName() << '\n';
                out << y.getHealth() << ' ';
                out << y.getAttack() << ' ';
                out << y.getDefense() << ' ';
                out << y.coin << '\n';
            }
        }
        // monster
        out << monster.size() << '\n';
        for(auto x: monster) {
            out << x->getName() << '\n';
            Monster *_monster = dynamic_cast<Monster*>(x);
            // out << _monster->getName() << '\n';
            out << _monster->getMaxHealth() << ' ';
            out << _monster->getCurrentHealth() << ' ';
            out << _monster->getAttack() << ' ';
            out << _monster->getDefense() << ' ';
            out << _monster->coin << '\n';
        }
    }
}
void Record::loadPlayer(Player* player, vector<Room> &rooms, ifstream& in) {
    string name; getline(in, name);
    int a, b, c, d, e; in >> a >> b >> c >> d >> e; in.ignore();    // add current health   
    *player = Player(name, a, b, c, d, e);
    in >> a >> b; in.ignore();
    player->setCurrentRoom(&rooms[a]);
    if(b == -1) player->setPreviousRoom(nullptr);
    else player->setPreviousRoom(&rooms[b]);
    // item (inventory)
    int n; in >> n; in.ignore();
    for(int i = 0; i < n; i++) {
        getline(in, name);
        int a, b, c; in >> a >> b >> c; in.ignore();
        Item *item = new Item(name, a, b, c, 0);
        player->addItem(*item);
    }
}
void Record::loadRooms(vector<Room>& r, ifstream& in) {
    int n;
    in >> n;
    r.clear();
    r.resize(n);
    for(int i = 0; i < n; i++) {
        r[i].setIndex(i);
        int a;
        in >> a; if(a != -1) r[i].setUpRoom(&r[a]);
        in >> a; if(a != -1) r[i].setDownRoom(&r[a]);
        in >> a; if(a != -1) r[i].setLeftRoom(&r[a]);
        in >> a; if(a != -1) r[i].setRightRoom(&r[a]);
        in >> a; if(a != -1) r[i].setFrontRoom(&r[a]);
        in >> a; if(a != -1) r[i].setBackRoom(&r[a]);
        in >> a; r[i].setIsExit(a);
        int m;
        // item
        in >> m; in.ignore();
        for(int j = 0; j < m; j++) {
            string _name; getline(in, _name);
            int a, b, c; in >> a >> b >> c; in.ignore();
            Object *obj = new Item(_name, a, b, c, 0);
            r[i].getObjects().push_back(obj);
        }
        // NPC
        in >> m; in.ignore();
        for(int j = 0; j < m; j++) {
            string _name; getline(in, _name);
            string scr = "", tmp;
            while(getline(in, tmp)) {
                if(tmp == "-asdfghjkl-") break;
                scr += tmp + '\n';
            }
            int num; in >> num; in.ignore();
            vector<Item> *com = new vector<Item>;
            for(int k = 0; k < num; k++) {
                string str; getline(in, str);
                int a, b, c, d; in >> a >> b >> c >> d; in.ignore();
                com->push_back(Item(str, a, b, c, d));
            }
            Object *obj = new NPC(_name, scr, *com);
            r[i].getObjects().push_back(obj);
        }
        // monster
        in >> m; in.ignore();
        for(int j = 0; j < m; j++) {
            string _name; getline(in, _name);
            int a, b, c, d, e; in >> a >> b >> c >> d >> e; in.ignore();
            Object *obj = new Monster(_name, a, b, c, d, e);
            r[i].getObjects().push_back(obj);
        }
    }
    // debug
    // for(int i = 0; i < n; i++) {
    //     cout << "for room " << i << ":\n";
    //     cout << "index: " << r[i].getIndex() << '\n';
    //     if(r[i].getUpRoom() != nullptr) cout << "up: " << r[i].getUpRoom()->getIndex() << '\n';
    //     if(r[i].getDownRoom() != nullptr) cout << "down: " << r[i].getDownRoom()->getIndex() << '\n';
    //     if(r[i].getLeftRoom() != nullptr) cout << "left: " << r[i].getLeftRoom()->getIndex() << '\n';
    //     if(r[i].getRightRoom() != nullptr) cout << "right: " << r[i].getRightRoom()->getIndex() << '\n';
    // }
    // cout << '\n';
}

void Record::saveToFile(Player* p, vector<Room>& r, ofstream& out) {
    saveRooms(r, out);
    savePlayer(p, out);
}

void Record::loadFromFile(Player* p, vector<Room>& r, ifstream& in) {
    loadRooms(r, in);
    loadPlayer(p, r, in);
}
