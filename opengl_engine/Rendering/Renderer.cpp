#include "Renderer.h"
#include <iostream>


Renderer::Renderer(Color clearColor_, const Window& window) : clearColor(clearColor_), windowRef(window)
{
}


void Renderer::draw()
{
	Matrix4 view = currentCam->GetViewMatrix();
	Matrix4 projection = Matrix4::createPerspectiveFOV(Maths::toRadians(currentCam->getFov()), windowRef.getWidth(), windowRef.getHeigth(), 0.1f, 100.0f);

	//  clear with flat color
	glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//  draw objects depending of their materials
	for (auto mat : objects)
	{
		Shader& shader = mat.first->getShader();
		shader.use();
		shader.setMatrix4("view", view.getAsFloatPtr());
		shader.setMatrix4("projection", projection.getAsFloatPtr());

		MaterialType mat_type = mat.first->getMatType();
		switch (mat_type) //  feels a bit hardcoded, should be cool to find a better way to do this
		{
		case Lit:
			//  use lights
			for (auto light_t : lights)
			{
				LightType light_type = light_t.first;

				int light_type_used = 0;
				for (auto light : light_t.second)
				{
					light->use(shader, light_type_used);

					light_type_used++;
					if (light_type_used >= lights_limits.at(light_type))
					{
						break;
					}
				}

				switch (light_type)
				{
				case Point:
					shader.setInt("nbPointLights", light_type_used++);
				break;
				case Spot:
					shader.setInt("nbSpotLights", light_type_used++);
				break;
				}
			}

			shader.setVec3("viewPos", currentCam->getPosition());

		break;

		case Unlit:
			//  nothing else to do
		break;
		}
			
		for (auto object : mat.second)
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

	if (lights[type].size() > lights_limits.at(type))
	{
		std::cout << "Renderer Warning : A light has been added but will not be used as the lit shader array has a too small size.\n";
	}
}

void Renderer::addObject(std::weak_ptr<Object> object, std::shared_ptr<Material> mat)
{
	objects[mat].push_back(object.lock());
}
