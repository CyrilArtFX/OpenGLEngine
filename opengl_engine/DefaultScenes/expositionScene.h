#pragma once
#include <Core/scene.h>

#include <Rendering/shader.h>
#include <Rendering/vertexArray.h>
#include <Objects/object.h>

#include <Rendering/camera.h>
#include <Rendering/texture.h>

#include <Maths/Matrix4.h>
#include <Maths/Vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/DirectionalLight.h>
#include <Objects/Lights/PointLight.h>
#include <Objects/Lights/SpotLight.h>

#include <Materials/litMaterial.h>
#include <Materials/flatEmissiveMaterial.h>


class ExpositionScene : public Scene
{
public:
	ExpositionScene(std::weak_ptr<Renderer> renderer_);

	void load() override;
	void unload() override;

	void update(float dt) override;

private:
};

