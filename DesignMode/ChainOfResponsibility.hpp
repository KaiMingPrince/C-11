#pragma once
#include <memory>
#include <iostream>
class AbstractEvent
{
public:
	AbstractEvent() {
	}
	virtual ~AbstractEvent() {
	}

	virtual void EventProcess() {
	}
};

class TopLevelEvent : public AbstractEvent
{
public:
	TopLevelEvent() {
	}
	~TopLevelEvent() {
	}

	void EventProcess()
	{
		std::cout << "The Event has Process In TopLevel";
		AbstractEvent::EventProcess();
	}
};