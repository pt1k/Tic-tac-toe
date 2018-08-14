/**
 * @file    gui.cc
 * @author  Pekka Koivuniemi
 * @date    20 Jul 2018
 * @version 0.1
 * @brief   Graphical user interface.
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "ttt.h"
#include "gui.h"

    
/**
 * Ask player's name from the user.
 */
std::string Gui::askPlayerName(int playerNumber)
{
    return Curse::askPlayerName(playerNumber);
}
/**/

/** 
 * Ask from the user if the player is computer/machine or human.
 */
bool Gui::askIfMachine(int playerNumber)
{
    return Curse::askIfMachine(playerNumber);
}

/**
 * Set next player's turn
 */
void Gui::setTurn(char symbol)
{
    Curse::setTurn(symbol);
}


/**
 * Ask next move from the player.
 */
int Gui::askMove (const boardMtx__t& mtx, char symbol, std::string& name, int preferred)
{
    int move;
    selectionType selType;

    Curse::setTurn(symbol);

    Curse::getSelection(move, selType);
    
    if (move == 'q' || move == 'Q')
        move = TERMINATE__C;
    else
        move++; // [0,8] --> [1,9]
    
    return move;
}

/** 
 * Ask from the user if they want to play again.
 */
bool Gui::askToPlayAgain(void)
{
    return Curse::askToPlayAgain();
}

/**
 * Clear the screen for a new game.
 */
void Gui::clear(void)
{
    Curse::clear();
}

/**
 * Display the game board on the screen.
 */
void Gui::showBoard(const boardMtx__t& pm, winLine__t& wl) 
{
    Curse::showBoard(pm, wl);
}

/**
 * Display scores on the screen.
 */
void Gui::showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2)
{
    Curse::showScores(name1, score1, draws, name2, score2);
}

