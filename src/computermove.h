/**
 * @file    computermove.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   Computer move definitions.
 */

#ifndef COMPUTERMOVE_H
#define COMPUTERMOVE_H

/**
 * Calculate best move for the player who is in-turn.
 * @param boardMtx game board with symbols
 * @param pTurn symbol of the player who is making the move now
 * @return cell number (1-9) which produces an optimal move
 */
int compMove(const boardMtx__t& boardMtx, char pTurn);

#endif