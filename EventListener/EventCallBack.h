#pragma once

#include <functional>

#define CreateEventCallback(ClassName, ClassInstance, FunctionName) EventCallBack(ClassInstance, std::bind(&ClassName::FunctionName, ClassInstance, std::placeholders::_1))

enum EventPhase : uint8_t {
	E_Pre = 0,
	E_Post = 1
};

struct EventData {
	const virtual unsigned int GetEventID() = 0;

	template<typename T>
	T* Cast() { return dynamic_cast<T*>(this); };
};

struct EventCallBack {
	EventCallBack(void* callBackObject, std::function<void(EventData*)> callBackFunction);

	void Call(EventData* Data);

	bool equal(EventCallBack callback);
	bool equal(void* callback);
private:
	std::function<void(EventData*)> callBackFunction;
	void* callBackObject;
};

