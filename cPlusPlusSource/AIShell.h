#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include "Move.h"
#include <vector>
#include <time.h>
#include <queue>
#include <limits>
#include <random>
#include <functional>
#include <unordered_map>

// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;
    double current;

private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.
     Move bestMove;
     std::unordered_map<int**, int> nodes;
    bool empty;
    int currentDepth;


public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
	int h(Move m, int** board);
    std::pair<Move, int> minMax(int depth, int** board, int player, time_t start);
    std::vector<Move> generateMoves(int** board);
    std::pair<Move, int> IDS();
    int winner(int** board);
    int MaxMove(int depth, time_t start, int** board, int& alpha, int& beta);
    int MinMove(int depth, time_t start, int** board, int& alpha, int& beta);
    int EvalState(int** board, int player);
    int** clone(int** board);
};

#endif //AISHELL_H
