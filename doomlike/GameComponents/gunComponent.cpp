#include "gunComponent.h"
#include <ECS/entity.h>
#include <ServiceLocator/locator.h>
#include <Inputs/Input.h>
#include <Assets/assetManager.h>

#include <GameComponents/playerComponent.h>
#include <GameComponents/OverrideComponents/cameraLagComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>


void GunComponent::reset()
{
	if (!gunValid) return;

	// TODO: clear all active bullets

	reloadTimer = 0.0f;
	ammoCount = ammoMax;
	writeAmmoText();
}

void GunComponent::init()
{
	entity = getOwner();

	player = entity->getComponentByClass<PlayerComponent>();
	if (!player)
	{
		Locator::getLog().LogMessage_Category("Doomlike: A gun component was added on an entity that doesn't have a Player Component!", LogCategory::Warning);
		setUpdateActivated(false);
		return;
	}
	entity->onTransformUpdated.registerObserver(this, Bind_0(&GunComponent::onPlayerTransformUpdated));
	gunValid = true;

	gunModel = entity->addComponentByClass<ModelRendererComponent>();
	gunModel->setModel(&AssetManager::GetModel("gun"));
	gunModel->setIgnoreOwnerTransform(true);
	gunModel->offset.setScale(0.1f);

	ammoText = entity->addComponentByClass<TextRendererComponent>();
	ammoText->setTextDatas("", AssetManager::GetFont("arial_64"), Vector2::zero, Vector2::zero, Vector2{ 50.0f, 50.0f }, Vector2{ 0.6f }, 0.0f, Color::white);
	writeAmmoText();

	crosshairSprite = entity->addComponentByClass<SpriteRendererComponent>();
	crosshairSprite->setSpriteDatas(AssetManager::GetTexture("hud_crosshair"), Vector2::halfUnit, Vector2::halfUnit, Vector2::zero, Vector2{ 0.5f }, 0.0f, Color::white);
}

void GunComponent::exit()
{
	entity->onTransformUpdated.unregisterObserver(this);

	//  release shared pointers
	player = nullptr;
	gunModel = nullptr;
	ammoText = nullptr;
	crosshairSprite = nullptr;
}

void GunComponent::update(float deltaTime)
{
	if (!gunValid) return;

	// shoot
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT) && ammoCount > 0 && reloadTimer == 0.0f)
	{
		// TODO: shoot bullet
		Locator::getLog().LogMessageToScreen("Gun component: Shoot!", Color::cyan, 5.0f);

		//  play shoot sound
		Locator::getAudio().InstantPlaySound2D(AssetManager::GetSound("shoot"), 0.15f);

		ammoCount--;
		writeAmmoText();
	}


	//  reload
	if (Input::IsKeyPressed(GLFW_KEY_R) && ammoCount < ammoMax && reloadTimer == 0.0f)
	{
		reloadTimer = reloadDuration;
	}

	if (reloadTimer > 0.0f)
	{
		reloadTimer -= deltaTime;
		if (reloadTimer <= 0.0f)
		{
			reloadTimer = 0.0f;
			ammoCount = ammoMax;
			writeAmmoText();
		}
	}
}

void GunComponent::onPlayerTransformUpdated()
{
	if (!gunValid) return;

	Transform& gun_offset = gunModel->offset;
	CameraLagComponent& player_camera = *player->camera;
	gun_offset.setPosition(player_camera.getCamPosition());
	gun_offset.setRotation(Quaternion::concatenate(player_camera.getRotOffset(), entity->getRotation()));
	gun_offset.incrementRotation(Quaternion{ gun_offset.getUp(), Maths::toRadians(180.0f) }); //  gun is rotated backward by default
	gun_offset.addPositionRotated(Vector3{ 0.1f, -0.1f, -0.2f }); //  gun offset of camera
	gun_offset.incrementRotation(Quaternion{ gun_offset.getRight(), Maths::toRadians(reloadTimer * 720.0f) });
}

void GunComponent::writeAmmoText()
{
	if (!gunValid) return;

	ammoText->setText("Ammo: " + std::to_string(ammoCount) + "/" + std::to_string(ammoMax));
}
