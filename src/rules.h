/**
 * @file    rules.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The game rule utilities.
 */

#ifndef RULES_H
#define RULES_H

/**
 * Validate if the given move is legal.
 * @param mtx the game board
 * @param position the cell number of the move to validate
 * @return true: the move is legal.
 *         false: the move is not legal
 */
bool isLegalMove(const boardMtx__t& mtx, int position);

/**
 * Calculate the currect state of the game.
 * @param mtx the game board
 * @param winLine the winning line is returned here if a winner exists
 * @return the state of the game
 */
gameState__t calculateGameState(const boardMtx__t& mtx, winLine__t& winLine);


#endif
