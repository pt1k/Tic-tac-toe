/**
 * @file    ttt.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   This is the main module of the Tic-tac-toe game.
 * @see https://en.wikipedia.org/wiki/Tic-tac-toe for more information about the game.
 */

#include <iostream>
using namespace std;

#include <cstdlib>
#include <vector>
#include <array>
#include <cstring>

#include "ttt.h"
#include "console.h"
#include "game.h"
#include "engine.h"

#ifndef NOGUI
#include "gui.h"
#endif

// unit tests of the rules functions
extern void testRules();

/**
 * Get user interaface class.
 * @param arg 1st command argument from user, if any
 * @return pointer to selected user interface class
 */
UserIf* getUserInterface(std::string arg)
{
#ifndef NOGUI
    if (arg != std::string("nogui")) {
        return new Gui();
    }
#endif

    return new Console();
}

/**
 * The main function of the Tic-tac-toe game.
 * Create the objects needed and start the game engine.
 */
int main(int argc, const char* argv[]) 
{

    testRules();

    auto ui = getUserInterface(argc >= 2 ? argv[1] : "");

    Game *game = new Game(ui);
    Engine engine(game, ui);
    
    while (engine.start());

    delete game;
    delete ui;
    
    return EXIT_SUCCESS;
}
    
