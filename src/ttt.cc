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
#include "gui.h"
#include "game.h"
#include "engine.h"

// unit tests of the rules functions
extern void testRules();

/**
 * The main function of the Tic-tac-toe game.
 * Create the objects needed and start the game engine.
 */
int main(int argc, const char* argv[]) 
{

    testRules();

    UserIf* ui;
    if (argc >= 2 && argv[1] == std::string("console"))
        ui = new Console();
    else
        ui = new Gui();
    
    Game *game = new Game(ui);
    Engine engine(game, ui);
    
    while (engine.start());

    delete game;
    delete ui;
    
    return EXIT_SUCCESS;
}
    
