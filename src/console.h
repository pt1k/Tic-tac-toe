/**
 * @file    console.h
 * @author  Pekka Koivuniemi
 * @date    20 April 2018
 * @version 0.1
 * @brief   Definitions for user console interface.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "userif.h"

/**
 * User interface class for console i/o.
 */
class Console: public UserIf
{
    
  public:
    /**
     * Constructor.
     */
    Console() {};

    /**
     * Ask player's name from the user.
     * @param playerNumber the order number of the player
     * @return the name entered by the user
     */
    string askPlayerName(int playerNumber) const;

    /** 
     * Ask from the user if the player is computer/machine or human.
     * @return true:  player is computer/machine. 
     *         false: player is human
     */
    bool askIfMachine(void) const;
    
    /**
     * Ask next move from the player.
     * @param mtx game board with symbols
     * @param symbol player's game symbol
     * @param name player's name
     * @param preferred preferred move, just a hint to the user for best move
     * @return answer the user entered
     */
    int askMove(const boardMtx__t& mtx, char symbol, std::string& name, int preferred);

    /** 
     * Ask from the user if they want to play again.
     * @return true: they want to play again. false: they want to quit playing
     */
    bool askToPlayAgain(void);

    /**
     * Clear the screen for a new game.
     */
    void clear(void);

    /**
     * Display the game board on the screen.
     * @param mtx game board with symbols
     */
    void showBoard(const boardMtx__t& mtx);

    /**
     * Display scores on the screen.
     * @param name1 name of the player 1
     * @param score1 score of the player 1
     * @param draws number of draws 
     * @param name1 name of the player 2
     * @param score1 score of the player 2
     */
    void showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2);
};

#endif
