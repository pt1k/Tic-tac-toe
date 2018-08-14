/**
 * @file    game.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The game module.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <unistd.h>           

#include "ttt.h"
#include "game.h"
#include "rules.h"
#include "computermove.h"

/**
 * Clear the counter of drawn matches
 */
void Game::clearDrawnMatches(void)
{
    drawnMatches = 0;
}

/**
 * Mark all cells free and set the game state to 'starting'.
 */
void Game::initBoard(void)
{
    for (size_t i = 0; i < mtx.size(); i++)
        mtx[i] = n__C;

    gameState = STARTING__C;
    std::fill(winLine.begin(), winLine.end(), -1);
}

/**
 * Get a move from the player
 */
bool Game::makeMove(Player *player)
{
    int move;
    auto symbol = player->getSymbol();

    ui->setTurn(symbol);

    do {
        int preferred = compMove(mtx, symbol);
        if (player->isMachine()) 
            move = preferred;
        else 
            move = ui->askMove(mtx, symbol, player->getName(), 0 /*preferred*/);
        if (move == TERMINATE__C)
            return false;
        
    } while (!setMove(player, move));
    
    return true;
}

/**
 * Get the state of the game.
 */
gameState__t Game::getGameState(void) const
{
    return gameState;
}

/**
 * Update the game items (board, scores) on the screen.
 */
void Game::update(players__t& players)
{
    if (gameState == STARTING__C) {
        ui->clear();
    }
        
    ui->showScores(players[0]->getName(), players[0]->getScore(),
                   drawnMatches,
                   players[1]->getName(), players[1]->getScore());
    ui->showBoard(mtx, winLine);
}

/**
 * Handle the move the player just entered.
 * Check the move validity, update game state and statistics.
 * @param player the player who made this move
 * @param move to which cell the player dropped his/her symbol
 * Return: true: the move is legal
 *         false: player terminates his tournament or gave an illegal move
 */
bool Game::setMove(Player *player, int move)
{
    if (!isLegalMove(mtx, move))
        return false;
    
    mtx[move-1] = player->getSymbol();
    gameState = calculateGameState(mtx, winLine);
    switch (gameState) {
        case DRAWN_MATCH__C:
            drawnMatches++;
            break;
        case GOT_WINNER__C:
            player->raiseScore();
            break;
        default:
            break;
    }
    
    return true;
}    


