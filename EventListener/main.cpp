#include "Event.h"

#include <iostream>
#include <string>

enum CustomEvents : uint16_t {
	CE_CustomEventData = 1,
};

struct CustomEventData : public EventData {
	std::string message;

	//Make sure to have a non overlapping EventID between events.
	const unsigned int GetEventID() override { return CustomEvents::CE_CustomEventData; };
};

class RecieverClass {
public:
	void PrintMessageEvent(EventData* Data) {
		//Cast to the data structure that holds your actual data.
		auto ConvertedData = Data->Cast<CustomEventData>();
		//Nothing should go wrong, but if the dynamic_cast fails you will get a nullptr returned.
		if (ConvertedData != nullptr) {
			std::cout << ConvertedData->message << std::endl;
		}
	}
};

int main() {
	RecieverClass Instance;
	//Add the Instance of the RecieverClass as a recipent.
	Event::addHook(CustomEvents::CE_CustomEventData, EventPhase::E_Pre, CreateEventCallback(RecieverClass, &Instance, PrintMessageEvent));

	//Test Sending an Event
	CustomEventData* Event = new CustomEventData();
	Event->message = "PreEventTest";
	Event::sendEvent(CustomEvents::CE_CustomEventData, EventPhase::E_Pre, Event);
	//A hook isn't added for the post even so this doesn't actually appear.
	Event->message = "PostEventTest";
	Event::sendEvent(CustomEvents::CE_CustomEventData, EventPhase::E_Post, Event);

	//Now the hook gets added and it will output
	Event::addHook(CustomEvents::CE_CustomEventData, EventPhase::E_Post, CreateEventCallback(RecieverClass, &Instance, PrintMessageEvent));
	Event::sendEvent(CustomEvents::CE_CustomEventData, EventPhase::E_Post, Event);

	//Remeber to clean up the event. If you're using multiple threads you might want to consider using shared pointers rather then deleting it manually.
	delete Event;


	int i = 0;
	std::cin >> i;

	return 0;
}