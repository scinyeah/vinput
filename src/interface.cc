#include <node.h>
#include <nan.h>
#include <v8.h>

#include "vinput.h"

NAN_METHOD(mouseMove) 
{
	if (info.Length() != 2)
		return;
	int32_t x = info[0]->Int32Value();
	int32_t y = info[1]->Int32Value();
	mouseMove(x, y);
}

NAN_METHOD(mousePress)
{
	if (info.Length() != 4)
		return;
	int32_t x = info[0]->Int32Value();
	int32_t y = info[1]->Int32Value();
	int32_t btn = info[2]->Int32Value();
	bool isDown = info[3]->BooleanValue();
	mousePress(x, y,btn,isDown);
}

NAN_METHOD(keyPress)
{
	if (info.Length() != 2)
		return;
	int32_t keyCode = info[0]->Int32Value();
	bool isDown = info[1]->BooleanValue();
	keyPress(keyCode, isDown);
}


NAN_MODULE_INIT(Initialize) {
	Nan::Set(target, Nan::New<v8::String>("mouseMove").ToLocalChecked(),
		Nan::GetFunction(Nan::New<v8::FunctionTemplate>(mouseMove)).ToLocalChecked());
	Nan::Set(target, Nan::New<v8::String>("mousePress").ToLocalChecked(),
		Nan::GetFunction(Nan::New<v8::FunctionTemplate>(mousePress)).ToLocalChecked());
	Nan::Set(target, Nan::New<v8::String>("keyPress").ToLocalChecked(),
		Nan::GetFunction(Nan::New<v8::FunctionTemplate>(keyPress)).ToLocalChecked());
}

NODE_MODULE(vinput, Initialize)