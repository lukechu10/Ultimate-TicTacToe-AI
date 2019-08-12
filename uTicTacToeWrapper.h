#pragma once

#include <napi.h>

#include "UltimateTicTacToe.h"
#include "MoveWrapper.h"


class uTicTacToe : public Napi::ObjectWrap<uTicTacToe>
{
public:
	static Napi::Object Init(Napi::Env env, Napi::Object exports);
	uTicTacToe(const Napi::CallbackInfo &info);

private:
	static Napi::FunctionReference constructor;

	// wrapped class
	UltimateTicTacToe game;

	// instance methods

	// To Napi::Array
	Napi::Value toArray(const Napi::CallbackInfo &info);
	// Get value
	Napi::Value getValue(const Napi::CallbackInfo &info);
	// Availible moves
	Napi::Value availibleMoves(const Napi::CallbackInfo &info);
	// Apply Move
	Napi::Value applyMove(const Napi::CallbackInfo &info);
	// Check for sub wins
	Napi::Value checkSubWin(const Napi::CallbackInfo &info);
	// Get sub wins array
	Napi::Value subWins(const Napi::CallbackInfo &info);

	// Get global win
	Napi::Value checkForWinGlobal(const Napi::CallbackInfo &info);
};