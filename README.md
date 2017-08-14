# EventListener
Simple Event Listner system.

Just a framework to call bound functions remotely. I use it mainly for events that need to go to a lot of different places and I don't want to think too much about the structure if I don't include it in the initial design. Screen Resizing is a good example of something that may need to be told to a lot of objects, changing configuration options like audio is another.

One macro is defined to make it simpler to create a CallBack, 

#define CreateEventCallback(ClassName, ClassInstance, FunctionName) EventCallBack(ClassInstance, std::bind(&ClassName::FunctionName, ClassInstance, std::placeholders::_1))

and it's really just there to make it a bit easier writing the std::bind function. Otherwise, the main.cpp contains a demo of how to use the event listener setup.
