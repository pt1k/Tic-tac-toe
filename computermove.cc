/**
 * @file    computermove.cc
 * @author  Pekka Koivuniemi
 * @date    6 April 2018
 * @version 0.1
 * @brief   Calculating the best suitable move.
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>

#include "ttt.h"
#include "computermove.h"


using valueMtx__t = std::array<int, MTX_SIZE>;  ///< game board structure with values -1, 0 and 1

struct scores__t {                              
    int score;
    int move;
};                                              ///< Datatype holding the score value of a move

/**
 * Indices of winning line indices in the 3x3 game board
 * Usage:
 * for (size_t i = 0; i < numWinLines; i++) {
 *     if (abs(mtx[winLine[i][0]] + mtx[winLine[i][1]] + mtx[winLine[i][2]]) == 3) {
 *       // we have a winning line 
 *     }
 * }
 * // winning line does not exist
 * 
 */
static int winLine[][3] = { { 0, 1, 2 },
                     { 3, 4, 5 },
                     { 6, 7, 8 },
                     { 0, 3, 6 },
                     { 1, 4, 7 },
                     { 2, 5, 8 },
                     { 0, 4, 8 },
                     { 2, 4, 6 }
                   };
static const int numWinLines = (sizeof(winLine) / sizeof(winLine[0])); ///< Number of possible winning lines in a game board

/**
 * Fill up matrix where in-turn player's cells are 1, opponent's cells are -1 and unused cells are 0.
 * @param boardMtx game board with symbols
 * @param valueMtx returned game board with values
 * @param pTurn symbol of the player who is making the move now
 */
static void initValueMtx(const boardMtx__t& boardMtx, valueMtx__t& valueMtx, char pTurn)
{
    for (size_t i = 0; i < boardMtx.size(); i++)
        valueMtx[i] = (boardMtx[i] == pTurn) ? 1 : (boardMtx[i] == n__C) ?  0 : -1;
}

/**
 * Check if game is over and provide game result.
 * @param valueMtx game board with values
 * @param result return game result when game is over: 
 *        1: player with  1's won, 0: draw, -1: player with -1's won
 * @return true: game is over, and then the result as side effect returned. 
 *         false: game is ongoing
 */
static bool isGameOver(const valueMtx__t mtx, int& result)
{
    for (size_t i = 0; i < numWinLines; i++) {
        int sum = mtx[winLine[i][0]] + mtx[winLine[i][1]] + mtx[winLine[i][2]];
        if (abs(sum) == 3) {
            result = mtx[winLine[i][0]];
            return true;
        }
    }
        
    for (size_t i = 0; i < mtx.size(); i++) {
        if (mtx[i] == 0)
            return false;
    }

    result = 0;
    return true;
}

/**
 * Get max score value of one players turn
 * @param valueMtx game board with values
 * @param turn board value (1 or -1) of the player who is making the move now
 * @return maximum score value after trying each free cell play
 */
static int minMax(valueMtx__t& valueMtx, int turn)
{
    int result, bestScore = -2;
    if (isGameOver(valueMtx, result))
        return result * turn;

    for (int move = 0; move < (int)valueMtx.size(); move++) {
        
        if (valueMtx[move] != 0)
            continue;
        
        valueMtx[move] = turn;
        int tmpScore = -minMax(valueMtx, -turn);
        bestScore = max(tmpScore, bestScore);
        valueMtx[move] = 0;
    }
    return bestScore;
}

/**
 * Compare two scores__t elements by their score values.
 * @param sc1 first score element to compare
 * @param sc2 second score element to compare
 * @return true:  sc1 > sc2. 
 *         false: sc1 <= sc2
 * Used by std::sort.
 */
static bool compareScores (scores__t sc1, scores__t sc2) { return (sc1.score > sc2.score); }

/**
 * Choose one of the moves which has the largest score.
 * @param scoreVec vector of score-move pairs
 * @return the move (board index 0-8) which has the largest score
 */
static int chooseBestMove(std::vector<scores__t>& scoreVec)
{
    // Rearrange moves in some random order to get variation between the games
    std::random_shuffle(scoreVec.begin(), scoreVec.end());
    
    // Sort them by scores in descending order (highest score first).
    std::sort(scoreVec.begin(), scoreVec.end(), compareScores);

    // for (size_t i = 0; i < scoreVec.size(); i++) 
    //    printf("move:%d score:%d\n", scoreVec[i].move + 1, scoreVec[i].score);
    
    return scoreVec[0].move;
}
    
/**
 * Calculate best move for the player who is in-turn.
 * @return cell number (1-9) which produces an optimal move
 */
int compMove(const boardMtx__t& boardMtx, const char pTurn)
{
    // Game array with values instead of symbols
    valueMtx__t valueMtx;
    initValueMtx(boardMtx, valueMtx, pTurn);
    
    scores__t result;
    std::vector<scores__t> scoreVec {};

    // 'Play' all available cells and save their scores
    for (int move = 0; move < (int)valueMtx.size(); move++) {

        if (valueMtx[move] != 0)
            continue;

        valueMtx[move] = 1;
        result.score = -minMax(valueMtx, -1);
        result.move  = move;
        valueMtx[move] = 0;
        scoreVec.push_back(result);
    }
    // Return the best move whatever recorded
    return chooseBestMove(scoreVec) + 1;
}
