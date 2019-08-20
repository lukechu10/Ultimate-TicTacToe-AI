#include "UltimateTicTacToe.h"

#include <array>
#include <limits>
#include <utility>

using namespace std;

Square opponent(Square who) {
  if (who == Square::Player1)
    return Square::Player2;
  return Square::Player1;
}

template <typename T>
unsigned countNum(T first, T second, T third, const T what) {
  unsigned count = 0;
  if (first == what)
    count++;
  if (second == what)
    count++;
  if (third == what)
    count++;
  return count;
}

// max: player1
// min: player2
// evaluate a quadrant
int UltimateTicTacToe::evaluateBasicBoard(SubGameBoard<Square> subGameBoard) {
  int evaluateVal = 0;
  // evaluate rows
  for (auto &row : subGameBoard) {
    int max = (int)count(row.begin(), row.end(), Square::Player1);
    int min = (int)count(row.begin(), row.end(), Square::Player2);
    if (max == 0)
      evaluateVal -= (min == 2) ? 3 : min;
    else if (min == 0)
      evaluateVal += (max == 2) ? 3 : max;
  }
  // evaluate cols
  for (unsigned col = 0; col < 3; col++) {
    int max = (int)countNum(subGameBoard[0][col], subGameBoard[1][col],
                            subGameBoard[2][col], Square::Player1);
    int min = (int)countNum(subGameBoard[0][col], subGameBoard[1][col],
                            subGameBoard[2][col], Square::Player2);
    if (max == 0)
      evaluateVal -= (min == 2) ? 3 : min;
    else if (min == 0)
      evaluateVal += (max == 2) ? 3 : max;
  }
  // evaluate diaganol
  {
    int max = (int)countNum(subGameBoard[0][0], subGameBoard[1][1],
                            subGameBoard[2][2], Square::Player1);
    int min = (int)countNum(subGameBoard[0][0], subGameBoard[1][1],
                            subGameBoard[2][2], Square::Player2);
    if (max == 0)
      evaluateVal -= (min == 2) ? 3 : min;
    else if (min == 0)
      evaluateVal += (max == 2) ? 3 : max;
  }
  // evaluate anti-diaganol
  {
    int max = (int)countNum(subGameBoard[0][2], subGameBoard[1][1],
                            subGameBoard[2][0], Square::Player1);
    int min = (int)countNum(subGameBoard[0][2], subGameBoard[1][1],
                            subGameBoard[2][0], Square::Player2);
    if (max == 0)
      evaluateVal -= (min == 2) ? 3 : min;
    else if (min == 0)
      evaluateVal += (max == 2) ? 3 : max;
  }
  return evaluateVal;
}

SubGameBoard<int> UltimateTicTacToe::generateCoefs() {
  SubGameBoard<int> res;
  array<int, 3> temp;
  temp.fill(0);
  res.fill(temp);
  // evaluate rows
  for (unsigned row = 0; row < 3; row++) {
    int max =
        (int)count(subWins[row].begin(), subWins[row].end(), Square::Player1);
    int min =
        (int)count(subWins[row].begin(), subWins[row].end(), Square::Player2);
    if ((max != 0 && min != 0) || (max == 0 && min == 0)) {
      res[row][0] += 1;
      res[row][1] += 1;
      res[row][2] += 1;
    } else if (max != 0 && min != 0) {
      // do nothing
    } else {
      res[row][0] += (max + min) * 2;
      res[row][1] += (max + min) * 2;
      res[row][2] += (max + min) * 2;
    }
  }
  // evaluate cols
  for (unsigned col = 0; col < 3; col++) {
    int max = (int)countNum(subWins[0][col], subWins[1][col], subWins[2][col],
                            Square::Player1);
    int min = (int)countNum(subWins[0][col], subWins[1][col], subWins[2][col],
                            Square::Player2);
    if ((max != 0 && min != 0) || (max == 0 && min == 0)) {
      res[0][col] += 1;
      res[1][col] += 1;
      res[2][col] += 1;
    } else if (max != 0 && min != 0) {
      // do nothing
    } else {
      res[0][col] += (max + min) * 2;
      res[1][col] += (max + min) * 2;
      res[2][col] += (max + min) * 2;
    }
  }
  // evaluate diaganol
  {
    int max = (int)countNum(subWins[0][0], subWins[1][1], subWins[2][2],
                            Square::Player1);
    int min = (int)countNum(subWins[0][0], subWins[1][1], subWins[2][2],
                            Square::Player2);
    if ((max != 0 && min != 0) || (max == 0 && min == 0)) {
      res[0][0] += 1;
      res[1][1] += 1;
      res[2][2] += 1;
    } else if (max != 0 && min != 0) {
      // do nothing
    } else {
      res[0][0] += (max + min) * 2;
      res[1][1] += (max + min) * 2;
      res[2][2] += (max + min) * 2;
    }
  }
  // evaluate anti-diaganol
  {
    int max = (int)countNum(subWins[0][2], subWins[1][1], subWins[2][0],
                            Square::Player1);
    int min = (int)countNum(subWins[0][2], subWins[1][1], subWins[2][0],
                            Square::Player2);
    if (max == 0 && min == 0) {
      res[0][2] += 1;
      res[1][1] += 1;
      res[2][0] += 1;
    } else if (max != 0 && min != 0) {
      // do nothing
    } else {
      res[0][2] += (max + min) * 2;
      res[1][1] += (max + min) * 2;
      res[2][0] += (max + min) * 2;
    }
  }
  return res;
}

// evaluate all quadrants and multiply by coefficient
int UltimateTicTacToe::evaluate() {
  int val = 0;
  SubGameBoard<int> coefs =
      /*{ { { 3, 2, 3 }, { 2, 4, 2 }, {3, 2, 2} } }; // */ generateCoefs();

  for (unsigned row = 0; row < 3; row++) {
    for (unsigned col = 0; col < 3; col++) {
      if (subWins[row][col] == Square::Blank)
        val += evaluateBasicBoard(data.getSubGameBoard(row, col)) *
               coefs[row][col];
      else if (subWins[row][col] == Square::Player1)
        val += 100 * coefs[row][col];
      else
        val -= 100 * coefs[row][col];
    }
  }

  return val;
}

// main minimax function
// max: player1
// min: player2
int UltimateTicTacToe::minimax(bool isMax, int depth, int alpha, int beta) {

  // end state or depth
  auto globalWin = checkForWinGlobal();
  if (globalWin != Square::Blank) {
    return (globalWin == Square::Player1) ? (INT_MAX - 1) : (INT_MIN + 1);
  }
  if (depth == 6) {
    return evaluate();
  }

  // isMax if is Square::Player1's turn

  signed int bestValue = isMax ? INT_MIN : INT_MAX;

  // get availible moves
  auto moves = availibleMoves(isMax ? Square::Player1 : Square::Player2);
  for (auto &move : moves) {
    // apply move
    applyMove(move);
    // update subWins
    checkForFull(move.row, move.col);

    if (isMax) {
      bestValue = max(bestValue, minimax(false, depth + 1, alpha, beta));
      alpha = max(alpha, bestValue);
    } else {
      bestValue = min(bestValue, minimax(true, depth + 1, alpha, beta));
      beta = min(beta, bestValue);
    }

    // undo move
    move.who = Square::Blank;
    applyMove(move);
    checkForFull(move.row, move.col);
    subWins[move.row][move.col] = Square::Blank;

    // Alpha Beta Pruning
    if (beta <= alpha)
      break;
  }

  // depth
  if (bestValue < 0)
    bestValue++;

  if (bestValue > 0)
    bestValue--;

  // deduce return value;
  return bestValue;
}

Move UltimateTicTacToe::bestMove(Square who) {
  int alpha = INT_MIN;
  int beta = INT_MAX;
  // end state or depth
  if (checkForWinGlobal() != Square::Blank) {
    throw runtime_error("Game is already in final state");
  }

  signed int bestValue = (who == Square::Player1) ? INT_MIN : INT_MAX;
  int bestIndex = 0;

  auto moves = availibleMoves(who);
  // vector<int> values(moves.size(), 0); // vector to store values of each
  // individual move

  for (unsigned i = 0; i < moves.size(); i++) {
    // apply move
    applyMove(moves[i]);
    // update subWins
    checkForFull(moves[i].row, moves[i].col);

    if (who == Square::Player1) {
      auto temp = minimax(false, 0, INT_MIN, INT_MAX);
      if (bestValue < temp) {
        bestValue = temp;
        bestIndex = i;
        alpha = max(alpha, bestValue);
      }
    } else {
      auto temp = minimax(true, 0, INT_MIN, INT_MAX);
      if (bestValue > temp) {
        bestValue = temp;
        bestIndex = i;
        beta = min(beta, bestValue);
      }
    }

    // undo move
    moves[i].who = Square::Blank;
    applyMove(moves[i]);
    // reset move
    moves[i].who = who;
    // checkSubWin(moves[i].row, moves[i].col);
    subWins[moves[i].row][moves[i].col] = Square::Blank;
    checkForFull(moves[i].row, moves[i].col);

    // Alpha Beta Pruning
    if (beta <= alpha)
      break;
  }

  return moves[bestIndex];
}