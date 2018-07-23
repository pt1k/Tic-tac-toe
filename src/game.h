/**
 * @file    game.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The definitions of the game class.
 */

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "userif.h"

/**
 * The game class.
 */

class Game : public Player
{
  private:
    UserIf *ui;
    boardMtx__t mtx;
    winLine__t  winLine;
    int drawnMatches;
    gameState__t gameState;
    
    bool setMove(Player *player, int move);
    
  public:
    /** 
     * Constructor 
     */
    Game() { /*printf("Game ..\n"); */ };

    /** 
     * Constructor 
     */
    Game(UserIf *p_ui) : ui(p_ui) { /*printf("Game(ui) ..\n"); */ drawnMatches = 0; gameState = STARTING__C; };

    /**
     * Initialize the game board, needed at the beginning of the game.
     */
    void initBoard(void);

    /**
     * Get a move from the player.
     * @param player the player whose turn is now 
     * @return true: legal move received.
     *         false: player terminates his tournament
     */
    bool makeMove(Player *player);
    
    /**
     * Get the state of the game.
     * @return state of the game 
     */
    gameState__t getGameState() const;

    /**
     * Update the game items (board, scores) on the screen.
     * @param players array of the players
     */
    void update(players__t& players);
};

#endif
