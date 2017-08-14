#pragma once

#include <unordered_map>
#include <vector>
#include <array>

#include "EventCallBack.h"

class Event {
public:
	static void sendEvent(unsigned int type, EventPhase phase, EventData* data);
	static void addHook(unsigned int type, EventPhase phase, EventCallBack callback);
	static void removeHook(unsigned int type, EventPhase phase, void* callback);
	
	static void removeAllHooks(void* callback);

private:
	static std::unordered_map<unsigned int, std::array<std::vector<EventCallBack>, 2>> hookedEvents;
};
