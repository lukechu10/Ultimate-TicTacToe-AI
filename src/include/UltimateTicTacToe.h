#pragma once
#include "headers.h"

#include "GameBoard.h"
#include "Move.h"

class UltimateTicTacToe {
    GameBoard data; // Representation of gameboard
public:
    // Creates a blank game board
    UltimateTicTacToe();

    inline UltimateTicTacToe &applyMove(Move m) {
        data.setValue(m.row, m.col, m.subRow, m.subCol, m.who);
        checkSubWin(m.row, m.col);
        return *this;
    }

    std::vector<Move> availibleMoves(Square who);

    // sub game board wins
    SubGameBoard<Square> subWins;

    // Get move from user input
    Move getMoveFromInput(Square who);

    // Check for win is sub game board and update
    inline void checkSubWin(unsigned row, unsigned col) {
        // check if sub game board is full

#define subBoard data.getSubGameBoard(row, col)
        // Checking for Rows for X or O victory.
        for (int subRow = 0; subRow < 3; subRow++) {
            if (subBoard[subRow][0] == subBoard[subRow][1] &&
                subBoard[subRow][1] == subBoard[subRow][2] &&
                subBoard[subRow][0] != Square::Blank) {
                subWins[row][col] = subBoard[subRow][0];
                return;
            }
        }

        // Checking for Columns for X or O victory.
        for (int subCol = 0; subCol < 3; subCol++) {
            if (subBoard[0][subCol] == subBoard[1][subCol] &&
                subBoard[1][subCol] == subBoard[2][subCol] &&
                subBoard[0][subCol] != Square::Blank) {
                subWins[row][col] = subBoard[0][subCol];
                return;
            }
        }

        // Checking for Diagonals for X or O victory.
        if (subBoard[0][0] == subBoard[1][1] && subBoard[1][1] == subBoard[2][2] &&
            subBoard[0][0] != Square::Blank) {
            subWins[row][col] = subBoard[0][0];
            return;
        }

        if (subBoard[0][2] == subBoard[1][1] && subBoard[1][1] == subBoard[2][0] &&
            subBoard[0][2] != Square::Blank) {
            subWins[row][col] = subBoard[0][2];
            return;
        }
        // no win detected
#undef subBoard
    }

    inline void checkForFull(unsigned row, unsigned col) {
        for (auto &boardRow : data.getSubGameBoard(row, col)) {
            for (auto &col : boardRow) {
                if (col == Square::Blank)
                    return; // exit function
            }
        }
        // no more availible moves
        // set subWins
        subWins[row][col] = Square::Full;
    }

    // Check for global win and returns winner
    Square checkForWinGlobal();

    // print gameboard
    friend std::ostream &operator<<(std::ostream &os, const UltimateTicTacToe &b);

    // return array representation
    SubGameBoard<SubGameBoard<Square>> toArray();

    int evaluateBasicBoard(SubGameBoard<Square>);

    SubGameBoard<int> generateCoefs();

    // minimax evaluation funtion
    int evaluate();

    int minimax(bool isMax, int depth, int alpha, int beta);

    // minimax ai
    Move bestMove(Square who);
};