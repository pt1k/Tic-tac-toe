/**
 * @file    engine.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The game engine module.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "ttt.h"
#include "engine.h"

/**
 * Create objects for the players
 */
void Engine::createPlayers(void)
{
    for(size_t i = 0; i < players.size(); i++) {
        std::string playerName = ui->askPlayerName(i + 1);
        bool machine = ui->askIfMachine(i + 1);
        players[i] = new Player(playerName, i==0 ? X__C : O__C, machine);
    }
}

/**
 * Delete the players at the end
 */
void Engine::deletePlayers(void)
{
    for(size_t i = 0; i < players.size(); i++) {
        delete players[i];
        players[i] = NULL;
    }
}

/**
 * Get index of the player whose turn is next
 * @param lastTurn index of the player whose turn just gone
 * @return index of the player whose turn is next
 */
int Engine::nextTurn(int lastTurn)
{
    return (lastTurn + 1) % players.size();
}

/**
 * Play one board, i.e  lot or a round
 * @param starter index of the player who makes the first move of the game
 * @return: true if want to play a new board
 */
bool Engine::playOneBoard(int starter)
{
    game->initBoard();
    game->update(players);
    int turn = starter;
    do {
        if (!game->makeMove(players[turn]))
            return false;
        game->update(players);
        turn = nextTurn(turn);
        
    } while (game->getGameState() == IN_PROGRESS__C);

    return ui->askReadyForNewGame();
}

/**
 * Play games over and over again until a player terminates his tournament.
 * @return true: some other players want to play.
 *         false: they're all gonna quit playing :( 
 */
bool Engine::start(void)
{
    //printf("Engine::start..\n");
    
    createPlayers();
    game->clearDrawnMatches();
    srand (time(NULL));
    
    int starter = 0;
    while (playOneBoard(starter)) {
        starter = nextTurn(starter);
    }

    deletePlayers();
    ui->clear();
            
    return ui->askToPlayAgain();
}
