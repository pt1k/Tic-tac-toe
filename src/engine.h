/**
 * @file    engine.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The game engine definitions.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "game.h"
#include "player.h"
#include "userif.h"

/**
 * The game engine class.
 */
class Engine : private Game
{
  private:
    Game *game;
    UserIf *ui;
    players__t players;

    void createPlayers(void);
    void deletePlayers(void);
    bool playOneBoard(int starter);
    int nextTurn(int lastTurn);

public:
    /**
     * Constructor of the engine class
     */
    Engine() { /*printf("Engine ..\n");*/  };

    /**
     * Constructor of the engine class
     */
    Engine(Game *pGame, UserIf *pUi) : game(pGame), ui(pUi) { /*printf("Engine(game, ui) ..\n");*/ };

    /**
     * Method to start the game engine.
     * @return returns a bool if they wanted to play again (with other players).
     */
    bool start(void);
};

#endif
