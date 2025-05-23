#include "ExpositionScene.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/Lights/spotLightComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>

#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <Physics/ObjectChannels/collisionChannels.h>

#include <Inputs/input.h>


void ExpositionScene::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  player
	player = createEntity();
	camera = player->addComponentByClass<CameraComponent>();
	camera->setAsActiveCamera();
	player->setPosition(Vector3{ 0.0f, 0.0f, -3.0f });
	camera->setYaw(-90.0f);


	//  entities
	Entity* cube_1 = createEntity();
	cube_1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));
	Entity* cube_2 = createEntity();
	cube_2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));
	movingCube = createEntity();
	movingCube->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));
	Entity* backpack = createEntity();
	backpack->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("backpack"));

	Entity* light_cube_1 = createEntity();
	light_cube_1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("light_cube_cyan"));
	light_cube_1->addComponentByClass<PointLightComponent>()->setColor(Color::cyan);
	Entity* light_cube_2 = createEntity();
	light_cube_2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("light_cube_white"));
	light_cube_2->addComponentByClass<PointLightComponent>();
	flashlight = createEntity();
	flashlight->addComponentByClass<SpotLightComponent>();

	Entity* collision_cube = createEntity();
	collision_cube->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));
	physicsCube = createEntity();
	physicsCube->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));

	cube_1->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	cube_1->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(45.0f) });
	cube_2->setPosition(Vector3{ 2.0f, 1.5f, 2.0f });
	movingCube->setPosition(Vector3{ 3.5f, -1.0f, -3.0f });
	backpack->setPosition(Vector3{ 2.5f, 1.5f, -1.0f });
	backpack->setScale(0.002f);

	light_cube_1->setPosition(Vector3{ 1.0f, 2.0f, 1.0f });
	light_cube_1->setScale(0.2f);
	light_cube_2->setPosition(Vector3{ 1.5f, 1.0f, -0.5f });
	light_cube_2->setScale(0.2f);

	collision_cube->setPosition(Vector3{ -5.0f, 0.0f, 0.0f });
	collision_cube->setScale(Vector3{ 2.0f, 0.2f, 2.0f });
	physicsCube->setPosition(Vector3{ -5.0f, 5.0f, 0.0f });
	physicsCube->setScale(0.3f);


	//  audio
	musicAudioSource = movingCube->addComponentByClass<AudioSourceComponent>();
	musicAudioSource->playSound(AssetManager::GetSound("music"));
	musicAudioSource->setVolume(0.2f);

	Audio& audio = Locator::getAudio();
	audio.SetGlobalVolume(0.0f);


	//  physics
	Physics& physics = Locator::getPhysics();
	//BoxAABBColComp& sound_wall = static_cast<BoxAABBColComp&>(physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &soundWall, false, "nothing")));
	//sound_wall.setupAudioCollision(AssetManager::GetAudioCollisionType("default_audio_collision"));
	collision_cube->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("test_ground");
	physicsCube->addComponentByClass<BoxAABBColComp>()->setBox(Box::one);
	std::shared_ptr<RigidbodyComponent> rigidbody = physicsCube->addComponentByClass<RigidbodyComponent>();
	rigidbody->associateCollision(physicsCube->getComponentByClass<BoxAABBColComp>());
	rigidbody->setPhysicsActivated(true);
	rigidbody->setUseGravity(true);
	rigidbody->setTestChannels({ "test_ground" });


	//  hud (text & sprite)
	Entity* hud_entity = createEntity();
	sandboxText = hud_entity->addComponentByClass<TextRendererComponent>();
	sandboxText->setTextDatas("Welcome to the sandbox.\nTake a cookie.", AssetManager::GetFont("arial_64"), Vector2{ 0.0f, 0.0f }, Vector2::halfUnit, Vector2{ 120.0f, 35.0f }, Vector2{ 0.3f }, 0.0f, Color::cyan);

	//  sprite
	sandboxSprite = hud_entity->addComponentByClass<SpriteRendererComponent>();
	sandboxSprite->setSpriteDatas(AssetManager::GetTexture("smileyface_sprite"), Vector2{ 1.0f, 0.0f }, Vector2::halfUnit, Vector2{ -80.0f, 80.0f }, Vector2{ 0.25f }, 0.0f, Color::white);
}


void ExpositionScene::unloadScene()
{
}


void ExpositionScene::updateScene(float dt)
{
	//  move camera
	if (Input::IsKeyDown(GLFW_KEY_W))
		player->addPosition(camera->getCamForward() * playerCamSpeed * dt);

	if (Input::IsKeyDown(GLFW_KEY_S))
		player->addPosition(-camera->getCamForward() * playerCamSpeed * dt);

	if (Input::IsKeyDown(GLFW_KEY_A))
		player->addPosition(camera->getCamRight() * playerCamSpeed * dt);

	if (Input::IsKeyDown(GLFW_KEY_D))
		player->addPosition(-camera->getCamRight() * playerCamSpeed * dt);

	if (Input::IsKeyDown(GLFW_KEY_SPACE))
		player->addPosition(Vector3::unitY * playerCamSpeed * dt);

	if (Input::IsKeyDown(GLFW_KEY_C))
		player->addPosition(Vector3::negUnitY * playerCamSpeed * dt);

	Vector2 mouse_delta = Input::GetMouseDelta() * playerCamSensitivity;
	//player->incrementRotation(Quaternion{ Vector3::unitY, -mouse_delta.x * 0.01f }); //  it works, keeping it here for later
	camera->addYaw(-mouse_delta.x);
	camera->setPitch(Maths::clamp(camera->getPitch() + mouse_delta.y, -89.0f, 89.0f));


	flashlight->setPosition(camera->getCamPosition());
	flashlight->getComponentByClass<SpotLightComponent>()->setDirection(camera->getCamForward());

	//movingCube->incrementRotation(Quaternion{ Vector3::unitX, Maths::toRadians(90.0f) * dt });

	time += dt;
	movingCube->setPosition(Vector3{ 3.5f, -1.0f, -3.0f } + Vector3{ 0.0f, Maths::sin(time), Maths::cos(time) });

	sandboxSprite->setRotAngle(Maths::fmod(sandboxSprite->getRotAngle() + dt * 180.0f, 360.0f));

	if (Input::IsKeyPressed(GLFW_KEY_E))
	{
		textAnimationTimer = 0.0f;
	}

	if (textAnimationTimer >= 0.0f)
	{
		textAnimationTimer += dt;

		sandboxText->setRotAngle(textAnimationTimer * 180.0f);

		if (textAnimationTimer > 4.0f)
		{
			textAnimationTimer = -1.0f;
			sandboxText->setRotAngle(0.0f);
		}
	}

	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		std::shared_ptr<SpotLightComponent> spotlight = flashlight->getComponentByClass<SpotLightComponent>();
		spotlight->setActive(!spotlight->isActive());
	}

	if (Input::IsKeyPressed(GLFW_KEY_Q))
	{
		physicsCube->setPosition(Vector3{ -5.0f, 5.0f, 0.0f });
	}
}