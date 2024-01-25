#pragma once
#include "observer_zeroParam.h"
#include <vector>


class Event_ZeroParam
{
public:
	void registerObserver(Observer_ZeroParam* observer);
	void unregisterObserver(Observer_ZeroParam* observer);

	void broadcast() const;


private:
	std::vector<Observer_ZeroParam*> observers;
};

