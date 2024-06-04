#include "maze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
/*
class myRoom{
public:
    void set(int, char);
    int x_;
    char y_;
}
*/

Room :: Room() : x_(-1), y_('*') {}



void Room::pick() {

    int randomX = rand() % mazeSize_ + 1;
    char randomY = 'a' + rand() % mazeSize_;

    x_ = randomX;
    y_ = randomY;

}



const Room Room :: pickAdjacent() {

    char randDirection;

    char Direction[]{ 'u' , 'd', 'l', 'r' };   // intializes array containing directions

    do {
        randDirection = Direction[rand() % 4];
    } while (!goodDirection(randDirection)); // checks if direction is valid

    return createAdjacent(randDirection); // returns coordinates for new room
}


const Room Room :: nextMove() const {

    cout << "What direction do you want to move: [u,d,l,r] - press q to quit" << endl;
    char direction;
    cin >> direction;

    if (direction == 'q') {   // quits if player enters q
        cout << "quiting" << endl;
       // return Room {-1, '*' };
    }
    else if (!goodDirection(direction)) {    // determines if selected direction is invalid
        cout << "Invalid direction" << endl;
    }
    else
        return createAdjacent(direction);    // returns coordinates of new room
}



void Room :: print() const {
    cout << x_ << y_;   // prints x and y co-rdinates of room
}


bool Room :: goodDirection(const char dr) const {
    if (dr == 'u') {
        return (y_ != 'a' ? true : false);
    }
    else if (dr == 'd') {
        return (y_ != 'a' + mazeSize_ - 1 ? true : false);
    }
    else if (dr == 'l') {
        return (x_ != 1 ? true : false);
    }
    else if (dr == 'r') {
        return (x_ != mazeSize_ ? true : false);
    }
    else
        return false;
}

const Room Room::createAdjacent(const char dr)const {

    Room adjacentRm;
    adjacentRm.x_ = x_;
    adjacentRm.y_ = y_;

    switch (dr) { // creates adjacent room coordinates
    case 'u':
        --adjacentRm.y_; // moves y-axis up
        break;
    case 'd':
        ++adjacentRm.y_; // moves y-axis down
        break;
    case 'l':
        --adjacentRm.x_; // move x-axis left
        break;
    case 'r':
        ++adjacentRm.x_; // move x-axis right
        break;
    }

    return adjacentRm; // return coordinates
}


bool matchRoom(const Room& room1, const Room& room2) {
    if (room1.x_ == room2.x_ && room1.y_ == room2.y_)
        return true;
    else
        return false;
}



// functions for RoomPair
//

void RoomPair::pick() {

    Room firstRoom;
    firstRoom.pick();
    one_ = firstRoom;

    // uses pick adjacent to create random wall
    Room secondRoom;
    secondRoom = firstRoom.pickAdjacent();
    two_ = secondRoom;
}

void RoomPair::print() const {
    Room firstRoom = one_;
    Room secondRoom = two_;
 
    firstRoom.print();
    cout << "|";
    secondRoom.print();

    cout << " ";
      
}

bool matchPair(const RoomPair& roomPair1, const RoomPair& roomPair2) {
   bool matchCheck = (matchRoom(roomPair1.one_, roomPair2.one_) && matchRoom(roomPair1.two_, roomPair2.two_));
   bool matchCheckReverse = (matchRoom(roomPair1.one_, roomPair2.two_) && matchRoom(roomPair1.two_, roomPair2.one_));

   return matchCheck || matchCheckReverse;  // checks if rooms within room pairs have same coordinates

}



// maze functions
//
void Maze::print() const {

    for (int i = 0; i < numWalls_; ++i) {
          walls_[i].print(); 
    }

    //currentRoom_.print();
}

void Maze::build() {

    for (int i = 0; i < numWalls_; ++i) {
        RoomPair wallLocation;

        do {
            wallLocation.pick();
        } while (checkMaze(wallLocation)); // checks if Walls co-ordinates are the same as room co-ordinates

        walls_[i] = wallLocation; // assigns Walls the coordinates of wallLocation
    }

}

bool Maze :: move(const Room& moveRoom) {

    RoomPair roomMove(currentRoom_, moveRoom);

    if (checkMaze(roomMove))
        return false;
    else
        return true;

}


































/*

void clearWalls(RoomPair Walls[]) {
    for (int i = 0; i < numWalls; ++i) {  // assigns myMaze array with {-1,*} cooirdinates

        Walls[i].one.x = -1;
        Walls[i].one.y = '*';

        Walls[i].two.x = -1;
        Walls[i].two.y = '*';
    }
}

bool goodDirection(const Room& rm, const char dr) {

    // checks chosen direction and returns true or false value
    if (dr == 'u') {
        return (rm.y != 'a' ? true : false);
    }
    else if (dr == 'd') {
        return (rm.y != 'a' + mazeSize - 1 ? true : false);
    }
    else if (dr == 'l') {
        return (rm.x != 1 ? true : false);
    }
    else if (dr == 'r') {
        return (rm.x != mazeSize ? true : false);
    }
    else
        return false;
}



Room createAdjacent(const Room& rm, const char dr) {
    Room adjacentRm = rm;  // assigns adjacent room same coordinates as current room

    switch (dr) { // creates adjacent room co-ordinates
    case 'u':
        --adjacentRm.y; // moves y-axis up
        break;
    case 'd':
        ++adjacentRm.y; // moves y-axis down
        break;
    case 'l':
        --adjacentRm.x; // move x-axis left
        break;
    case 'r':
        ++adjacentRm.x; // move x-axis right
        break;
    }

    return adjacentRm; // return coordinates
}

const Room pickAdjacent(const Room& rm) {

    char randDirection;

    char Direction[]{ 'u' , 'd', 'l', 'r' };   // intializes array containing directions

    do {
        randDirection = Direction[rand() % 4];
    } while (!goodDirection(rm, randDirection)); // checks if direction is valid

    return createAdjacent(rm, randDirection); // returns coordinates for new room
}

const RoomPair pickPair() {

    RoomPair room;

    // assingns room one random x,y coordinates
    room.one.x = rand() % mazeSize + 1;
    room.one.y = 'a' + rand() % mazeSize;

    room.two = pickAdjacent(room.one); // picks random adjacent room to room.one

    return room;  // returns the room pair
}


bool matchRoom(const Room& r1, const Room& r2) {

    if (r1.x == r2.x && r1.y == r2.y)    // checks if rooms have same co-ordinates
        return true;
    else
        return false;
}


bool matchPair(const RoomPair& roomPair1, const RoomPair& roomPair2) {

    return (matchRoom(roomPair1.one, roomPair2.one) && matchRoom(roomPair1.two, roomPair2.two)) || (matchRoom(roomPair1.one, roomPair2.two) && matchRoom(roomPair1.two, roomPair2.one)); // checks if rooms within room pairs have same coordinates

}


bool checkMaze(const RoomPair Walls[], const RoomPair& roomPair) {

    for (int i = 0; i < numWalls; ++i) {
        if (matchPair(Walls[i], roomPair)) {    // uses match pair to check if Walls coordinates are same is roomPair
            return true;
        }
        else
            return false;
    }
}


void build(RoomPair Walls[]) {

    for (int i = 0; i < numWalls; ++i) {
        RoomPair wallLocation;

        do {
            wallLocation = pickPair();
        } while (checkMaze(Walls, wallLocation)); // checks if Walls co-ordinates are the same as room co-ordinates

        Walls[i] = wallLocation; // assigns Walls the coordinates of wallLocation
    }
}


void printRoom(const Room& rm) {
    cout << rm.x << "," << rm.y;   // prints x and y co-ordinates of room
}


void printPair(const RoomPair& rm) { // prints our coordinates of rooms within the roomPair

    printRoom(rm.one);

    cout << "  ,  ";

    printRoom(rm.two);

    cout << "  ,  ";
}


void printMaze(const RoomPair Walls[]) {
    for (int i = 0; i < numWalls; ++i) {

        printPair(Walls[i]); // prints co-ordinates of internal walls
    }
}


const Room nextMove(const Room& currentRoom) {

    cout << "What direction do you want to move: [u,d,l,r] - press q to quit" << endl;
    char direction;
    cin >> direction;

    if (direction == 'q') {   // quits if player enters q
        cout << "quiting" << endl;
        return { -1, '*' };
    }
    else if (!goodDirection(currentRoom, direction)) {    // determines if selected direction is invalid
        cout << "Invalid direction" << endl;
    }
    else
        return createAdjacent(currentRoom, direction);    // returns co-ordinates of new room
}
*/