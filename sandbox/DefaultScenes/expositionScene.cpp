#include "ExpositionScene.h"
#include <ServiceLocator/locator.h>

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


	//  objects
	cube1.addModel(&AssetManager::GetModel("container"));
	cube2.addModel(&AssetManager::GetModel("container"));
	cube3.addModel(&AssetManager::GetModel("container"));

	backpack.addModel(&AssetManager::GetModel("backpack"));

	lightCube1.addModel(&AssetManager::GetModel("light_cube"));
	lightCube2.addModel(&AssetManager::GetModel("light_cube"));

	soundWall.addModel(&AssetManager::GetModel("container"));


	registerObject(&cube1);
	registerObject(&cube2);
	registerObject(&cube3);
	registerObject(&backpack);
	registerObject(&lightCube1);
	registerObject(&lightCube2);
	registerObject(&soundWall);

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

	registerLight(&sunLight);
	registerLight(&pointLight1);
	registerLight(&pointLight2);
	registerLight(&flashLight);
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
}