#include "Event.h"

std::unordered_map<unsigned int, std::array<std::vector<EventCallBack>, 2>> Event::hookedEvents;

void Event::sendEvent(unsigned int type, EventPhase phase, EventData * data) {
	auto f = hookedEvents.find(type);
	if (f != hookedEvents.end()) {
		for (auto Hook : f->second[phase]) {
			Hook.Call(data);
		}
	}
}

void Event::addHook(unsigned int type, EventPhase phase, EventCallBack callback) {
	auto f = hookedEvents.find(type);
	if (f == hookedEvents.end()) {
		hookedEvents.insert(std::make_pair(type, std::array<std::vector<EventCallBack>, 2>()));
		f = hookedEvents.find(type);
	}
	f->second[phase].push_back(callback);
}

void Event::removeHook(unsigned int type, EventPhase phase, void * callback) {
	auto f = hookedEvents.find(type);
	if (f != hookedEvents.end()) {
		erased:
		for (auto it = f->second[phase].begin(); it != f->second[phase].end(); it++) {
			if (it->equal(callback)) {
				f->second[phase].erase(it);
				//Restart the iteration because we've just invalidated it.
				goto erased;
			}
		}
	}
}

void Event::removeAllHooks(void * callback) {
	for(auto T : hookedEvents) {
		for (auto iter : T.second) {
			erased:
			for (auto it = iter.begin(); it != iter.end(); it++) {
				if (it->equal(callback)) {
					T.second[0].erase(it);
					//Restart the iteration because we've just invalidated it.
					goto erased;
				}
			}
		}		
	}
}