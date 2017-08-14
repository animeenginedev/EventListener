#include "EventCallBack.h"


EventCallBack::EventCallBack(void * callBackObject, std::function<void(EventData*)> callBackFunction) {
	this->callBackObject = callBackObject;
	this->callBackFunction = callBackFunction;
}

void EventCallBack::Call(EventData * Data) {
	callBackFunction(Data);
}

bool EventCallBack::equal(EventCallBack callback) {
	return this->callBackObject == callback.callBackObject;
}

bool EventCallBack::equal(void * callback) {
	return this->callBackObject == callback;
}
