#pragma once

#include "headers.h"

// GameBoard for (non ultimate) tictactoe game
template<typename T>
using SubGameBoard = std::array<std::array<T, 3>, 3>;

enum class Square : unsigned char {
	Blank = 0,
	Player1 = 1,
	Player2 = 2,
	Full = 3 // only used for subWins, Full if there are no more availible spaces
};

inline std::ostream& operator<<(std::ostream& os, Square& sq) {
	switch (sq) {
	case Square::Blank:
		os << '-'; break;
	case Square::Player1:
		os << 'x'; break;
	case Square::Player2:
		os << 'o'; break;
	}
	return os;
}

class GameBoard {
	// Representation of GameBoard
	SubGameBoard<SubGameBoard<Square>> data;

	// Sub GameBoard for next move
	int subNextRow_ = -1, subNextCol_ = -1;
public:
	GameBoard(SubGameBoard<SubGameBoard<Square>> b) {
		data = b;
	}
	GameBoard() {
		// initialize data
		for (auto& row : data) {
			for (auto& col : row) {
				for (auto& subRow : col) {
					for (auto& subCol : subRow) {
						subCol = Square::Blank;
					}
				}
			}
		}
	};
	// Return sub GameBoard
	const inline SubGameBoard<Square>& getSubGameBoard(unsigned row, unsigned col) const { return data[row][col]; }

	// Set value of a sub GameBoard
	void setSubGameBoard(unsigned row, unsigned col, SubGameBoard<Square> value) { data[row][col] = value; }

	// Get a value inside sub GameBoard
	const Square& getValue(int row, int col, int subRow, int subCol) const { return data[row][col][subRow][subCol]; }

	// Set a value inside sub GameBoard
	void setValue(unsigned row, unsigned col, unsigned subRow, unsigned subCol, Square value) {
		data[row][col][subRow][subCol] = value;
		// positions for next move
		subNextRow_ = subRow;
		subNextCol_ = subCol;
	}

	// Return std::array representation
	SubGameBoard<SubGameBoard<Square>> toArray() const { return data; }

	int subNextRow() const { return subNextRow_; }
	int subNextCol() const { return subNextCol_; }
};

