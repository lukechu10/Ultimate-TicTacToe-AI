#pragma once
#include "headers.h"

#include "GameBoard.h"
#include "Move.h"

class UltimateTicTacToe {
	GameBoard data; // Representation of gameboard

	enum Turn : bool {
		Player1 = true,
		Payer2
	};
public:
	// Creates a blank game board
	UltimateTicTacToe();
	UltimateTicTacToe& applyMove(Move m);
	std::vector<Move> availibleMoves(Square who);

	// sub game board wins
	SubGameBoard<Square> subWins;

	// Get move from user input
	Move getMoveFromInput(Square who);

	// Check for win is sub game board and update
	void checkSubWin(unsigned row, unsigned col);

	void checkForFull(unsigned row, unsigned col);

	// Check for global win and returns winner
	Square checkForWinGlobal();

	// print gameboard
	friend std::ostream& operator<< (std::ostream& os, const UltimateTicTacToe& b);

	// return array representation
	SubGameBoard<SubGameBoard<Square>> toArray();
};