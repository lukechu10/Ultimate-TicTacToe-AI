#include "uTicTacToeWrapper.h"

using namespace std;

Napi::FunctionReference uTicTacToe::constructor;

Napi::Object uTicTacToe::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  // hook methods
  Napi::Function func = DefineClass(
      env, "uTictacToe",
      {InstanceMethod("toArray", &uTicTacToe::toArray),
       InstanceMethod("getValue", &uTicTacToe::getValue),
       InstanceMethod("availibleMoves", &uTicTacToe::availibleMoves),
       InstanceMethod("applyMove", &uTicTacToe::applyMove),
       InstanceMethod("checkSubWin", &uTicTacToe::checkSubWin),
       InstanceMethod("subWins", &uTicTacToe::subWins),
       InstanceMethod("checkForWinGlobal", &uTicTacToe::checkForWinGlobal),
       InstanceMethod("bestMove", &uTicTacToe::bestMove),
       InstanceMethod("evaluate", &uTicTacToe::evaluate)});

  // Create a peristent reference to the class constructor. This will allow
  // a function called on a class prototype and a function
  // called on instance of a class to be distinguished from each other.
  constructor = Napi::Persistent(func);
  // Call the SuppressDestruct() method on the static data prevent the calling
  // to this destructor to reset the reference when the environment is no longer
  // available.
  constructor.SuppressDestruct();
  exports.Set("uTicTacToe", func);
  return exports;
}

uTicTacToe::uTicTacToe(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<uTicTacToe>(info) {
  Napi::Env env = info.Env();

  int length = info.Length(); // constructor arguments
}

inline string squareToString(Square sq) {
  switch (sq) {
  case Square::Blank:
    return "blank";
  case Square::Player1:
    return "player1";
  case Square::Player2:
    return "player2";
  case Square::Full:
    return "full";
  }
  return "error";
}

Napi::Value uTicTacToe::toArray(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  // check if number of arguments is 0
  if (info.Length() != 0) {
    throw Napi::Error::New(env, "Invalid argument length");
  }

  auto data = game.toArray(); // data

  Napi::Array res = Napi::Array::New(env, 3);
  // fill array
  for (unsigned row = 0; row < 3; row++) {
    // create sub array
    res.Set(row, Napi::Array::New(env, 3));
// Napi::Array &rowData = res.Get(row).As<Napi::Array>();
#define rowData res.Get(row).As<Napi::Array>()
    for (unsigned col = 0; col < 3; col++) {
      rowData.Set(col, Napi::Array::New(env, 3));
      // Napi::Array &colData = rowData.Get(col).As<Napi::Array>();
#define colData rowData.Get(col).As<Napi::Array>()
      for (unsigned subRow = 0; subRow < 3; subRow++) {
        colData.Set(subRow, Napi::Array::New(env, 3));
        // Napi::Array &subRowData = colData.Get(subRow).As<Napi::Array>();
#define subRowData colData.Get(subRow).As<Napi::Array>()
        for (unsigned subCol = 0; subCol < 3; subCol++) {
          // assign data
          subRowData.Set(
              subCol, Napi::String::New(
                          env, squareToString(data[row][col][subRow][subCol])));
        }
      }
    }
  }
  // undefs
#undef rowData
#undef colData
#undef subRowData
  // return result
  return res;
}

Napi::Value uTicTacToe::getValue(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  // check arguments
  if (info.Length() != 4)
    throw Napi::Error::New(env, "Invalid argument length");
  int row = info[0].As<Napi::Number>();
  int col = info[1].As<Napi::Number>();
  int subRow = info[2].As<Napi::Number>();
  int subCol = info[3].As<Napi::Number>();

  return Napi::String::New(
      env, squareToString(game.toArray()[row][col][subRow][subCol]));
}

Napi::Value uTicTacToe::availibleMoves(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  // argument for specifying which player
  if (info.Length() != 1)
    throw Napi::Error::New(env, "Invalid argument length");

  Napi::String whoStr = info[0].ToString();

  Square who = Square::Blank;

  if ((string)whoStr == "player1")
    who = Square::Player1;
  else if ((string)whoStr == "player2")
    who = Square::Player2;
  else // invalid argument
    throw Napi::Error::New(env, "Invalid argument. Must have value of either "
                                "\"player1\" or \"player2\"");

  auto moves = game.availibleMoves(who);

  Napi::Array res = Napi::Array::New(env, moves.size());
  // fill array with moves
  for (unsigned i = 0; i < moves.size(); i++) {
    Napi::Object item = Napi::Object::New(env);
    item.Set("row", moves[i].row);
    item.Set("col", moves[i].col);
    item.Set("subRow", moves[i].subRow);
    item.Set("subCol", moves[i].subCol);
    item.Set("who", squareToString(moves[i].who));
    res.Set(i, item);
  }
  return res;
}

Napi::Value uTicTacToe::applyMove(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  // arg[4]
  Square who = Square::Blank;

  // check string argument
  if ((string)info[4].As<Napi::String>() == "player1")
    who = Square::Player1;
  else if ((string)info[4].As<Napi::String>() == "player2")
    who = Square::Player2;
  else // invalid argument
    throw Napi::Error::New(env, "Invalid argument. Must have value of either "
                                "\"player1\" or \"player2\"");

  // get move
  Move mv(info[0].As<Napi::Number>(), info[1].As<Napi::Number>(),
          info[2].As<Napi::Number>(), info[3].As<Napi::Number>(), who);
  game.applyMove(mv); // update gameboard
  return Napi::Value();
}

Napi::Value uTicTacToe::checkSubWin(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  int row = info[0].As<Napi::Number>();
  int col = info[1].As<Napi::Number>();
  // call wrapped function
  game.checkSubWin(row, col);
  game.checkSubWin(1, 1);

  return Napi::Value();
}

Napi::Value uTicTacToe::subWins(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  auto data = game.subWins;
  Napi::Array res = Napi::Array::New(env, 3);

  // fill res
  for (unsigned i = 0; i < 3; i++) {
    res.Set(i, Napi::Array::New(env, 3));
    // Napi::Array &col = res.Get(i).As<Napi::Array>();
#define col res.Get(i).As<Napi::Array>()
    for (unsigned n = 0; n < 3; n++) {
      col.Set(n, squareToString(data[i][n]));
    }
#undef col
  }

  return res;
}

Napi::Value uTicTacToe::checkForWinGlobal(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  auto data = game.checkForWinGlobal();

  return Napi::String::New(env, squareToString(data));
}

Napi::Value uTicTacToe::bestMove(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  // parse square
  auto whoStr = info[0].As<Napi::String>();
  Square who;
  // check string argument
  if ((string)whoStr == "player1")
    who = Square::Player1;
  else if ((string)whoStr == "player2")
    who = Square::Player2;
  else // invalid argument
    throw Napi::Error::New(env, "Invalid argument. Must have value of either "
                                "\"player1\" or \"player2\"");

  try { // bestMove can throw exception
    Move data = game.bestMove(who);

    Napi::Object res = Napi::Object::New(env);
    res.Set("row", data.row);
    res.Set("col", data.col);
    res.Set("subRow", data.subRow);
    res.Set("subCol", data.subCol);
    res.Set("who", squareToString(data.who));
    return res;
  } catch (exception &e) {
    throw Napi::Error::New(env, e.what());
  }
}

Napi::Value uTicTacToe::evaluate(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  return Napi::Value::From(env, game.evaluate());
}