#include "UltimateTicTacToe.h"

using namespace std;

UltimateTicTacToe::UltimateTicTacToe() {
  // initialize subWins
  for (unsigned row = 0; row < 3; row++) {
    for (unsigned col = 0; col < 3; col++) {
      subWins[row][col] = Square::Blank;
    }
  }
}

vector<Move> UltimateTicTacToe::availibleMoves(Square who) {
  vector<Move> results;

  // check if subNext == -1 -1 or subWin set
  if ((data.subNextRow() == -1 && data.subNextCol() == -1) ||
      subWins[data.subNextRow()][data.subNextCol()] != Square::Blank) {
    // get all tiles availible
    for (unsigned winRow = 0; winRow < 3; winRow++) {
      for (unsigned winCol = 0; winCol < 3; winCol++) {
        if (subWins[winRow][winCol] == Square::Blank) {
          // get all empty squares
          for (unsigned subRow = 0; subRow < 3; subRow++) {
            for (unsigned subCol = 0; subCol < 3; subCol++) {
              if (data.getSubGameBoard(winRow, winCol)[subRow][subCol] ==
                  Square::Blank) {
                results.push_back(Move(winRow, winCol, subRow, subCol, who));
              }
            }
          }
          //
        }
      }
    }
  }

  else {
    if (subWins[data.subNextRow()][data.subNextCol()] == Square::Blank) {
      // get moves is subWins[data.subNextRow][data.subNextCol]
      for (unsigned row = 0; row < 3; row++) {
        for (unsigned col = 0; col < 3; col++) {
          if (data.getValue(data.subNextRow(), data.subNextCol(), row, col) ==
              Square::Blank) {
            // square is availible
            results.push_back(
                Move(data.subNextRow(), data.subNextCol(), row, col, who));
          }
        }
      }
    }
  }

  return results;
}

Move UltimateTicTacToe::getMoveFromInput(Square who) {
  // check if sub game board is won already
  if (subWins[data.subNextRow()][data.subNextCol()] == Square::Blank &&
      data.subNextRow() != -1 && data.subNextCol() != -1) {
    string input; // input buffer
    int subRow, subCol;

    cout << "Sub game board is row: " << data.subNextRow()
         << " col: " << data.subNextCol() << "\n";
    cout << "Enter sub row:\n>";
    cin >> input;
    subRow = stoi(input);

    cout << "Enter sub colomn:\n>";
    cin >> input;
    subCol = stoi(input);

    // check if move is valid
    if (subRow <= 2 && subCol <= 2 && subRow >= 0 && subCol >= 0 &&
        data.getValue(data.subNextRow(), data.subNextCol(), subRow, subCol) ==
            Square::Blank)
      return Move(data.subNextRow(), data.subNextCol(), subRow, subCol, who);
    else {
      cout << "Move is invalid, please try again\n";
      return getMoveFromInput(who); // ask user for new input
    }
  } else {
    string input; // input buffer
    int row, col, subRow, subCol;

    cout << "Enter row:\n>";
    cin >> input;
    row = stoi(input);

    cout << "Enter colomn:\n>";
    cin >> input;
    col = stoi(input);

    cout << "Enter sub row:\n>";
    cin >> input;
    subRow = stoi(input);

    cout << "Enter sub colomn:\n>";
    cin >> input;
    subCol = stoi(input);

    // check if move is valid
    if (row <= 2 && col <= 2 && subRow <= 2 && subCol <= 2 && row >= 0 &&
        col >= 0 && subRow >= 0 && subCol >= 0 &&
        data.getValue(row, col, subRow, subCol) == Square::Blank)
      return Move(row, col, subRow, subCol, who);
    else {
      cout << "Move is invalid, please try again\n";
      return getMoveFromInput(who); // ask user for new input
    }
  }
}

Square UltimateTicTacToe::checkForWinGlobal() {
  // Checking for Rows for X or O victory.
  for (int row = 0; row < 3; row++) {
    if (subWins[row][0] == subWins[row][1] &&
        subWins[row][1] == subWins[row][2] &&
        subWins[row][0] != Square::Blank) {
      return subWins[row][0];
    }
  }

  // Checking for Columns for X or O victory.
  for (int col = 0; col < 3; col++) {
    if (subWins[0][col] == subWins[1][col] &&
        subWins[1][col] == subWins[2][col] &&
        subWins[0][col] != Square::Blank) {
      return subWins[0][col];
    }
  }

  // Checking for Diagonals for X or O victory.
  if (subWins[0][0] == subWins[1][1] && subWins[1][1] == subWins[2][2] &&
      subWins[0][0] != Square::Blank) {
    return subWins[0][0];
  }

  if (subWins[0][2] == subWins[1][1] && subWins[1][1] == subWins[2][0] &&
      subWins[0][2] != Square::Blank) {
    return subWins[0][2];
  }

  // Else if none of them have won then return 0
  return Square::Blank;
  // Win check
}

std::ostream &operator<<(std::ostream &os, const UltimateTicTacToe &b) {
#ifdef _WIN32
  HANDLE hConsole;

  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

  for (int row = 0; row < 3; row++) {
    for (int subRow = 0; subRow < 3; subRow++) {
      for (int col = 0; col < 3; col++) {
#ifdef _WIN32
        if (row == b.data.subNextRow() && col == b.data.subNextCol())
          SetConsoleTextAttribute(hConsole, 10); // green
        else
          SetConsoleTextAttribute(hConsole, 7); // white
#endif
        for (int subCol = 0; subCol < 3; subCol++) {
          os << " " << b.data.toArray()[row][col][subRow][subCol] << " ";
        }
        os << "  ";
      }
      os << '\n';
    }
    os << '\n';
  }
#ifdef _WIN32
  SetConsoleTextAttribute(hConsole, 7); // white
#endif
  return os;
}

SubGameBoard<SubGameBoard<Square>> UltimateTicTacToe::toArray() {
  return data.toArray();
}