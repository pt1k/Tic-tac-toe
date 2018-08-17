/**
 * @file    ttt.h
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.2
 * @brief   This header file contains general definitions of the program.
 */

#ifndef TTT_H
#define TTT_H

#include <array>
//#include <vector>

#define NUM_PLAYERS 2                               ///< The game needs exactly two players

#define MTX_SIZE 9                                  ///< Size (3x3) of the game board matrix
#define X__C 'X'                                    ///< Board symbol 'X'
#define O__C 'O'                                    ///< Board symbol 'O'
#define n__C ' '                                    ///< Denotes a free cell on the board
#define TERMINATE__C 0                              ///< Quit the game by entering 0

//using board_mtx__t = char [MTX_SIZE];
using boardMtx__t = std::array<char, MTX_SIZE>;     ///< datatype for the game matrix
using winLine__t  = std::array<int, 3>;             ///< datatype for the winning line in game board

/** 
 * States of the game
 */
enum gameState__t {
    STARTING__C,
    IN_PROGRESS__C,
    DRAWN_MATCH__C,
    GOT_WINNER__C
};

class Player;
/** 
 * Array of player classes
 */
using players__t = std::array<Player *, NUM_PLAYERS>;

#endif
