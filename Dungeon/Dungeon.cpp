#include "Dungeon.h"

Dungeon::Dungeon(): end(0), first(1) {
}

// Create a new player, and give him/her basic status 
void Dungeon::createPlayer() {
    cout << "Please enter your name: ";
    string name;
    getline(cin, name);
    cout << '\n';
    std::ifstream file;
    file.open(name + ".txt");
    if(file) {
        cout << "-----------------------------------------------\n";
        cout << "The player had been created before!\n";
        // cout << "Please choose another player name, or load \"" << name << ".txt\".\n";
        // cout << "If you want to restart " << name << "'s Dungeon travel, please go to folder and delete \"" << name << ".txt\".\n";
        cout << "0: Choose another player name.\n";
        cout << "1: Load \"" << name << ".txt\".\n";
        cout << "2: Restart " << name << "'s Dungeon travel (it will overwrite the previous file if you choose \"record game status\" latter ).\n";
        string str;
        while(1) {
            getline(cin, str);
            cout << '\n';
            if(str.length() == 0) {
                cout << "Invalid! Please choose an action: ";
                continue;
            }
            if(str.length() > 1) {
                cout << "Invalid! Please input only one charater: ";
                continue;
            }
            if(str[0] < '0' || str[0] > '2') {
                cout << "Invalid! Please choose a valid action: ";
                continue;
            }
            break;
        }
        if(str[0] == '0') { //choose another player name
            createPlayer();
        }
        else if(str[0] == '1') {    //load the previous file
            Record re;
            re.loadFromFile(&player, rooms, file);
            file.close();
        }
        else {  //restart and overwrite
            cout << "Hello, " << name << "!\n\n";
            player.setName(name);
            file.close();
        }
        // startGame();
        return;
    }
    cout << "Hello, " << name << "!\n\n";
    player.setName(name);
}

// Create a map, which include several different rooms 
void Dungeon::createMap() {
    // Record re;
    // re.loadFromFile(&player, rooms, file);
    // std::ifstream file;
    // file.open("room.txt");
    // re.loadRooms(rooms, file);
    // file.close();
}

// Deal with player's moveing action 
void Dungeon::handleMovement() {
    vector<string> options;
    if(player.getCurrentRoom()->getUpRoom() != nullptr) {
        options.push_back({"Go up"});
    }
    if(player.getCurrentRoom()->getDownRoom() != nullptr) {
        options.push_back({"Go down"});
    }
    if(player.getCurrentRoom()->getLeftRoom() != nullptr) {
        options.push_back({"Go left"});
    }
    if(player.getCurrentRoom()->getRightRoom() != nullptr) {
        options.push_back({"Go right"});
    }
    if(player.getCurrentRoom()->getFrontRoom() != nullptr) {
        options.push_back({"Go front"});
    }
    if(player.getCurrentRoom()->getIndex() == 1 && GoToBoss == 0) {
        options.pop_back();
    }
    if(player.getCurrentRoom()->getBackRoom() != nullptr) {
        options.push_back({"Go back"});
    }
    options.push_back("Cancel");
    int cnt = 0;
    for(auto x: options) {
        cout << cnt++ << ": " << x << ".\n";
    }
    cout << "Choose an direction to move: ";
    string str;
    while (1) {
        getline(cin, str);
        cout << '\n';
        if(str.length() == 0) {
            cout << "Invalid! Please choose an action: ";
            continue;
        }
        if(str.length() > 1) {
            cout << "Invalid! Please input only one charater: ";
            continue;
        }
        if(str[0] >= cnt + '0' || str[0] < '0') {
            cout << "Invalid! Please choose a valid action: ";
            continue;
        }
        break;
    }
    int choose = str[0] - '0';

    if(options[choose][3] == 'u') {
        player.changeRoom(player.getCurrentRoom()->getUpRoom());
        cout << "You have gone up.\n";
    }
    else if(options[choose][3] == 'd') {
        player.changeRoom(player.getCurrentRoom()->getDownRoom());
        cout << "You have gone down.\n";
    }
    else if(options[choose][3] == 'l') {
        player.changeRoom(player.getCurrentRoom()->getLeftRoom());
        cout << "You have gone left.\n";
    }
    else if(options[choose][3] == 'r') {
        player.changeRoom(player.getCurrentRoom()->getRightRoom());
        cout << "You have gone right.\n";
    }
    else if(options[choose][3] == 'f') {
        player.changeRoom(player.getCurrentRoom()->getFrontRoom());
        cout << "You have gone left.\n";
    }
    else if(options[choose][3] == 'b') {
        player.changeRoom(player.getCurrentRoom()->getBackRoom());
        cout << "You have gone right.\n";
    }
    else {
        return;
    }
    cout << "You are in the room " << player.getCurrentRoom()->getIndex() << ".\n\n";
}

// Deal with player's iteraction with objects in that room 
void Dungeon::handleEvent(Object* obj) {
    if(obj->triggerEvent(&player)) {    //for item and monster
        player.getCurrentRoom()->popObject(obj);
    }
}

// Deal with all game initial setting       
// Including create player, create map etc  
void Dungeon::startGame() {
    cout << "-----------------------------------------------\n";
    cout << "0: Start a new game.\n";
    cout << "1: Load previous record.\n";
    string str;
    while(1) {
        getline(cin, str);
        cout << '\n';
        if(str.length() == 0) {
            cout << "Invalid! Please choose an action: ";
            continue;
        }
        if(str.length() > 1) {
            cout << "Invalid! Please input only one charater: ";
            continue;
        }
        if(str[0] < '0' || str[0] > '1') {
            cout << "Invalid! Please choose a valid action: ";
            continue;
        }
        break;
    }
    Record re;
    std::ifstream file;
    if(str[0] == '0') {
        file.open("default.txt");
        re.loadFromFile(&player, rooms, file);
        file.close();
        createPlayer();
        // newgame = 1;
    }
    else {
        cout << "-----------------------------------------------\n";
        cout << "Input the file name: ";
        string fileName;
        getline(cin, fileName);
        fileName += ".txt";
        cout << '\n';
        file.open(fileName);
        if(!file) {
            cout << "Invalid file name!\n";
            startGame();
            return;
        }
        re.loadFromFile(&player, rooms, file);
        file.close();
        cout << "You have loaded it successfully!\n\n";
        cout << "Hello, " << player.getName() << "!\n\n";
    }
    GoToBoss = 1;
    for(int i = 4; i <= 7; i++) {
        for(auto x: rooms[i].getObjects()) {
            if(x->getTag() == "Monster") {
                GoToBoss = 0;
                break;
            }
        }
    }
    if(GoToBoss) first = 0;
}
 
void Dungeon::chooseAction(vector<Object*> object) {
    vector<string> options;
    options.push_back("Move");
    options.push_back("Status");
    options.push_back("Backpack");
    options.push_back("Leave");
    for(auto x: object) {
        if(x->getTag() == "Item") {
            options.push_back("Pick up the " + x->getName());
        }
        else if(x->getTag() == "Monster") {
            options.push_back("Fight against " + x->getName());
        }
        else if(x->getTag() == "NPC") {
            options.push_back("Talk to " + x->getName());
        }
    }
    if(player.getCurrentRoom()->getIsExit() == 1) {
        bool canExit = 1;
        for(auto x: options) {
            if(x[0] == 'F') {
                canExit = 0;
                break;
            }
        }
        if(canExit) options.push_back("Exit (Victory)");
    }
    cout << "-----------------------------------------------\n";
    cout << "You have the following options:\n";
    int cnt = 0;
    for(auto x: options) {
        cout << cnt++ << ": " << x << ".\n";
        for(auto y: object) {
            if(x == "Pick up the " + y->getName()) {
                Item *item = dynamic_cast<Item*>(y);
                item->output("       "); //add tab
                break;
            }
            else if(x == "Fight against " + y->getName()) {
                Monster *monster = dynamic_cast<Monster*>(y);
                monster->output("       "); //add tab
                break;
            }
        }
    }
    // cout << "";
    // cout << "Please enter an options index: ";
    string str;
    while(1) {
        getline(cin, str);
        cout << '\n';
        if(str.length() == 0) {
            cout << "Invalid! Please choose an action: ";
            continue;
        }
        if(str.length() > 1) {
            cout << "Invalid! Please input only one charater: ";
            continue;
        }
        if(str[0] >= cnt + '0' || str[0] < '0') {
            cout << "Invalid! Please choose a valid action: ";
            continue;
        }
        break;
    }
    int choose = str[0] - '0';
    cout << "-----------------------------------------------\n";
    if(choose == 0) {
        // move
        // cout << "Choose an direction to move.\n";
        bool canmove = 1;
        for(auto x: options) {
            if(x[0] == 'F') {
                canmove = 0;
                break;
            }
        }
        if(canmove) handleMovement();
        if(canmove) return;

        cout << "Because there is a monster, you can only move to previous room.\n\n";
        cout << "0: Go to previous room.\n";
        cout << "1: Stay here.\n";
        
        string str;
        while(1) {
            getline(cin, str);
            cout << '\n';
            if(str.length() == 0) {
                cout << "Invalid! Please choose an action: ";
                continue;
            }
            if(str.length() > 1) {
                cout << "Invalid! Please input only one charater: ";
                continue;
            }
            if(str[0] < '0' || str[0] > '1') {
                cout << "Invalid! Please choose a valid action: ";
                continue;
            }
            break;
        }
        if(str[0] == '0') {
            player.changeRoom(player.getPreviousRoom());
            cout << "You back to the previous room.\n";
            cout << "You are in room " << player.getCurrentRoom()->getIndex() << ".\n\n";
        }
    }
    else if(choose == 1) {
        // show status
        player.triggerEvent(&player);
    }
    else if(choose == 2) {
        // check backpack
        if(player.getInventory().size()) cout << "You have the following items:\n\n";
        else cout << "You have no item in your backpack now.\n";
        for(auto x: player.getInventory()) {
            x.output(""); cout << '\n';
        }
        // cout << '\n';
    }
    else if(choose == 3) {
        // record system
        cout << "0: Record game status.\n";
        cout << "1: Leave without saving.\n";
        cout << "2: Cancel.\n";
        // cout << "";
        // cout << "Please enter an options: ";
        // add while 
        string str;
        while(1) {
            getline(cin, str);
            cout << '\n';
            if(str.length() == 0) {
                cout << "Invalid! Please choose an action: ";
                continue;
            }
            if(str.length() > 1) {
                cout << "Invalid! Please input only one charater: ";
                continue;
            }
            if(str[0] < '0' || str[0] > '2') {
                cout << "Invalid! Please choose a valid action: ";
                continue;
            }
            break;
        }
        if(str[0] == '2') {
            //do nothing
        }
        else if(str[0] == '0') {
            Record re;
            std::ofstream file;
            // create a new file in folder ""
            
            string filename = player.getName() + ".txt";
            // if the filename already exist: 
            //  if choose start a new game, then save filename(1)
            //  if choose start from file, then overwrite it
            // if(!newgame) {
            // }
            file.open(filename);    // default will overwrite the file
            // cout << "live\n";
            re.saveToFile(&player, rooms, file);
            file.close();
            // cout << "still live\n";
            end = 2;
        }
        else {
            end = 2;
        }
    }
    else if(options[choose][0] == 'E') {
        end = 1;
    }
    else {
        for(auto x: object) {
            if(options[choose] == "Pick up the " + x->getName()) {
                handleEvent(x);
                break;
            }
            else if(options[choose] == "Fight against " + x->getName()) {
                handleEvent(x);
                break;
            }
            else if(options[choose] == "Talk to " + x->getName()) {
                handleEvent(x);
                break;
            }
        }
    }
    // cout << "leave the choose action\n";
}

// Check whether the game should end or not 
// Including player victory, or he/she dead 
bool Dungeon::checkGameLogic() {
    // cout << "in check game logic\n";
    if(end == 1) {
        cout << "-----------------------------------------------\n";
        cout << "------------------- Victory -------------------\n";
        cout << "--------------- You Won The Game --------------\n";
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n\n";
        return 0;
    }
    if(end == 2) {
        cout << "You quited game.\n";
        return 0;
    }
    if(player.getCurrentHealth() <= 0) {
        cout << "-----------------------------------------------\n";
        cout << "------------------ Game Over ------------------\n";
        cout << "-----------------------------------------------\n\n";
        return 0;
    }
    GoToBoss = 1;
    for(int i = 4; i <= 7; i++) {
        for(auto x: rooms[i].getObjects()) {
            if(x->getTag() == "Monster") {
                GoToBoss = 0;
                break;
            }
        }
    }

    if(GoToBoss && first) {
        first = 0;
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n";
        cout << "------------ Dong...... Dong...... ------------\n";
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n\n";

        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n";
        cout << "- You heard a muffled sound from somewhere... -\n";
        cout << "-- It might make by a original locked gate... -\n";
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n";
        cout << "-----------------------------------------------\n\n";
    }
    return 1;
}

// Deal with the whole game process 
void Dungeon::runDungeon() {
    cout << "-----------------------------------------------\n";
    cout << "------------- WELLCOME TO DUNGEON -------------\n";
    startGame();
    while(checkGameLogic()) {
        chooseAction(player.getCurrentRoom()->getObjects());
    }
}
