#pragma once
#include <vector>
#include <functional>

template <typename... params>
class Event;

template <typename... params>
class EventListener
{
public:

	std::vector<Event<params...>*> subscribedEvents;
	std::function<void(params...)> Trigger;

	EventListener(std::function<void(params...)> function) {
		Trigger = function;
	}

	~EventListener();
};

template <typename... params>
class Event
{
	std::vector<EventListener<params...>*> eventListeners;

public:

	void Invoke(params... args) {
		for (size_t i = 0; i < eventListeners.size(); i++)
		{		
			if (eventListeners.at(i)) {
				eventListeners.at(i)->Trigger(args...);
			} 
		}
	}

	void AddListener(EventListener<params...>* newListener) {
		eventListeners.push_back(newListener);
		newListener->subscribedEvents.push_back(this);
	}

	void RemoveListener(EventListener<params...>* listenerToRemove) {
		for (int i = eventListeners.size() - 1; i >= 0; i--)
		{
			if (eventListeners.at(i) == listenerToRemove) {
				eventListeners.erase(eventListeners.begin() + i);
				break;
			}
		}
	}

	void CompletelyRemoveListener(EventListener<params...>* listenerToRemove) {
		for (int i = eventListeners.size() - 1; i >= 0; i--)
		{
			if (eventListeners.size() != 0 && eventListeners.at(i) == listenerToRemove) {
				eventListeners.erase(eventListeners.begin() + i);
			}
		}
	}
};

template <typename... params>
EventListener<params...>::~EventListener() {
	for (size_t i = 0; i < subscribedEvents.size(); i++)
	{
		subscribedEvents.at(i)->CompletelyRemoveListener(this);
	}
}