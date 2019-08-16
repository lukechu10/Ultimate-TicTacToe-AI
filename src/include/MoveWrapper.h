#pragma once

#include <napi.h>
#include "Move.h"

class WrappedMove : public Napi::ObjectWrap<WrappedMove> {
public:
	static Napi::Object Init(Napi::Env env, Napi::Object exports);
	WrappedMove(const Napi::CallbackInfo& info);
private:
	static Napi::FunctionReference constructor;

	// wrapped class
	Move move;
};