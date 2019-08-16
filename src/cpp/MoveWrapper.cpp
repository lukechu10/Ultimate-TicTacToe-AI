#include "MoveWrapper.h"

using namespace std;
Napi::FunctionReference WrappedMove::constructor;

Napi::Object WrappedMove::Init(Napi::Env env, Napi::Object exports) {
	Napi::HandleScope scope(env);
	// hook methods
	Napi::Function func = DefineClass(env, "Move", {
		//InstanceValue("row", Napi::Value())
		});


	// Create a peristent reference to the class constructor. This will allow
	// a function called on a class prototype and a function
	// called on instance of a class to be distinguished from each other.
	constructor = Napi::Persistent(func);
	// Call the SuppressDestruct() method on the static data prevent the calling
	// to this destructor to reset the reference when the environment is no longer
	// available.
	constructor.SuppressDestruct();
	exports.Set("Move", func);
	return exports;
}

WrappedMove::WrappedMove(const Napi::CallbackInfo& info) : Napi::ObjectWrap<WrappedMove>(info) {
	Napi::Env env = info.Env();
	//Napi::HandleScope scope(env);

	if (info.Length() != 5) throw Napi::Error::New(env, "Invalid argument length");
	int row = info[0].As<Napi::Number>();
	int col = info[1].As<Napi::Number>();
	int subRow = info[2].As<Napi::Number>();
	int subCol = info[3].As<Napi::Number>();

	// check if number is between 0 and 3 inclusive
	if (row < 0 || row > 3) throw Napi::Error::New(env, "Invalid argument. Argument row must be between 0 and 3 inclusive");
	if (col < 0 || col > 3) throw Napi::Error::New(env, "Invalid argument. Argument col must be between 0 and 3 inclusive");
	if (subRow < 0 || subRow > 3) throw Napi::Error::New(env, "Invalid argument. Argument subRow must be between 0 and 3 inclusive");
	if (subCol < 0 || subCol > 3) throw Napi::Error::New(env, "Invalid argument. Argument subCol must be between 0 and 3 inclusive");

	string whoStr = info[4].As<Napi::String>();

	Square who = Square::Blank;
	// check string argument
	if ((string)whoStr == "player1")
		who = Square::Player1;
	else if ((string)whoStr == "player2")
		who = Square::Player2;
	else // invalid argument
		throw Napi::Error::New(env, "Invalid argument. Must have value of either \"player1\" or \"player2\"");
}
