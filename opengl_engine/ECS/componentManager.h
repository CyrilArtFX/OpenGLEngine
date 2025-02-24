#pragma once
#include "component.h"

#include <vector>
#include <unordered_map>
#include <memory>


/**
* Component List
* Base class for specialized component lists.
* A component list manage each components of a class and is responsible of storing them continuously in the memory.
*/
class ComponentList
{
public:
	ComponentList(size_t numComponentsPerList_)
	{
		numComponentsPerList = numComponentsPerList_;
	}


	/** Create a component and store it continuously with the other components of this class in the memory. */
	virtual std::shared_ptr<Component> createComponent() = 0;

	/** Remove a component from the list of this class of components. */
	virtual void deleteComponent(const std::shared_ptr<Component>& component) = 0;

	/** Update all components of the list of this class of components. */
	virtual void updateComponents() = 0;


	/** Get the maximum number of components of this class that can be stored in a single list. */
	size_t getNumComponentsPerList() { return numComponentsPerList; }

	/** Get every components of this class. */
	const std::vector<std::shared_ptr<Component>>& getAllComponents() const { return componentsShared; }

private:
	std::vector<std::shared_ptr<Component>> componentsShared;
	size_t numComponentsPerList;
};


template<class T>
class ComponentListByClass : ComponentList
{
public:
	ComponentListByClass(size_t numComponentsPerList_) : ComponentList(numComponentsPerList_)
	{
		ComponentSubList& sublist = componentSubLists.emplace_back();
		sublist.components = std::make_unique<T[]>(numComponentsPerList);
		sublist.freeSlots = numComponentsPerList;
	}

private:
	struct ComponentSubList
	{
		std::unique_ptr<T[]> components;
		size_t freeSlots = 0;
	};
	std::vector<ComponentSubList> componentSubLists;
};


class ComponentManager
{
public:
	/**  */
	template<typename T>
	static void AddComponentList(size_t classId)
	{
		componentLists[classId] = std::make_unique<ComponentListByClass<T>>(100);
	}

	/**  */
	template<typename T>
	static std::shared_ptr<T> CreateComponent()
	{
		const component_class_id = typeid(T).hash_code(); //  get the "unique id" of the given component class
		if (componentLists.find(component_class_id) == componentLists.end())
		{
			//  if there is no existing list for this component class, create one
			AddComponentList<T>(component_class_id);
		}

		//  create the component in the corresponding component list
		return std::static_pointer_cast<T>(componentLists[component_class_id]->createComponent());
	}

	/**  */
	template<typename T>
	static void DeleteComponent(const std::shared_ptr<T>& component)
	{
		const component_class_id = typeid(*component.get()).hash_code(); //  get the "unique id" of the class of the component to remove (can't get the id from 'T' cause it will just be the 'Component' class)
		if (componentLists.find(component_class_id) != componentLists.end())
		{
			//  if there is no existing list for this component class, it is impossible to delete the given component
			componentLists[component_class_id]->deleteComponent(component);
		}
	}


	/**  */
	static void UpdateComponents()
	{
	}

	/**  */
	static void ClearAllComponents()
	{
	}


private:
	static std::unordered_map<size_t, std::unique_ptr<ComponentList>> componentLists;
};

