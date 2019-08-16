#include "headers.h"
using namespace std;

#include "uTicTacToeWrapper.h"

Napi::String Method(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	return Napi::String::New(env, "world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, Method));
	uTicTacToe::Init(env, exports);
	WrappedMove::Init(env, exports);
	return exports;
}

NODE_API_MODULE(uTicTacToe, Init)