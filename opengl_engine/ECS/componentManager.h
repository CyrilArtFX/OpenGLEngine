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
	ComponentList(size_t numComponentsPerSublist_)
	{
		numComponentsPerSublist = numComponentsPerSublist_;
	}


	/** Create a component and store it continuously with the other components of this class in the memory. */
	virtual std::shared_ptr<Component> createComponent() = 0;

	/** Remove a component from the list of this class of components. */
	virtual void deleteComponent(const std::shared_ptr<Component>& component) = 0;

	/** Update all components of the list of this class of components. */
	virtual void updateComponents() = 0;


	/** Get the maximum number of components of this class that can be stored in a single list. */
	size_t getNumComponentsPerList() { return numComponentsPerSublist; }

	/** Get every components of this class. */
	const std::vector<std::shared_ptr<Component>>& getAllComponents() const { return componentsShared; }

protected:
	std::vector<std::shared_ptr<Component>> componentsShared;
	size_t numComponentsPerSublist;
};


template<class T>
class ComponentListByClass : ComponentList
{
private:
	struct ComponentSubList
	{
		std::unique_ptr<T[]> components;
		std::unique_ptr<bool[]> memoryAllocated;
		size_t freeSlots = 0;
	};
	std::vector<ComponentSubList> componentSubLists;


public:
	ComponentListByClass(size_t numComponentsPerSublist_) : ComponentList(numComponentsPerSublist_)
	{
		ComponentSubList& sublist = componentSubLists.emplace_back();
		sublist.components = std::make_unique<T[]>(numComponentsPerSublist);
		sublist.memoryAllocated = std::make_unique<bool[]>(numComponentsPerSublist);
		sublist.freeSlots = numComponentsPerSublist;
	}

	/** Create a component and store it continuously with the other components of this class in the memory. */
	std::shared_ptr<Component> createComponent() override
	{
		//  step 1: get a sublist with a free slot available
		//  ------------------------------------------------
		int sublist_index = -1;
		const size_t num_sublists = componentSubLists.size();

		for (size_t sublists_iter = 0; sublists_iter < num_sublists; sublists_iter++)
		{
			if (componentSubLists[sublists_iter]->freeSlots > 0)
			{
				sublist_index = sublists_iter;
				break;
			}
		}

		//  step 1-B: create a new sublist if no free slot
		//  ----------------------------------------------
		if (sublist_index == -1)
		{
			ComponentSubList& sublist = componentSubLists.emplace_back();
			sublist.components = std::make_unique<T[]>(numComponentsPerSublist);
			sublist.memoryAllocated = std::make_unique<bool[]>(numComponentsPerSublist);
			sublist.freeSlots = numComponentsPerSublist;
			sublist_index = num_sublists; //  index of the new sublist will be the total number of sublists before its creation
		}

		ComponentSubList& sublist_creating_in = componentSubLists[sublist_index];


		//  step 2: create the component in the sublist
		//  -------------------------------------------
		int created_component_slot = -1;
		for (size_t slots_iter = 0; slots_iter < numComponentsPerSublist; slots_iter++)
		{
			if (sublist_creating_in.memoryAllocated[slots_iter]) continue;

			sublist_creating_in.memoryAllocated[slots_iter] = true;
			new (&sublist_creating_in.components[slots_iter]) T();
			sublist_creating_in.freeSlots--;
			created_component_slot = slots_iter;
			break;
		}

		if (created_component_slot == -1)
		{
			// TODO: assert error
		}

		// TODO: finish the component creation: call the register component function, give it to the shared list and bind the memory clear on the shared ptr destructor
	}

	/** Remove a component from the list of this class of components. */
	void deleteComponent(const std::shared_ptr<Component>& component) override
	{
		// TODO: create the function
	}

	/** Update all components of the list of this class of components. */
	void updateComponents() override
	{
		for (const std::shared_ptr<Component>& component : componentShared)
		{
			// TODO: call the function update on the component
		}
	}
};


class ComponentManager
{
public:
	/** Create a component list for this component class. Warning: This function does not check if a list for this class already exists. */
	template<typename T>
	static void AddComponentList(size_t classId)
	{
		componentLists[classId] = std::make_unique<ComponentListByClass<T>>(100);
	}

	/** Create a component and return a shared pointer to it. */
	template<typename T>
	static std::shared_ptr<T> CreateComponent()
	{
		const size_t component_class_id = typeid(T).hash_code(); //  get the "unique id" of the given component class
		if (componentLists.find(component_class_id) == componentLists.end())
		{
			//  if there is no existing list for this component class, create one
			AddComponentList<T>(component_class_id);
		}

		//  create the component in the corresponding component list
		return std::static_pointer_cast<T>(componentLists[component_class_id]->createComponent());
	}

	/** Delete a component. */
	template<typename T>
	static void DeleteComponent(const std::shared_ptr<T>& component)
	{
		const size_t component_class_id = typeid(*component.get()).hash_code(); //  get the "unique id" of the class of the component to remove (can't get the id from 'T' cause it will just be the 'Component' class)
		if (componentLists.find(component_class_id) != componentLists.end())
		{
			//  if there is no existing list for this component class, it is impossible to delete the given component
			componentLists[component_class_id]->deleteComponent(component);
		}
	}


	/** Update all active components. */
	static void UpdateComponents()
	{
		for (auto& component_list_pair : componentLists)
		{
			component_list_pair.second->updateComponents();
		}
	}

	/** Clear all components and all component lists. */
	static void ClearAllComponents()
	{
		// TODO: create the function
	}


private:
	static std::unordered_map<size_t, std::unique_ptr<ComponentList>> componentLists;
};

