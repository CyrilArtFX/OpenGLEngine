#include "rendererOpenGL.h"
#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>

#include <iostream>
#include <algorithm>


void RendererOpenGL::draw()
{
	//  clear with flat color
	glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (!currentCam) return;

	Matrix4 view = currentCam->getViewMatrix();
	Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(currentCam->getFov()), windowSize.x, windowSize.y, 0.1f, 100.0f);

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
		case ShaderType::Lit:
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
				case EPointLight:
					shader->setInt("nbPointLights", light_type_used++);
					break;
				case ESpotLight:
					shader->setInt("nbSpotLights", light_type_used++);
					break;
				}
			}

			shader->setVec3("viewPos", currentCam->getPosition());

			break;

		case ShaderType::Unlit:
			//  nothing else to do
			break;
		}
		
		//  loop through all materials that use the shader
		for (auto material : materials_by_shaders.second)
		{
			shader->setBool("beta_prevent_tex_scaling", false); //  should do a better thing for all beta parameters

			material->use();

			//  loop through all objects to draw all meshes that uses the material
			for (auto object : objects)
			{
				object->draw(material);
			}
		}
	}

	if (drawDebugMode)
	{
		Material& debug_collision_mat = AssetManager::GetMaterial("debug_collisions");
		Shader& debug_collision_shader = debug_collision_mat.getShader();
		debug_collision_shader.use();
		debug_collision_shader.setMatrix4("view", view.getAsFloatPtr());
		debug_collision_shader.setMatrix4("projection", projection.getAsFloatPtr());

		debug_collision_mat.use();

		Locator::getPhysics().DrawCollisionsDebug(debug_collision_mat);
	}
}



void RendererOpenGL::SetCamera(Camera* camera)
{
	currentCam = camera;
}

const Camera& RendererOpenGL::GetCamera() const
{
	return *currentCam;
}


void RendererOpenGL::SetClearColor(Color clearColor_)
{
	clearColor = clearColor_;
}

const Color RendererOpenGL::GetClearColor() const
{
	return clearColor;
}


void RendererOpenGL::AddMaterial(Material* material)
{
	materials[material->getShaderPtr()].push_back(material);
}

void RendererOpenGL::RemoveMaterial(Material* material)
{
	auto iter = std::find(materials[material->getShaderPtr()].begin(), materials[material->getShaderPtr()].end(), material);
	if (iter == materials[material->getShaderPtr()].end())
	{
		std::cout << "Renderer can't remove a material that doesn't exist.\n";
		return;
	}

	std::iter_swap(iter, materials[material->getShaderPtr()].end() - 1);
	materials[material->getShaderPtr()].pop_back();
}


void RendererOpenGL::AddLight(Light* light)
{
	lights[light->getLightType()].push_back(light);

	if (lights[light->getLightType()].size() > lightsLimits.at(light->getLightType()))
	{
		std::cout << "Renderer Warning : A light has been added but will not be used as the lit shader array has a too small size.\n";
	}
}

void RendererOpenGL::RemoveLight(Light* light)
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


void RendererOpenGL::AddObject(Object* object)
{
	objects.push_back(object);
}

void RendererOpenGL::RemoveObject(Object* object)
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



void RendererOpenGL::initializeRenderer(Color clearColor_, Vector2Int windowSize_)
{
	clearColor = clearColor_;
	windowSize = windowSize_;
}

void RendererOpenGL::setWindowSize(Vector2Int windowSize_)
{
	windowSize = windowSize_;
}