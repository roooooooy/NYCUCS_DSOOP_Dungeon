#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"

using namespace std;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */

class Record
{
private:
public:
    void savePlayer(Player*, ofstream&);
    void saveRooms(vector<Room>&, ofstream&);
    void loadPlayer(Player*, vector<Room>&, ifstream&);
    void loadRooms(vector<Room>&, ifstream&);
    
    Record();
    void saveToFile(Player*, vector<Room>&, ofstream&);
    void loadFromFile(Player*, vector<Room>&, ifstream&);
};

#endif // RECORD_H_INCLUDED
