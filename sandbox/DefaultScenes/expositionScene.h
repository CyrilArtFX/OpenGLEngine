#pragma once
#include <Core/scene.h>

#include <Rendering/cameraComponent.h>
#include <Audio/audioSourceComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <memory>


class ExpositionScene : public Scene
{
public:
	void updateScene(float dt) override;

protected:
	void loadScene() override;

	void unloadScene() override;

private:
	Entity* player{ nullptr };
	std::shared_ptr<CameraComponent> camera;

	Entity* movingCube{ nullptr };
	Entity* flashlight{ nullptr };
	Entity* physicsCube{ nullptr };

	std::shared_ptr<AudioSourceComponent> musicAudioSource;
	std::shared_ptr<TextRendererComponent> sandboxText;
	std::shared_ptr<SpriteRendererComponent> sandboxSprite;

	float playerCamSpeed{ 4.0f };
	float playerCamSensitivity{ 0.1f };

	float time{ 0.0f };

	float textAnimationTimer{ -1.0f };
};

