#include "ExpositionScene.h"
#include <ServiceLocator/locator.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/Lights/pointLightComponent.h>

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


	test_entity_1 = createEntity();
	test_entity_1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("container"));
	test_entity_1->setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	test_entity_1->setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(45.0f) });

	DirectionalLightComponent* dir_light = createEntity()->addComponentByClass<DirectionalLightComponent>();
	dir_light->setDirection(Vector3{ -0.4f, -0.5f, 1.0f });

	test_entity_2 = createEntity();
	test_entity_2->addComponentByClass<PointLightComponent>();
	test_entity_2->getComponentByClass<PointLightComponent>()->setColor(Color::cyan);
	test_entity_2->setPosition(Vector3{ 1.0f, 0.0f, 1.0f });


	//  objects
	cube1.addModel(&AssetManager::GetModel("container"));
	cube2.addModel(&AssetManager::GetModel("container"));
	cube3.addModel(&AssetManager::GetModel("container"));

	backpack.addModel(&AssetManager::GetModel("backpack"));

	lightCube1.addModel(&AssetManager::GetModel("light_cube"));
	lightCube2.addModel(&AssetManager::GetModel("light_cube"));

	soundWall.addModel(&AssetManager::GetModel("container"));

	cube1.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	cube1.setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(45.0f) });
	cube2.setPosition(Vector3{ 2.0f, 1.5f, 2.0f });
	cube3.setPosition(Vector3{ 3.5f, -1.0f, -3.0f });
	backpack.setPosition(Vector3{ 2.5f, 1.5f, -1.0f });
	backpack.setScale(0.002f);
	lightCube1.setPosition(Vector3{ 1.0f, 2.0f, 1.0f });
	lightCube1.setScale(0.2f);
	lightCube2.setPosition(Vector3{ 1.5f, 1.0f, -0.5f });
	lightCube2.setScale(0.2f);
	soundWall.setPosition(Vector3{ 2.0f, -1.0f, -3.0f });
	soundWall.setScale(Vector3{ 0.5f, 3.0f, 3.0f });


	//  audio
	musicSource.playSound(AssetManager::GetSound("music"));
	musicSource.setVolume(0.2f);

	Audio& audio = Locator::getAudio();
	audio.SetGlobalVolume(0.0f);


	//  physics
	Physics& physics = Locator::getPhysics();
	BoxAABBColComp& sound_wall = static_cast<BoxAABBColComp&>(physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &soundWall, false, "nothing")));
	//sound_wall.setupAudioCollision(AssetManager::GetAudioCollisionType("default_audio_collision"));


	//  lights
	sunLight.load(Color::white, Vector3{ -0.4f, -0.5f, 1.0f });
	pointLight1.load(Color::white, Vector3{ 1.0f, 2.0f, 1.0f });
	pointLight2.load(Color::white, Vector3{ 1.5f, 1.0f, -0.5f });
	flashLight.load(Color::white, Vector3::zero, Vector3::unitX);


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



	flashLight.setPosition(camera.getPosition());
	flashLight.setDirection(camera.getForward());

	//cube3.incrementRotation(Quaternion{ Vector3::unitX, Maths::toRadians(90.0f) * dt });

	time += dt;
	cube3.setPosition(Vector3{ 3.5f, -1.0f, -3.0f } + Vector3{ 0.0f, Maths::sin(time), Maths::cos(time) });

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

	if (Input::IsKeyPressed(GLFW_KEY_KP_1) && test_entity_1)
	{
		test_entity_1->destroyEntity();
		test_entity_1 = nullptr;
	}

	if (Input::IsKeyPressed(GLFW_KEY_KP_2) && test_entity_2)
	{
		test_entity_2->destroyEntity();
		test_entity_2 = nullptr;
	}

	if (Input::IsKeyPressed(GLFW_KEY_KP_0) && test_entity_2)
	{
		PointLightComponent* point_light = test_entity_2->getComponentByClass<PointLightComponent>();
		point_light->setActive(!point_light->isActive());
	}
}