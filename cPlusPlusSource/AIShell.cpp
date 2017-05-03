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
    time_t start;
    time(&start);
    int depth = 0;
    std::pair<Move, int> result;
    //auto gt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second > right.second; }
    auto lt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second < right.second; };

    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> PQ(lt_score);
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> m(lt_score);
    empty = true;
    std::vector<Move> moves = generateMoves(gameState);

    if (empty) {
        return std::pair<Move, int>(Move(numCols / 2, numRows - 1), 0);
    }
    current = difftime(time(NULL), start) * 1000;

    while (current < deadline - 1000) {
        int alpha, beta;
        alpha = std::numeric_limits<int>::min();
        beta = std::numeric_limits<int>::max();
        int** keycheck = clone(gameState);
        keycheck[moves[0].col][moves[0].row] = AI_PIECE;
        if (nodes.find(keycheck) == nodes.end()) {
            for (Move move : moves) {
                currentDepth = 0;
                PQ.push(std::pair<Move, int>(move, MinMove(depth, start, keycheck, alpha, beta)));
            }
        }
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
        delete[] keycheck;
        currentDepth++;
        current = difftime(time(NULL), start) * 1000;
    }
    std::cout << PQ.top().second << std::endl;
    return PQ.top();
}

int AIShell::MaxMove(int depth, time_t start, int** board, int& alpha, int& beta) {
    current = difftime(time(NULL), start) * 1000;
    currentDepth += 1;
    if ((current >= deadline - 1000) || (currentDepth >= depth)){
        int eval = EvalState(board, AI_PIECE);
        nodes.insert({ board, eval });
        return eval;
    }
    std::vector<Move> moves = generateMoves(board);
    int eval = std::numeric_limits<int>::min();
    //auto gt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second > right.second; };
    //std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(gt_score)> PQ(gt_score);
    auto lt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second < right.second; };
    std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> PQ(lt_score);
    int** key = clone(board);
    int local = currentDepth;

    key[moves[0].col][moves[0].row] = AI_PIECE;
    bool explored = (nodes.find(key) != nodes.end()) ? true : false;
    if (explored) {
        for (Move move : moves) {
            int** b = clone(board);
            b[move.col][move.row] = AI_PIECE;
            PQ.push(std::pair<Move, int>(move, nodes.find(b)->second));
            delete[] b;
        }

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
    }
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
    //auto lt_score = [](std::pair<Move, int> left, std::pair<Move, int> right) {return left.second < right.second; };
    //std::priority_queue < std::pair<Move, int>, std::vector<std::pair<Move, int>>, decltype(lt_score)> PQ(lt_score);
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
    }
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
