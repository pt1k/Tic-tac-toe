/**
 * @file    userif.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   Console user interface.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cstdlib>

#include "ttt.h"
#include "userif.h"

/**
 * Ask player's name from the user.
 */
std::string UserIf::askPlayerName(int playerNumber) const
{
    std::string name;
    
    printf("Enter player %d name: ", playerNumber);
    std::cin >> name;
    
    return name;
}

/** 
 * Ask from the user if the player is computer/machine or human.
 */
bool UserIf::askIfMachine(void) const
{
    std::string answer;
    
    while (true) {
        printf("Human or Machine (H/M): ");
        std::cin >> answer;
        if (tolower(answer[0]) == 'h')
            return false;
        if (tolower(answer[0]) == 'm')
            return true;
    }
}

/**
 * Ask next move from the player.
 */
int UserIf::askMove (const boardMtx__t& mtx, char symbol, std::string& name, int preferred)
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
bool UserIf::askToPlayAgain(void)
{
    char answer;
    
    printf("Play again (Y/N): ");
    std::cin >> answer;
    
    return (toupper(answer) == 'Y');
}

/**
 * Clear the screen for a new game.
 */
void UserIf::clear(void)
{
    //printf("UserIf::clear() ..\n");
    printf("\n\n----------------------------------------\n\n");
}

/**
 * Display the game board on the screen.
 */
void UserIf::showBoard(const boardMtx__t& pm) 
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
void UserIf::showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2)
{
    printf("\n\n\t%s: %d  Draws: %d  %s: %d\n\n", name1.data(), score1, draws, name2.data(), score2);
}

