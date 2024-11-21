#pragma once
#include <Core/scene.h>

#include <Assets/assetManager.h>
#include <Objects/object.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/directionalLight.h>
#include <Objects/Lights/pointLight.h>
#include <Objects/Lights/spotLight.h>

#include <Audio/audioSourceComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Sprite/spriteRendererComponent.h>


class ExpositionScene : public Scene
{
public:
	ExpositionScene();

	void updateScene(float dt) override;

protected:
	void loadScene() override;

	void unloadScene() override;

private:
	//  scene objects
	//-----------------

	Camera camera;

	Object cube1;
	Object cube2;
	Object cube3;
	Object backpack;
	Object lightCube1;
	Object lightCube2;
	Object soundWall;

	AudioSourceComponent musicSource{ &cube3, ChannelSpatialization::Channel3D };
	TextRendererComponent* sandboxText;
	SpriteRendererComponent* sandboxSprite;

	DirectionalLight sunLight;
	PointLight pointLight1;
	PointLight pointLight2;
	SpotLight flashLight;

	float time{ 0.0f };
};

