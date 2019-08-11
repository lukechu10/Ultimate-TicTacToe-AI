'use strict';

var ultimate = require('./build/Release/binding.node');

var test = new ultimate.uTicTacToe();

test.applyMove(1, 1, 0, 1, "player1");
test.applyMove(1, 1, 1, 1, "player1");
test.applyMove(1, 1, 2, 1, "player1");

test.checkSubWin(1, 1);
console.log(test.subWins())
console.log(test)

console.log("")