#include "renderer.h"
#include <iostream>


Renderer::Renderer(Color clearColor_, const Window& window) : clearColor(clearColor_), windowRef(window)
{
}


void Renderer::draw()
{
	//  clear with flat color
	glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (!currentCam) return;

	Matrix4 view = currentCam->getViewMatrix();
	Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(currentCam->getFov()), windowRef.getWidth(), windowRef.getHeigth(), 0.1f, 100.0f);

	//  draw objects depending of their materials
	for (auto objs_by_shader : objects)
	{
		std::shared_ptr<Shader> shader = objs_by_shader.first;
		shader->use();
		shader->setMatrix4("view", view.getAsFloatPtr());
		shader->setMatrix4("projection", projection.getAsFloatPtr());

		ShaderType shader_type = shader->getShaderType();
		switch (shader_type) //  feels a bit hardcoded, should be cool to find a better way to do this
		{
		case Lit:
			//  use lights
			for (auto light_t : lights)
			{
				LightType light_type = light_t.first;

				int light_type_used = 0;
				for (auto light : light_t.second)
				{
					light->use(*shader, light_type_used);

					light_type_used++;
					if (light_type_used >= lightsLimits.at(light_type))
					{
						break;
					}
				}

				switch (light_type)
				{
				case Point:
					shader->setInt("nbPointLights", light_type_used++);
				break;
				case Spot:
					shader->setInt("nbSpotLights", light_type_used++);
				break;
				}
			}

			shader->setVec3("viewPos", currentCam->getPosition());

		break;

		case Unlit:
			//  nothing else to do
		break;
		}
			
		for (auto object : objs_by_shader.second)
		{
			object->draw();
		}
	}
}


void Renderer::setCamera(std::weak_ptr<Camera> camera)
{
	currentCam = camera.lock();
}

void Renderer::addLight(std::weak_ptr<Light> light, LightType type)
{
	lights[type].push_back(light.lock());

	if (lights[type].size() > lightsLimits.at(type))
	{
		std::cout << "Renderer Warning : A light has been added but will not be used as the lit shader array has a too small size.\n";
	}
}

void Renderer::addObject(std::weak_ptr<Object> object, std::shared_ptr<Shader> shader)
{
	objects[shader].push_back(object.lock());
}
