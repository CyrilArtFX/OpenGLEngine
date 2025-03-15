#include "componentManager.h"
#include "entity.h"

//  the static variable need to be defined in a cpp file to exist for the compiler
std::unordered_map<size_t, std::unique_ptr<ComponentList>> ComponentManager::componentLists;


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
