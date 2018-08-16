/**
 * @file    curse.h
 * @author  Pekka Koivuniemi
 * @date    20 Jul 2018
 * @version 0.1
 * @brief   Definitions for curses graphical user interface of the Tic-tac-toe game.
 */

#ifndef CURSE_H
#define CURSE_H

#include <iostream>
#include <vector>

#include <ncurses.h>

#include "ttt.h"

class Curse
{

public:

    /**
     * Ask player's name from the user.
     * @param playerNumber the order number of the player
     * @return the name entered by the user
     */
    std::string askPlayerName(int playerNumber);

    /** 
     * Ask from the user if the player is computer/machine or human.
     * @param playerNumber the order number of the player
     * @return true:  player is computer/machine. 
     *         false: player is human
     */
    virtual bool askIfMachine(int playerNumber);

    /** 
     * Ask from the user if they want to play again.
     * @return true: they want to play again. false: they want to quit playing
     */
    bool askToPlayAgain(void);

    /**
     * Set next player's turn
     * It can be a human or machine.
     * @param symbol next player's playing symbol
     */
    void setTurn(char symbol);

    /**
     * Clear the screen for a new game.
     */
    virtual void clear(void);

    /**
     * Display the game board on the screen.
     * @param mtx game board with symbols
     */
    virtual void showBoard(const boardMtx__t& mtx);

    /**
     * Display scores on the screen.
     * @param name1 name of the player 1
     * @param score1 score of the player 1
     * @param draws number of draws 
     * @param name1 name of the player 2
     * @param score1 score of the player 2
     */
    virtual void showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2);

    /**
     * Get cell selection on the game board done by the user with mouse.
     * @return cell number [0,8] on the game board selected by user
     *         or 'Q' or 'q' from keyboard to quit
     */
    int getMove(void);
    
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

    Curse(void)  { initCurse(); }
    ~Curse(void) { endCurse(); }
    
private:  
    
    struct subWin_t {
        int starty, startx;
        int leny, lenx;
        WINDOW *win;
    };
    
    struct gridWin_t {
        subWin_t subWin;
    } gridWin;

    struct userWin_t {
        subWin_t subWin;
        std::string playerName;
        bool isMachine;
        size_t score;
        char symbol; // Playing symbol X or O
    } userWin[NUM_PLAYERS];

    struct drawWin_t {
        subWin_t subWin;
        std::string headerText;
        size_t score;
    } drawWin;

    boardMtx__t savedBoard;
    bool gridVisible;
    bool mouseIsOn;
    int turn;


    void initCurse(void);
    void endCurse();
    void showGrid(void);
    void createWindow(subWin_t& win, int starty, int startx, int leny, int lenx);
    void createSubWindows(void);
    int  getCellNumber(int y, int x);
    void getGridCoords(int cell, int& gridy, int& gridx);
    void updateBoard(const boardMtx__t& board);
    void setCellsColor(std::vector<int>& cells, int colorPair);
    void showWinningLine(winLine__t& wl);
    void showUserWindow(userWin_t&, const char*);
    void showDrawWindow(const char*);
    int  playerNumberBySymbol(char symbol);

    
};
    
#endif