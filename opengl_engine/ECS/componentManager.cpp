#include "componentManager.h"
#include "entity.h"

//  static variables need to be defined in a cpp file to exist for the compiler
std::unordered_map<size_t, std::unique_ptr<ComponentList>> ComponentManager::componentLists;
std::unordered_map<size_t, ComponentClassData> ComponentManager::componentClassDatas;


void ComponentList::initializeComponent(const std::shared_ptr<Component>& component, Entity* componentOwner)
{
	component->setOwner(componentOwner);
	component->init();
	component->registerComponent();
}

void ComponentList::unregisterComponent(const std::shared_ptr<Component>& component)
{
	component->unregisterComponent();
}


ComponentClassData ComponentManager::GetComponentClassData(size_t classId)
{
	if (componentClassDatas.find(classId) == componentClassDatas.end())
	{
		return ComponentClassData();
	}

	return componentClassDatas[classId];
}
