#include "event_zeroParam.h"
#include <algorithm>

void Event_ZeroParam::registerObserver(Observer_ZeroParam* observer)
{
	observers.push_back(observer);
}

void Event_ZeroParam::unregisterObserver(Observer_ZeroParam* observer)
{
	auto iter = std::find(observers.begin(), observers.end(), observer);
	if (iter == observers.end()) return;

	std::iter_swap(iter, observers.end() - 1);
	observers.pop_back();
}

void Event_ZeroParam::broadcast() const
{
	for (auto& observer : observers)
	{
		observer->onEventObserved();
	}
}
