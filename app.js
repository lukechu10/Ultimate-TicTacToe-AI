'use strict';

var ultimate = require('./build/Release/uTicTacToe.node');

var test = new ultimate.uTicTacToe();

test.applyMove(1, 1, 0, 1, "player1");
test.applyMove(1, 1, 1, 1, "player1");
test.applyMove(1, 1, 2, 1, "player1");
test.checkSubWin(1, 1)

test.applyMove(0, 1, 0, 1, "player1");
test.applyMove(0, 1, 1, 1, "player1");
test.applyMove(0, 1, 2, 1, "player1");
test.checkSubWin(0, 1)

test.applyMove(2, 1, 0, 1, "player1");
//test.applyMove(2, 1, 1, 1, "player1");
test.applyMove(2, 1, 2, 1, "player1");
test.checkSubWin(2, 1)

var move = test.bestMove("player2")
test.applyMove(move.row, move.col, move.subRow, move.subCol, move.who);
console.log(move);
test.checkSubWin(move.row, move.col);
console.log(test.checkForWinGlobal());
console.log(test.toArray())
console.log("Finished");