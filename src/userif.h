/**
 * @file    userif.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   Definitions for user interface.
 */

#ifndef USERIF_H
#define USERIF_H

/**
 * User interface class.
 */
class UserIf 
{
    
  public:
    /**
     * Constructor.
     */
    UserIf() {};

    /**
     * Ask player's name from the user.
     * @param playerNumber the order number of the player
     * @return the name entered by the user
     */
    virtual std::string askPlayerName(int playerNumber) = 0;

    /** 
     * Ask from the user if the player is computer/machine or human.
     * @param playerNumber the order number of the player
     * @return true:  player is computer/machine. 
     *         false: player is human
     */
    virtual bool askIfMachine(int playerNumber) = 0;

    /**
     * Set next player's turn
     * It can be a human or machine.
     * @param symbol next player's playing symbol
     */
    virtual void setTurn(char symbol) = 0;
    
    /**
     * Ask next move from the player.
     * @param mtx game board with symbols
     * @param symbol player's game symbol
     * @param name player's name
     * @param preferred preferred move, just a hint to the user for best move
     * @return answer the user entered
     */
    virtual int askMove(const boardMtx__t& mtx, char symbol, std::string& name, int preferred) = 0;

    /** 
     * Ask from the user if they want to play again.
     * @return true: they want to play again. false: they want to quit playing
     */
    virtual bool askToPlayAgain(void) = 0;

    /**
     * Clear the screen for a new game.
     */
    virtual void clear(void) = 0;

    /**
     * Display the game board on the screen.
     * @param mtx game board with symbols
     */
    virtual void showBoard(const boardMtx__t& mtx) = 0;

    /**
     * Display scores on the screen.
     * @param name1 name of the player 1
     * @param score1 score of the player 1
     * @param draws number of draws 
     * @param name1 name of the player 2
     * @param score1 score of the player 2
     */
    virtual void showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2) = 0;

    /**
     * Display game result (winner or draw, winning line).
     * @param winLine winning line indices [0,8] on the game board
     */
    virtual void showGameResult(winLine__t& winLine) = 0;

    /**
     * Ask for an user interaction to start a new game.
     * @return true for a new game, false to quit
     */
    virtual bool askReadyForNewGame() = 0;

    /**
     * Destructor.
     */
    virtual ~UserIf(){};
    
};

#endif
