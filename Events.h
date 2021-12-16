#pragma once
#include <vector>
#include <functional>
#include <iostream>

template <typename... params>
class Event;

template <typename... params>
class EventListener //Do not declare a listener who's function deletes itself
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
		for (auto& eventListener : eventListeners)
		{
			if (eventListener) {
				eventListener->Trigger(args...);
			}
		}
	}

	EventListener<params...>* AddListener(EventListener<params...>* newListener) {
		eventListeners.push_back(newListener);
		newListener->subscribedEvents.push_back(this);
		return newListener;
	}

	void RemoveListener(EventListener<params...>* listenerToRemove) {
		for (int i = eventListeners.size() - 1; i >= 0; i--)
		{
			if (eventListeners[i] == listenerToRemove) {
				eventListeners.erase(eventListeners.begin() + i);
				break;
			}
		}
	}

	void CompletelyRemoveListener(EventListener<params...>* listenerToRemove) {
		for (int i = eventListeners.size() - 1; i >= 0; i--)
		{
			if (eventListeners.size() != 0 && eventListeners[i] == listenerToRemove) {
				eventListeners.erase(eventListeners.begin() + i);
			}
		}
	}
};

template <typename... params>
EventListener<params...>::~EventListener() {
	for (auto& event : subscribedEvents)
	{
		event->CompletelyRemoveListener(this);
	}
}