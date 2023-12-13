#include "renderer.h"
#include <iostream>
#include <algorithm>


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

	//  loop through all shaders
	for (auto materials_by_shaders : materials)
	{
		//  retrieve the shader
		Shader* shader = materials_by_shaders.first;

		if (!shader->isLoaded()) continue;

		//  activate the shader and set the primary uniforms
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
					if (!light->isLoaded()) continue;

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
		
		//  loop through all materials that use the shader
		for (auto material : materials_by_shaders.second)
		{
			material->use();

			//  loop through all objects to draw all meshes that uses the material
			for (auto object : objects)
			{
				object->draw(material);
			}
		}
	}
}


void Renderer::setCamera(std::weak_ptr<Camera> camera)
{
	currentCam = camera.lock();
}

void Renderer::addMaterial(Material* material)
{
	materials[material->getShaderPtr()].push_back(material);
}

void Renderer::addLight(Light* light)
{
	lights[light->getLightType()].push_back(light);

	if (lights[light->getLightType()].size() > lightsLimits.at(light->getLightType()))
	{
		std::cout << "Renderer Warning : A light has been added but will not be used as the lit shader array has a too small size.\n";
	}
}

void Renderer::addObject(Object* object)
{
	objects.push_back(object);
}

void Renderer::removeLight(Light* light)
{
	auto iter = std::find(lights[light->getLightType()].begin(), lights[light->getLightType()].end(), light);
	if (iter == lights[light->getLightType()].end())
	{
		std::cout << "Renderer can't remove a light that doesn't exist.\n";
		return;
	}

	std::iter_swap(iter, lights[light->getLightType()].end() - 1);
	lights[light->getLightType()].pop_back();
}

void Renderer::removeObject(Object* object)
{
	auto iter = std::find(objects.begin(), objects.end(), object);
	if (iter == objects.end())
	{
		std::cout << "Renderer can't remove an object that doesn't exist.\n";
		return;
	}

	std::iter_swap(iter, objects.end() - 1);
	objects.pop_back();
}
