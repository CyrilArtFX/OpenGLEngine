#include "Player.h"

#include <Inputs/input.h>
#include <Maths/maths.h>
#include <Physics/physics.h>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>


Player::Player() :
	rigidbody(&Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box::one, this, false), true, false)))
{
	rigidbody->onRigidbodyDelete.registerObserver(this, Bind_0(&Player::onRigidbodyDeleted));
}

void Player::setup(float height, float speed, Renderer* renderer)
{
	camHeight = height;
	moveSpeed = speed;
	rendererRef = renderer;

	setPosition(0.0f, 0.0f, 0.0f);
	camera.setPosition(Vector3{ 0.0f, camHeight, 0.0f });
	camera.setSensitivity(0.08f);

	BoxAABBColComp& collision = static_cast<BoxAABBColComp&>(rigidbody->getAssociatedCollisionNonConst());
	collision.changeBox(Box{ Vector3{0.0f, camHeight / 2.0f, 0.0f}, Vector3{0.3f, camHeight / 2.0f, 0.3f} });
	rigidbody->setPhysicsActivated(true);
	rigidbody->setUseGravity(true);
}


void Player::update(float dt)
{
	//  move player
	Vector3 velocity = Vector3::zero;

	if (Input::IsKeyDown(GLFW_KEY_W))
		velocity += camera.getFlatFront() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_S))
		velocity -= camera.getFlatFront() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_A))
		velocity += camera.getRight() * moveSpeed;

	if (Input::IsKeyDown(GLFW_KEY_D))
		velocity -= camera.getRight() * moveSpeed;


	//  jump
	RaycastHitInfos hit_infos;
	onGround = Physics::RaycastLine(getPosition(), getPosition() - Vector3{ 0.0f, 0.01f, 0.0f }, hit_infos, 0.0f);

	if (Input::IsKeyPressed(GLFW_KEY_SPACE) && onGround)
	{
		setPosition(getPosition() + Vector3::unitY * 0.01f);
		velocity += Vector3::unitY * 500.0f;
	}


	//  apply velocity to rigidbody
	rigidbody->setVelocity(velocity);


	//  shoot
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (rendererRef)
		{
			Quaternion bullet_rotation = camera.getRotation();
			bullet_rotation = Quaternion::concatenate(bullet_rotation, Quaternion{ camera.getUp(), Maths::toRadians(90.0f) });
			bullets.push_back(std::make_unique<Bullet>(camera.getPosition(), bullet_rotation, camera.getForward(), shootVelocity, bulletLifeTime, rendererRef));
		}
		else
		{
			std::cout << "Doomlike game error : Player has not his renderer ref setup !\n";
		}
	}


	//  shoot raycast
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		Vector3 raycast_start = camera.getPosition();
		Vector3 raycast_end = raycast_start + camera.getForward() * 5.0f;

		Physics::RaycastLine(raycast_start, raycast_end);
	}


	Vector2 mouse_delta = Input::GetMouseDelta(); 
	camera.freecamMouseMovement(mouse_delta.x, mouse_delta.y); 

	camera.setPosition(getPosition() + Vector3{0.0f, camHeight, 0.0f});


	//  shoot
	for (auto& bullet : bullets)
	{
		bullet->update(dt);
	}
	
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isLTOver())
		{
			bullets[i]->destroy();

			std::iter_swap(bullets.begin() + i, bullets.end() - 1);
			bullets.pop_back();

			break; //  assume that we can't create 2 bullets on the same frame so 2 bullets cannot be destroyed by time out on the same frame
		}
	}
}

void Player::unload()
{
	for (auto& bullet : bullets)
	{
		bullet->destroy();
	}
	bullets.clear();
}

void Player::respawn(PlayerSpawnPoint& spawnPoint)
{
	unload();

	setPosition(spawnPoint.spawnPosition);
	//setRotation(spawnPoint.spawnRotation);

	camera.setPosition(spawnPoint.spawnPosition + Vector3{ 0.0f, camHeight, 0.0f });
	//camera.setRotByQuaternion(spawnPoint.spawnRotation);
}

void Player::onRigidbodyDeleted()
{
	rigidbody = nullptr;
}
