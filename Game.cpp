// Mikhail Nesterenko
// tests class-based Maze function implementation
// 3/23/2023

#include <iostream>
#include "maze.h"

using std::cout; using std::cin; using std::endl;

int main() {
    // 
    // checking room functions
    // 
    // srand(time(nullptr)); // random seed
    srand(1); // fixed seed


    Maze myMaze;

    myMaze.start(); // sets start room

    Room cheeseRoom;
    cheeseRoom.makeCheeseRoom();

    myMaze.build();

    char answer;
    cout << "do you want to see wall positions? [y/n]: ";
    cin >> answer;

    if (answer == 'y') {
        cout << "Wall positions:" << endl;
        myMaze.print();
        cout << endl;
        }

    while (!matchRoom(myMaze.getCurrentRoom(), cheeseRoom) && !matchRoom(myMaze.getCurrentRoom(), Room())) {  // current room is not the end room or -1 *

        Room currentRoom = myMaze.getCurrentRoom();

        cout << "Current room: ";
        currentRoom.print();
        cout << endl;

        Room moveRoom = currentRoom.nextMove(); // assigns next room coordinates based on current room

        if (!myMaze.move(moveRoom)) { // checks if move hits a wall
            cout << "hit wall!" << endl;
        }
    }

    cout << "current room :"; myMaze.getCurrentRoom().print(); cout << endl; // outputs current room after exiting loop

    if(matchRoom(myMaze.getCurrentRoom(), cheeseRoom)) // if current room matches cheese room
            cout << "you win!!!" << endl;
}