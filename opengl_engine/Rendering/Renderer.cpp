#include "Renderer.h"
#include <iostream>


Renderer::Renderer(Color clearColor_) : clearColor(clearColor_)
{
}


void Renderer::draw(Matrix4 view, Matrix4 projection, Vector3 viewPos)
{
	//  clear with flat color
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//  draw objects depending of their materials
	for (auto mat : objects)
	{
		Shader& shader = mat.first.getShader();
		shader.use();
		shader.setMatrix4("view", view.getAsFloatPtr());
		shader.setMatrix4("projection", projection.getAsFloatPtr());

		MaterialType mat_type = mat.first.getMatType();
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
					light->use(shader);

					light_type_used++;
					if (light_type_used >= lights_limits.at(light_type))
					{
						break;
					}
				}
			}

			shader.setVec3("viewPos", viewPos);

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


void Renderer::addLight(std::weak_ptr<Light> light, LightType type)
{
	lights[type].push_back(light.lock());

	if (lights[type].size() > lights_limits.at(type))
	{
		std::cout << "Renderer Warning : A light has been added but will not be used as the lit shader array has a too small size.\n";
	}
}

void Renderer::addObject(std::weak_ptr<Object> object, Material& mat)
{
	objects[mat].push_back(object.lock());
}
