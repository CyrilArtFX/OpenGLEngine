#pragma once
#include <Core/scene.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Audio/audioSourceComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>


class ExpositionScene : public Scene
{
public:
	ExpositionScene();

	void updateScene(float dt) override;

protected:
	void loadScene() override;

	void unloadScene() override;

private:
	Camera camera;

	Entity* movingCube{ nullptr };
	Entity* flashlight{ nullptr };

	//AudioSourceComponent musicSource{ &cube3, ChannelSpatialization::Channel3D };
	TextRendererComponent* sandboxText;
	SpriteRendererComponent* sandboxSprite;

	float time{ 0.0f };

	float textAnimationTimer{ -1.0f };
};

