/**
 * @file    player.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The player class definition.
 */

#ifndef PLAYER_H
#define PLAYER_H

/*
 * The player class.
 */
class Player 
{
    std::string name;
    char symbol;
    int score;
    bool machine;
    
  public:
    /**
     * Constructor of the player.
     */
    Player() {};

    /**
     * Constructor of the player.
     * @param pName name of the player
     * @param pSym symbol of the player 'X' or 'O'
     * @param pMachine is the player machine/computer
     */
    Player(std::string pName, char pSym, bool pMachine) 
           : name(pName), symbol(pSym), machine(pMachine) { score = 0; }

    /**
     * player destructor.
     */
    ~Player() { /* printf("Destroying player '%s'.\n", name.data()); */ };

    /**
     * Get the name of the player.
     * @return player's name 
     */
    std::string& getName()     { return name; }

    /**
     * Get the symbol 'X' or 'O' of the player.
     * @return player's symbol
     */
    char   getSymbol()  const { return symbol; }

    /**
     * Get the score of the player.
     * @return How many wins the player has
     */
    int    getScore()   const { return score; }

    /**
     * Increment the player's score by one.
     */
    void   raiseScore() { score++; }

    /**
     * Check whether the player is machine/computer.
     * @return true: the player is machine/computer
     *         false: the player is human
     */
    bool   isMachine() const { return machine; }
};

#endif
