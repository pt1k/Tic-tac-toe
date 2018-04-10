/**
 * @file    rules.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   The game rule utilities.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <assert.h>  

#include "ttt.h"
#include "rules.h"

/**
 * Check if the given line is winning line i.e. has all three symbols of a player.
 */
static bool isWinLine(const boardMtx__t& mtx, winLine__t& wl, int x1, int x2, int x3) 
{
    if (mtx[x1] != n__C &&
        mtx[x1] == mtx[x2] && 
        mtx[x1] == mtx[x3]) {
        wl[0] = x1; wl[1] = x2; wl[2] = x3;
        return true;
    }
    return false;
}

/**
 * Validate if the given move is legal.
 */
bool isLegalMove(const boardMtx__t& mtx, int position) {
    
    if (position < 1 || position > (int)mtx.size())
        return false;
    
    if ((mtx[position-1] != n__C))
        return false;
    
    return true;
}

/*
 * Calculate the currect state of the game.
 * Game is over when
 * - there is a winner who places three of the marks in a horizontal, vertical, or diagonal row; or
 * - the game board becomes full (without a winner)
 */
gameState__t calculateGameState(const boardMtx__t& mtx, winLine__t& wl) {
    
    // horizontal (---)
    for (size_t i = 0; i < mtx.size(); i += 3) {
        if (isWinLine(mtx, wl, i, i+1, i+2))
            return GOT_WINNER__C;
    }
    
    // vertical (|)
    for (size_t i = 0; i < 3; i++) {
        if (isWinLine(mtx, wl, i, i+3, i+6))
            return GOT_WINNER__C;
    }

    // diagonal up-left to down-right (\)
    if (isWinLine(mtx, wl, 0, 4, 8))
        return GOT_WINNER__C;

    // diagonal up-right to down-left (/)
    if (isWinLine(mtx, wl, 2, 4, 6))
        return GOT_WINNER__C;
    
    // no winner, check if the board is not filled up
    for (size_t i = 0; i < mtx.size(); i++) {
        if (mtx[i] == n__C)
            return IN_PROGRESS__C; // it's not over
    }
    
    // game over, no winner
    return DRAWN_MATCH__C;
}

/* 
 ************************************************
 *                                              * 
 *      Unit tests of the rules functions       *
 *                                              * 
 ************************************************
 */
void testRules(void)
{
#ifdef NDEBUG
    // no testing
    // printf("testRules: skipped.\n");
    return;
#else

    winLine__t wl;
    boardMtx__t m1 = { 
        X__C, X__C, O__C,
        O__C, O__C, X__C,
        X__C, O__C, n__C
    };
    assert(isLegalMove(m1, 1) == false);
    assert(isLegalMove(m1, 8) == false);
    assert(isLegalMove(m1, 9));
    assert(isLegalMove(m1, 10) == false);
    
    assert(calculateGameState(m1, wl) == IN_PROGRESS__C);
    
    // vertical
    boardMtx__t m2 = { 
        n__C, X__C, n__C,
        n__C, X__C, n__C,
        n__C, X__C, n__C
    };
    assert(isLegalMove(m2, 0) == false);
    assert(isLegalMove(m2, 1));
    assert(isLegalMove(m2, 2) == false);
    assert(calculateGameState(m2, wl) == GOT_WINNER__C);
    assert(wl[0]==1 && wl[1]==4 && wl[2]==7);
        
    // horizontal
    boardMtx__t m3 = { 
        n__C, X__C, n__C,
        n__C, X__C, n__C,
        O__C, O__C, O__C
    };
    assert(calculateGameState(m3, wl) == GOT_WINNER__C);
    assert(wl[0]==6 && wl[1]==7 && wl[2]==8);
    
    // diagonal \:
    boardMtx__t m4 = { 
        X__C, X__C, O__C,
        n__C, X__C, n__C,
        X__C, O__C, X__C
    };
    assert(calculateGameState(m4, wl) == GOT_WINNER__C);
    assert(wl[0]==0 && wl[1]==4 && wl[2]==8);
    
    // diagonal /
    boardMtx__t m5 = { 
        O__C, O__C, X__C,
        n__C, X__C, n__C,
        X__C, O__C, n__C
    };
    assert(calculateGameState(m5, wl) == GOT_WINNER__C);
    assert(wl[0]==2 && wl[1]==4 && wl[2]==6);
    
    // drawn
    boardMtx__t m6 = { 
        X__C, X__C, O__C,
        O__C, O__C, X__C,
        X__C, O__C, X__C
    };
    assert(calculateGameState(m6, wl) == DRAWN_MATCH__C);
        
    printf("testRules: passed.\n");

#endif
}
