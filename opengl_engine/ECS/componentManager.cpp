#include "componentManager.h"
#include "entity.h"

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
