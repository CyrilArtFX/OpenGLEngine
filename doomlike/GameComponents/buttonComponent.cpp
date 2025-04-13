#include "buttonComponent.h"
#include <ECS/entity.h>
#include <Assets/assetManager.h>
#include <Inputs/Input.h>

#include <Rendering/modelRendererComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>


void ButtonComponent::init()
{
	//  reset the value in case this component was used before (the component manager is a memory pool)
	frameOutsideCount = 0;
	used = false;


	//  initialize button
	buttonModel = getOwner()->addComponentByClass<ModelRendererComponent>();
	buttonModel->setModel(&AssetManager::GetModel("button"));
	buttonModel->offset.setScale(0.025f);
	buttonModel->offset.setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(-90.0f) });
	buttonModel->offset.setPosition(Vector3{ 0.0f, 0.6f, 0.0f });

	triggerBox = getOwner()->addComponentByClass<BoxAABBColComp>();
	triggerBox->setBox(Box{ Vector3{-1.5f, 0.5f, 0.0f}, Vector3{0.5f, 0.5f, 0.5f} });
	triggerBox->setCollisionChannel("trigger_zone");
	triggerBox->setCollisionType(CollisionType::Trigger);
	triggerBox->onTriggerEnter.registerObserver(this, Bind_1(&ButtonComponent::onBodyIntersect));

	text = getOwner()->addComponentByClass<TextRendererComponent>();
	text->setTextDatas(textContent, AssetManager::GetFont("arial_64"), Vector2::halfUnit, Vector2{ 0.5f, 0.0f }, Vector2{ 0.0f, 150.0f }, Vector2{ 0.7f, 0.7f }, 0.0f, Color::white);
	text->setEnabled(false);
}

void ButtonComponent::exit()
{
	triggerBox->onTriggerEnter.unregisterObserver(this);
}

void ButtonComponent::update(float deltaTime)
{
	if (used) return;

	if (frameOutsideCount <= 0) return;
	
	frameOutsideCount--;
	if (frameOutsideCount > 0)
	{
		text->setEnabled(true);
		
		if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			used = true;
			text->setEnabled(false);
		}
	}
	else
	{
		text->setEnabled(false);
	}
}

void ButtonComponent::onBodyIntersect(RigidbodyComponent& other)
{
	frameOutsideCount = 2;
}
