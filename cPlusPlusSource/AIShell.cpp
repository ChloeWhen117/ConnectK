#include "AIShell.h"
#include <iostream>



 

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

int** AIShell::clone(int** board) {
    int** result = new int*[numCols];
    for (int i = 0; i < numCols; i++) {
        result[i] = new int[numRows];
    }
    for (int i = 0; i < numCols; i++){
        for (int j = 0; j < numRows; j++){
            result[i][j] = gameState[i][j];
        }
    }
    return result;
};


int AIShell::EvalState(int** board, int player) {
	//heuristic function
    int count_enemy, count_AI;
    count_enemy = count_AI = 0;
    if (winner(board) == -1) {
        return -1000;
    }
    else if (winner(board) == 1) {
        return 1000;
    }
    int eval = 0;
    int connected = k - 1;
	// search for possible lines
    //vertical progress
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            if (board[i][j] == HUMAN_PIECE) {
                count_enemy++;
                count_AI = 0;
            }
            else if (board[i][j] == AI_PIECE) {
                count_enemy = 0;
                count_AI++;
            }
            else {
                if (count_enemy == connected) {
                    eval -= 100;
                }
                else if (count_AI == connected) {
                    eval += 100;
                } else if (count_enemy == connected - 1) {
                    eval -= 25;
                }
                else if (count_AI == connected - 1) {
                    eval += 25;
                }
                eval -= count_enemy*10;
                eval += count_AI*10;
                count_enemy = 0;
                count_AI = 0;
            }
        }
        count_enemy = 0;
        count_AI = 0;
    }

    //horizontal progress
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++) {
            if (board[i][j] == HUMAN_PIECE) {
                count_enemy++;
                count_AI = 0;
            }
            else if (board[i][j] == AI_PIECE) {
                count_enemy = 0;
                count_AI++;
            }
            else {
                if (count_enemy == connected) {
                    eval -= 100;
                }
                else if (count_AI == connected) {
                    eval += 100;
                }
                else if (count_enemy == connected - 1) {
                    eval -= 25;
                }
                else if (count_AI == connected - 1) {
                    eval += 25;
                }
                eval -= count_enemy*10;
                eval += count_AI*10;
                count_enemy = 0;
                count_AI = 0;
            }
        }
        count_enemy = 0;
        count_AI = 0;
    }
    //diagonal eval
    for (int i = 0; i < numCols - connected + 1; i++) {
        for (int j = 0; j < numRows - connected + 1; j++) {
            bool enemyWins, aiWins;
            enemyWins = aiWins = true;
            for (int m = 0; m < connected; m++) {
                if (board[i + m][j + m] != HUMAN_PIECE) {
                    enemyWins = false;
                    break;
                }
            }
            if (enemyWins) {
                eval -= 100;
            }
            else {
                enemyWins = true;
            }
            for (int m = 0; m < connected; m++) {
                if (board[i + (connected - 1 - m)][j + m] != HUMAN_PIECE) {
                    enemyWins = false;
                    break;
                }
            }
            if (enemyWins) {
                eval -= 100;
            }

            for (int m = 0; m < connected; m++) {
                if (board[i + m][j + m] != AI_PIECE) {
                    aiWins = false;
                    break;
                }
            }
            if (aiWins) {
                eval += 100;
            }
            else {
                aiWins = true;
            }
            for (int m = 0; m < connected; m++) {
                if (board[i + connected -1 - m][j + m] != AI_PIECE) {
                    aiWins = false;
                    break;
                }
            }
            if (aiWins) {
                eval += 100;
            }
        }
    }
    return eval;
}

int AIShell::winner(int** board){
	//returns winning states
	int connected = k;
	int count_enemy, count_AI;
	count_enemy = count_AI = 0;
	//vertical victory
	for (int i = 0; i < numCols; i++) {
		for (int j = 0; j < numRows; j++) {
			if (board[i][j] == HUMAN_PIECE) {
				count_enemy++;
				count_AI = 0;
				if (count_enemy == connected) {
					return -1;
				}
			} else if (board[i][j] == AI_PIECE) {
				count_enemy = 0;
				count_AI++;
				if (count_AI == connected) {
					return 1;
				}
			} else {
				count_enemy = 0;
				count_AI = 0;
			}
		}
		count_enemy = 0;
		count_AI = 0;
	}

	//horizontal victory
	for (int j = 0; j < numRows; j++) {
		for (int i = 0; i < numCols; i++) {
			if (board[i][j] == HUMAN_PIECE) {
				count_enemy++;
				count_AI = 0;
				if (count_enemy == connected) {
					return -1;
				}
			} else if (board[i][j] == AI_PIECE) {
				count_enemy = 0;
				count_AI++;
				if (count_AI == connected) {
					return 1;
				}
			} else {
				count_enemy = 0;
				count_AI = 0;
			}
		}
		count_enemy = 0;
		count_AI = 0;
	}

	//diagonal victory
	for (int i = 0; i < numCols - connected + 1; i++) {
		for (int j = 0; j < numRows - connected + 1; j++) {
			bool enemyWins, aiWins;
            enemyWins = aiWins = true;
			for (int m = 0; m < connected; m++) {
				if (board[i + m][j + m] != HUMAN_PIECE) {
					enemyWins = false;
					break;
				}
			}
			if (enemyWins){
                return -1;
            } else{
                enemyWins = true;
            }
			for (int m = 0; m < connected; m++) {
				if (board[i + (connected -1 - m)][j + m] != HUMAN_PIECE) {
					enemyWins = false;
					break;
				}
			}
			if (enemyWins) {
				return -1;
			}

			for (int m = 0; m < connected; m++) {
				if (board[i + m][j + m] != AI_PIECE) {
					aiWins = false;
					break;
				}
			}
			if (aiWins) {
				return 1;
			} else{
                aiWins = true;
            }
			for (int k = 0; k < connected; k++) {
				if (board[i + connected -1 - k][j + k] != AI_PIECE) {
					aiWins = false;
					break;
				}
			}
			if (aiWins) {
				return 1;
			}
		}
	}
    return 0;
}

std::vector<Move> AIShell::generateMoves(int **board) {
	//Input: Board state
	//Output: a vector of available Moves for every empty space on the board state.
	std::vector<Move> moves;
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            if(board[i][j] == NO_PIECE){
                moves.push_back(Move(i,j));
                if (gravityOn)
                    break;
            } else{
                empty = false;
            }
        }
    }
    return moves;
}

std::pair<Move, int> AIShell::IDS() {
	//Iterative Depthening Search
    time_t start;
    time(&start);
    int depth = 0;
    std::pair<Move, int> result;
    auto lt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second < right.second; };
	
	// PQ keep track of the moves returned so far
	// generate list of moves, m, in random order for first time
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> PQ(lt_score);
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> m(lt_score);
    empty = true;
    std::vector<Move> moves = generateMoves(gameState);

    if (empty) {
        return std::pair<Move, int>(Move(numCols / 2, numRows - 1), 0);
    }
    current = difftime(time(NULL), start) * 1000;
	// start IDS search with a series of Depth Limited Searches

    while (current < deadline - 1000) {
		// update alpha beta
        int alpha, beta;
        alpha = std::numeric_limits<int>::min();
        beta = std::numeric_limits<int>::max();
        int** keycheck = clone(gameState);
        keycheck[moves[0].col][moves[0].row] = AI_PIECE;
		// if no tree has been made yet (if hashMap doesn't have a record of child at all)... 
		// do a blind search
        if (nodes.find(keycheck) == nodes.end()) {
			// for each move, place the piece on a copy of the board, then send that new board to MinMove
			// this will cause a DFS to happen and return the lowest value given by making this move
			// then we add all the moves with their corresponding scores to a priority queue that is max first
            for (Move move : moves) {
                currentDepth = 0;
                PQ.push(std::pair<Move, int>(move, MinMove(depth, start, keycheck, alpha, beta)));
            }
        } // if tree HAS been made, then just check the tree to see which one to start with, then do the same process as the blind search
        else {
            for (Move move : moves) {
                int** b = clone(gameState);
                b[move.col][move.row] = AI_PIECE;
                std::cout << nodes[b] << std::endl;
                m.push(std::pair<Move, int>(move, nodes[b]));
                delete[] b;
            }
            for (; !m.empty(); ) {
                Move curr = (m.top()).first;
                m.pop();
                int** b = clone(gameState);
                b[curr.col][curr.row] = AI_PIECE;
                PQ.push(std::pair<Move, int>(curr, MinMove(depth, start, b, alpha, beta)));
                delete b;
            }
        }
		// clean up
        delete[] keycheck;
        currentDepth++;
        current = difftime(time(NULL), start) * 1000;
    }
	// to get the move that results in the state with the highest score, just pop off the first item.
    std::cout << PQ.top().second << std::endl;
    return PQ.top();
}

int AIShell::MaxMove(int depth, time_t start, int** board, int& alpha, int& beta) {
    current = difftime(time(NULL), start) * 1000;
    currentDepth += 1;
	// check if depth limit reached. If so, record to hash table "nodes" and send back eval of state
    if ((current >= deadline - 1000) || (currentDepth >= depth)){
        int eval = EvalState(board, AI_PIECE);
        nodes.insert({ board, eval });
        return eval;
    }
	// else, try every possible move, until depth limit is up
	// and save the score for every move
	// then return largest score
    std::vector<Move> moves = generateMoves(board);
    int eval = std::numeric_limits<int>::min();
	// initialize priority queue. this queue will keep track of the
	// moves, and have them sorted with best move first;

	// passes in ReversePriority PQ to tell PQ how to operate:
	// by reversing the order of natural ordering
    auto lt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second < right.second; };
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> PQ(lt_score);
    int** key = clone(board);
    int local = currentDepth;

	// IDEA:
	// get a sorted list of children nodes if possible, then expanding them
	//
	// METHOD:
	// just apply each move to the passed-in board state, then get the values for each state.
	// then start with the move that leads to the state with the largest value

	// Getting a sorted list of children nodes:
	//	- check if children have been explored
	//	- if the resulting state is in the hashMap, nodes, stick the value onto the move that
	//    would get to the resulting state, and put into PQ 
	//	- then do DFS using PQ as the source of moves to apply
	//	- if NOT in hashMap, nodes, then just continue with the depth first search by using
	//	- the array of moves that has no particular order

	// check if children are explored
    key[moves[0].col][moves[0].row] = AI_PIECE;
    bool explored = (nodes.find(key) != nodes.end()) ? true : false;
	
	// if state is in the hashMap, nodes, (i.e. this part of game tree is already explored)
	// make sorted list of moves that would get to each state, according to the states'
	// values. These values would go into the "move" that gets to the state
    if (explored) {
        for (Move move : moves) {
            int** b = clone(board);
            b[move.col][move.row] = AI_PIECE;
            PQ.push(std::pair<Move, int>(move, nodes.find(b)->second));
            delete[] b;
        }
			// go through the priority list and DFS each node
			// DFS:
			// 1. make sure global depth field is reset to current depth
			// 2. make a move on a copy of the state
			// 3. send state through MinMove function
			// 4. get returned value and associate it with the move
			// 5. put PointWithScore into PQ so that highest value comes out first
        for (; !PQ.empty();) {
            currentDepth = local;
            int** b = clone(board);
            Move move = PQ.top().first;
            PQ.pop();
            b[move.col][move.row] = AI_PIECE;
            int minMove = MinMove(depth, start, b, alpha, beta);
            delete[] b;
            if (minMove > eval) {
                eval = minMove;
                alpha = eval;
                if (alpha >= beta)
                    break;
            }
            
        }
    } // if not in hashMap then just do DFS with no ordering
    else {
        for (Move move : moves) {
            currentDepth = local;
            int** b = clone(board);
            Move m = PQ.top().first;
            PQ.pop();
            b[m.col][m.row] = AI_PIECE;
            int minMove = MinMove(depth, start, b, alpha, beta);
            delete[] b;

            if (minMove > eval) {
                eval = minMove;
                alpha = eval;
                if (alpha >= beta)
                    break;
            }
        }
    }
	// record this state with the best value found
    delete[] key;
    nodes.insert({ board, eval });

    return eval;
}

int AIShell::MinMove(int depth, time_t start, int** board, int& alpha, int& beta){
    currentDepth += 1;
    current = difftime(time(NULL), start) * 1000;
    if ((current >= deadline - 1000) || (currentDepth >= depth)) {
        int eval = EvalState(board, HUMAN_PIECE);
        nodes.insert({ board, eval });
        return eval;
    }
    std::vector<Move> moves = generateMoves(board);
    int eval = std::numeric_limits<int>::max();
    auto gt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second > right.second; };
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(gt_score)> PQ(gt_score);
    int** key = clone(board);
    int local = currentDepth;
    key[moves[0].col][moves[0].row] = HUMAN_PIECE;
    bool explored = (nodes.find(key) != nodes.end()) ? true : false;
    if (explored) {
        for (Move move : moves) {
            int** b = clone(board);
            b[move.col][move.row] = HUMAN_PIECE;
            PQ.push(std::pair<Move, int>(move, nodes.find(b)->second));
            delete[] b;
        }
		// go through the priority list and DFS each node
        for (; !PQ.empty();) {
            currentDepth = local;
            int** b = clone(board);
            Move move = PQ.top().first;
            PQ.pop();
            b[move.col][move.row] = HUMAN_PIECE;
            int maxMove = MaxMove(depth, start, b, alpha, beta);
            delete[] b;

            if (maxMove < eval) {
                eval = maxMove;
                beta = eval;
                if (alpha >= beta)
                    break;
            }
        }
    } 	// if not in hashMap then just do DFS with no ordering
    else {
        for (Move move : moves) {
            currentDepth = local;
            int** b = clone(board);
            Move m = PQ.top().first;
            PQ.pop();
            b[m.col][m.row] = AI_PIECE;
            int maxMove = MinMove(depth, start, b, alpha, beta);
            delete[] b;

            if (maxMove < eval) {
                eval = maxMove;
                beta = eval;
                if (alpha >= beta)
                    break;
            }
        }
    }
    delete[] key;
    nodes.insert({ board, eval });

    return eval; 
}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
	deadline = 5000;
	srand(time(NULL));
	std::pair<Move, int> answer = IDS();
    //std::cout << "MOVE IS (" << answer.first.col << "," << answer.first.row << ")" << std::endl;
	return Move(answer.first.col, answer.first.row);
}
