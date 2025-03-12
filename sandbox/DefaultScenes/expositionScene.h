#pragma once
#include <Core/scene.h>

#include <Rendering/cameraComponent.h>
#include <Audio/audioSourceComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>

#include <Maths/vector3.h>
#include <Utils/color.h>


class ExpositionScene : public Scene
{
public:
	ExpositionScene();

	void updateScene(float dt) override;

protected:
	void loadScene() override;

	void unloadScene() override;

private:
	Entity* player{ nullptr };
	CameraComponent* camera{ nullptr };

	Entity* movingCube{ nullptr };
	Entity* flashlight{ nullptr };
	Entity* physicsCube{ nullptr };

	AudioSourceComponent* musicAudioSource{ nullptr };
	TextRendererComponent* sandboxText{ nullptr };
	SpriteRendererComponent* sandboxSprite{ nullptr };

	float playerCamSpeed{ 4.0f };
	float playerCamSensitivity{ 0.1f };

	float time{ 0.0f };

	float textAnimationTimer{ -1.0f };
};

