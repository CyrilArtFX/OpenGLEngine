#include "playerComponent.h"
#include <ECS/entity.h>
#include <ServiceLocator/locator.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Inputs/Input.h>
#include <Assets/assetManager.h>

#include <GameplayStatics/gameplayStatics.h>
#include <doomlikeGame.h>

#include <Rendering/cameraComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <Audio/audioSourceComponent.h>


void PlayerComponent::setupPlayer(float camHeight_, float moveSpeed_, float jumpForce_, float stepHeight_)
{
	camHeight = camHeight_;
	moveSpeed = moveSpeed_;
	jumpForce = jumpForce_;

	camera->setOffset(Vector3{ 0.0f, camHeight, 0.0f });
	camera->setAsActiveCamera();

	collision->setBox(Box{ Vector3{0.0f, (camHeight / 2.0f) + 0.1f, 0.0f}, Vector3{0.3f, (camHeight / 2.0f) + 0.1f, 0.3f} });
	collision->setCollisionChannel("player");
	collision->useOwnerScaleForBoxSize = false;

	rigidbody->setStepHeight(stepHeight_);
	rigidbody->setPhysicsActivated(true);
	rigidbody->setUseGravity(true);
	rigidbody->setTestChannels(CollisionChannels::GetRegisteredTestChannel("PlayerEntity"));

	feetSoundSource->setSpatialization(ChannelSpatialization::Channel3D);
	feetSoundSource->setOffset(Vector3{ 0.0f, -1.1f, 0.0f });
	feetSoundSource->setVolume(0.2f);

	rigidbody->onCollisionRepulsed.registerObserver(this, Bind_1(&PlayerComponent::onCollision));

	setUpdateActivated(true);
}

void PlayerComponent::respawn(const Transform& respawnTransform)
{
	rigidbody->setVelocity(Vector3::zero);
	rigidbody->setGravityVelocity(Vector3::zero);

	entity->pasteTransform(respawnTransform);

	camera->setPitch(0.0f);
}

Vector3 PlayerComponent::getCamPosition() const
{
	return camera->getCamPosition();
}

void PlayerComponent::onCollision(const CollisionResponse& collisionResponse)
{
	if (collisionResponse.impactNormal == Vector3::negUnitY)
	{
		rigidbody->setGravityVelocity(Vector3::zero); //  cancel the jump velocity if hit a roof
	}
}


void PlayerComponent::init()
{
	entity = getOwner();

	camera = entity->addComponentByClass<CameraComponent>();
	
	collision = entity->addComponentByClass<BoxAABBColComp>();
	rigidbody = entity->addComponentByClass<RigidbodyComponent>();
	rigidbody->associateCollision(collision);

	feetSoundSource = entity->addComponentByClass<AudioSourceComponent>();

	setUpdateActivated(false); //  it will be activated once setupPlayer has been called
}

void PlayerComponent::update(float deltaTime)
{
	//  move player
	Vector3 velocity_xz = Vector3::zero;

	if (Input::IsKeyDown(GLFW_KEY_W))
		velocity_xz += entity->getForward() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_S))
		velocity_xz -= entity->getForward() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_A))
		velocity_xz += entity->getRight() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_D))
		velocity_xz -= entity->getRight() * moveSpeed;

	//  clamp the velocity to max movement speed
	velocity_xz.clampMagnitude(moveSpeed);

	//  apply velocity to rigidbody
	rigidbody->setVelocity(velocity_xz);


	//  player and camera rotation
	Vector2 mouse_delta = Input::GetMouseDelta() * camSensitivity;
	entity->incrementRotation(Quaternion{ Vector3::unitY, -mouse_delta.x * 0.01f });
	camera->setPitch(Maths::clamp(camera->getPitch() + mouse_delta.y, -89.0f, 89.0f));


	//  jump
	if (Input::IsKeyPressed(GLFW_KEY_SPACE) && rigidbody->isOnGround())
	{
		rigidbody->addGravityVelocity(Vector3::unitY * jumpForce);
	}


	//  shoot raycast
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		Vector3 raycast_start = camera->getCamPosition();
		Vector3 raycast_end = raycast_start + camera->getCamForward() * 5.0f;

		Physics& physics = Locator::getPhysics();
		//physics.LineRaycast(raycast_start, raycast_end, CollisionChannels::GetRegisteredTestChannel("PlayerEntity"));
		physics.AABBSweepRaycast(raycast_start, raycast_end, Box{ Vector3::zero, Vector3{0.1f, 0.1f, 0.1f} }, CollisionChannels::GetRegisteredTestChannel("PlayerEntity"));
	}


	//  feet sound
	feetSoundTimer -= deltaTime;
	if (rigidbody->isOnGround())
	{
		if (!(velocity_xz == Vector3::zero) || !onGroundLastFrame)
		{
			if (feetSoundTimer <= 0.0f)
			{
				feetSoundSource->playSound(AssetManager::GetSound(feetSoundAlternance ? "feet1" : "feet2"));

				feetSoundAlternance = !feetSoundAlternance;
				feetSoundTimer = 0.5f;
			}
		}
	}


	//  camera lag
	// TODO: camera lag can't be done anymore since the camera component works with an offset from its entity position
	// and what's bothering us is the player movement that is to violent.
	// We need to create an override of the camera component for lag, or change the current one with a boolean, idk


	//  death by void
	if (entity->getPosition().y < -50.0f)
	{
		Locator::getLog().LogMessageToScreen("Doomlike: Player die by falling.", Color::white, 5.0f);
		static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->restartLevel();
	}


	onGroundLastFrame = rigidbody->isOnGround();
}