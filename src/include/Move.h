#pragma once

#include "GameBoard.h"

struct Move {
	unsigned row = 0;
	unsigned col = 0;
	unsigned subRow = 0;
	unsigned subCol = 0;

	Square who = Square::Blank;

	// constructor
	Move(unsigned row, unsigned col, unsigned subRow, unsigned subCol, Square who) {
		this->row = row;
		this->col = col;
		this->subRow = subRow;
		this->subCol = subCol;
		this->who = who;
	}

	// create blank Move with default values
	Move() {}
};

