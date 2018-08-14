/**
 * @file    console.cc
 * @author  Pekka Koivuniemi
 * @date    20 April 2018
 * @version 0.1
 * @brief   Console user interface.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cstdlib>

#include "ttt.h"
#include "console.h"

    
/**
 * Ask player's name from the user.
 */
string Console::askPlayerName(int playerNumber) const
{
    std::string name;
    
    printf("Enter player %d name: ", playerNumber);
    std::cin >> name;
    
    return name;
}

/** 
 * Ask from the user if the player is computer/machine or human.
 */
bool Console::askIfMachine(int playerNumber) const
{
    std::string answer;
    
    while (true) {
        printf("Human or Machine (H/M): ");
        std::cin >> answer;
        if (toupper(answer[0]) == 'H')
            return false;
        if (toupper(answer[0]) == 'M')
            return true;
    }
}

/**
 * Ask next move from the player.
 */
int Console::askMove (const boardMtx__t& mtx, char symbol, std::string& name, int preferred)
{
    int move;

    if (preferred)
        printf("%s, make a move for '%c' (prefer %d): ", name.data(), symbol, preferred);
    else
        printf("%s, make a move for '%c': ", name.data(), symbol);
    std::cin >> move;
    
    if (move == 0)
        move = TERMINATE__C;
    
    return move;
}

/** 
 * Ask from the user if they want to play again.
 */
bool Console::askToPlayAgain(void)
{
    char answer;
    
    printf("Play again (Y/N): ");
    std::cin >> answer;
    
    return (toupper(answer) == 'Y');
}

/**
 * Set next player's turn
 * We do nothing with it.
 */
void Console::setTurn(int playerNumber) 
{
    return;
}

/**
 * Clear the screen for a new game.
 */
void Console::clear(void)
{
    //printf("Console::clear() ..\n");
    printf("\n\n----------------------------------------\n\n");
}

/**
 * Display the game board on the screen.
 */
void Console::showBoard(const boardMtx__t& pm) 
{
    
    const char *p = "              ";
    
    boardMtx__t m;
    for (size_t i = 0; i < m.size(); i++) {
        m[i] = (pm[i] == n__C) ? (char)i + '1': pm[i];
    }
    
    printf("%s %c | %c | %c \n",  p, m[0], m[1], m[2]);
    printf("%s---|---|---\n", p);
    printf("%s %c | %c | %c \n", p, m[3], m[4], m[5]);
    printf("%s---|---|---\n", p);
    printf("%s %c | %c | %c \n", p, m[6], m[7], m[8]);
    
}

/**
 * Display scores on the screen.
 */
void Console::showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2)
{
    printf("\n\n\t%s: %d  Draws: %d  %s: %d\n\n", name1.data(), score1, draws, name2.data(), score2);
}

