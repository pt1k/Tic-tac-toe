/**
 * @file    gui.h
 * @author  Pekka Koivuniemi
 * @date    20 April 2018
 * @version 0.1
 * @brief   Definitions for graphical user interface.
 */

#ifndef GUI_H
#define GUI_H

#include <iostream>

#include "curse.h"
#include "userif.h"

/**
 * User interface class for graphical i/o.
 */
class Gui: public Curse, public UserIf
{
    
  public:
    /**
     * Constructor.
     */
    Gui() {};

    /**
     * Ask player's name from the user.
     * @param playerNumber the order number of the player
     * @return the name entered by the user
     */
    std::string askPlayerName(int playerNumber);
    /**/

    /** 
     * Ask from the user if the player is computer/machine or human.
     * @param playerNumber the order number of the player
     * @return true:  player is computer/machine. 
     *         false: player is human
     */
    bool askIfMachine(int playerNumber);

    /**
     * Set next player's turn
     * It can be a human or machine.
     * @param symbol next player's playing symbol
     */
    void setTurn(char symbol);

    
    /**
     * Ask next move from the player.
     * @param mtx game board with symbols
     * @param symbol player's game symbol
     * @param name player's name
     * @param preferred preferred move, just a hint to the user for best move
     * @return cell number [1,9] on the game board 
     *         or 0 if user wants to quit the game
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

    /**
     * Display game result (winner or draw, winning line).
     * @param winLine winning line indices [0,8] on the game board
     */
    void showGameResult(winLine__t& winLine);

    /**
     * Ask for an user interaction to start a new game.
     * @return true for a new game, false to quit
     */
    bool askReadyForNewGame();

};

#endif
