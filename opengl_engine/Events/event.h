#pragma once
#include "observer.h"
#include <unordered_map>
#include <vector>
#include <functional>


template<typename ...Parameters>
class Event
{
public:
	using Function = std::function<void(Parameters...)>;

	void registerObserver(Observer* observer, Function broadcastFunction)
	{
		observers[observer] = broadcastFunction;
	}

	void unregisterObserver(Observer* observer)
	{
		if (inBroadcast)
		{
			pendingObservers.push_back(observer);
		}
		else
		{
			auto iter = observers.find(observer);
			if (iter == observers.end()) return;

			observers.erase(iter);
		}
	}


	void broadcast(Parameters ...parameters)
	{
		inBroadcast = true;
		for (auto observer : observers)
		{
			observer.second(parameters...);
		}
		inBroadcast = false;

		if (pendingObservers.empty()) return;
		for (auto pending_observer : pendingObservers)
		{
			unregisterObserver(pending_observer);
		}
		pendingObservers.clear();
	}


private:
	std::unordered_map<Observer*, Function> observers;
    std::vector<Observer*> pendingObservers;

	bool inBroadcast{ false };
};