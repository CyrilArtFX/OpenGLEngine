#include "ExpositionScene.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/Lights/spotLightComponent.h>

#include <Inputs/input.h>
#include <GLFW/glfw3.h>


ExpositionScene::ExpositionScene()
{
}


void ExpositionScene::loadScene()
{
	Renderer& renderer = Locator::getRenderer();

	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  camera
	camera.setPosition(Vector3{ 0.0f, 0.0f, -3.0f });
	currentCam = &camera;
	renderer.SetCamera(&camera);


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


	//  audio
	//musicSource.playSound(AssetManager::GetSound("music"));
	//musicSource.setVolume(0.2f);

	Audio& audio = Locator::getAudio();
	audio.SetGlobalVolume(0.0f);


	//  physics
	Physics& physics = Locator::getPhysics();
	//BoxAABBColComp& sound_wall = static_cast<BoxAABBColComp&>(physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &soundWall, false, "nothing")));
	//sound_wall.setupAudioCollision(AssetManager::GetAudioCollisionType("default_audio_collision"));


	//  text
	sandboxText = new TextRendererComponent();
	sandboxText->setTextDatas("Welcome to the sandbox.\nTake a cookie.", AssetManager::GetFont("arial_64"), Vector2{ 0.0f, 0.0f }, Vector2::halfUnit, Vector2{ 120.0f, 35.0f }, Vector2{ 0.3f }, 0.0f, Color::cyan);

	//  sprite
	sandboxSprite = new SpriteRendererComponent();
	sandboxSprite->setSpriteDatas(AssetManager::GetTexture("smileyface_sprite"), Vector2{ 1.0f, 0.0f }, Vector2::halfUnit, Vector2{ -80.0f, 80.0f }, Vector2{ 0.25f }, 0.0f, Color::white);
}


void ExpositionScene::unloadScene()
{
}


void ExpositionScene::updateScene(float dt)
{
	//  move camera
	if (Input::IsKeyDown(GLFW_KEY_W))
		camera.freecamKeyboard(Forward, dt);

	if (Input::IsKeyDown(GLFW_KEY_S))
		camera.freecamKeyboard(Backward, dt);

	if (Input::IsKeyDown(GLFW_KEY_A))
		camera.freecamKeyboard(Left, dt);

	if (Input::IsKeyDown(GLFW_KEY_D))
		camera.freecamKeyboard(Right, dt);

	if (Input::IsKeyDown(GLFW_KEY_SPACE))
		camera.freecamKeyboard(Up, dt);

	if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
		camera.freecamKeyboard(Down, dt);

	Vector2 mouse_delta = Input::GetMouseDelta();
	camera.freecamMouseMovement(mouse_delta.x, mouse_delta.y);

	camera.freecamMouseScroll(Input::GetScrollOffset());



	flashlight->setPosition(camera.getPosition());
	flashlight->getComponentByClass<SpotLightComponent>()->setDirection(camera.getForward());

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
		SpotLightComponent* spotlight = flashlight->getComponentByClass<SpotLightComponent>();
		spotlight->setActive(!spotlight->isActive());
	}
}