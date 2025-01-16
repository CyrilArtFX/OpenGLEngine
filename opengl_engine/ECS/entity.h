#pragma once
#include "component.h"
#include <ServiceLocator/locator.h>
#include <vector>

class Entity
{
public:
	/**
	* Create a component attached to this entity.
	* @param	args	The parameters of the constructor of the component.
	* @return			The created component.
	*/
	template<class T, typename... Args>
	std::enable_if_t<std::is_base_of<Component, T>::value, T*>
		addComponentByClass(Args&&... args)
	{
		//  not sure if I do it like this or if I force every components to have no parameters in their constructor
	}


	/**
	* Get a component of given class in this entity's components.
	* @return	The first component of given class found, nullptr if no component of given class has been found.
	*/
	template<class T>
	std::enable_if_t<std::is_base_of<Component, T>::value, T*>
		getComponentByClass()
	{
		for (Component* component : components)
		{
			T* component_as_t = dynamic_cast<T*>(component);
			if (component_as_t)
			{
				return component_as_t;
			}
		}

		Locator::getLog().LogMessage_Category("Entity: Unable to find a component of given class.", LogCategory::Warning);
		return nullptr;
	}

	/**
	* Get all components of given class in this entity's components.
	* @return	A list of all components of given class found.
	*/
	template<class T>
	std::enable_if_t <std::is_base_of<Component, T>::value, std::vector<T*>>
		getComponentsByClass()
	{
		std::vector<T*> return_list;

		for (Component* component : components)
		{
			T* component_as_t = dynamic_cast<T*>(component);
			if (component_as_t)
			{
				return_list.push_back(component_as_t);
			}
		}

		return return_list;
	}

	/**
	* Get all components of this entity.
	* @return	A list of all components this entity has.
	*/
	std::vector<Component*> getAllComponents()
	{
		return components;
	}

private:
	std::vector<Component*> components;
};
