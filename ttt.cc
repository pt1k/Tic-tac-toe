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

#include "ttt.h"
#include "userif.h"
#include "game.h"
#include "engine.h"

// unit tests of the rules functions
extern void testRules();

/**
 * The main function of the Tic-tac-toe game.
 * Create the objects needed and start the game engine.
 */
int main(int argc, char **argv) 
{

    testRules();
    
    UserIf ui;
    Game game(&ui);
    Engine engine(&game, &ui);
    
    while (engine.start());

    return EXIT_SUCCESS;
}
    
