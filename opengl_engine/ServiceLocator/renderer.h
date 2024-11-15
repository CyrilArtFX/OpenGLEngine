#pragma once

class Camera;
class Color;
class Material;
class Light;
class Object;
class TextRendererComponent;


/**
* The Renderer Service class (the virtual class provided by the Locator).
*/
class Renderer
{
public:
	virtual ~Renderer() {}


	/**
	* Set the new camera that will be used.
	* @param	camera		The new camera to use.
	*/
	virtual void SetCamera(Camera* camera) = 0;

	/**
	* Retrieve the currently used camera.
	* @return			The currently used camera.
	*/
	virtual const Camera& GetCamera() const = 0;


	/**
	* Set the new clear color that will be used.
	* @param	clearColor		The new clear color to use.
	*/
	virtual void SetClearColor(Color clearColor) = 0;

	/**
	* Retrieve the currently used clear color.
	* @return			The currently used clear color.
	*/
	virtual const Color GetClearColor() const = 0;


	/**
	* Register a material to the renderer.
	* @param	material	The material to register.
	*/
	virtual void AddMaterial(Material* material) = 0;

	/**
	* Unregister a material from the renderer.
	* @param	material	The material to unregister.
	*/
	virtual void RemoveMaterial(Material* material) = 0;


	/**
	* Register a light to the renderer.
	* @param	light	The light to register.
	*/
	virtual void AddLight(Light* light) = 0;

	/**
	* Unregister a light from the renderer.
	* @param	light	The light to unregister.
	*/
	virtual void RemoveLight(Light* light) = 0;


	/**
	* Register an object to the renderer.
	* @param	object	The object to register.
	*/
	virtual void AddObject(Object* object) = 0;

	/**
	* Unregister an object from the renderer.
	* @param	object	The object to unregister.
	*/
	virtual void RemoveObject(Object* object) = 0;


	/**
	* Register a text to the renderer.
	* @param	text	The text to register.
	*/
	virtual void AddText(TextRendererComponent* text) = 0;

	/**
	* Unregister a text from the renderer.
	* @param	text	The text to unregister.
	*/
	virtual void RemoveText(TextRendererComponent* text) = 0;
};