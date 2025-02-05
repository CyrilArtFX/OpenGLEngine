#pragma once

class Camera;
struct Color;
class Material;
class LightComponent;
class ModelRendererComponent;
class TextRendererComponent;
class SpriteRendererComponent;


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
	* Register a light component to the renderer.
	* @param	light	The light component to register.
	*/
	virtual void AddLight(LightComponent* light) = 0;

	/**
	* Unregister a light component from the renderer.
	* @param	light	The light component to unregister.
	*/
	virtual void RemoveLight(LightComponent* light) = 0;


	/**
	* Register a model renderer component to the renderer.
	* @param	modelRenderer	The model renderer component to register.
	*/
	virtual void AddModelRenderer(ModelRendererComponent* modelRenderer) = 0;

	/**
	* Unregister a model renderer component from the renderer.
	* @param	modelRenderer	The model renderer component to unregister.
	*/
	virtual void RemoveModelRenderer(ModelRendererComponent* modelRenderer) = 0;


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


	/**
	* Register a sprite to the renderer.
	* @param	sprite	The sprite to register.
	*/
	virtual void AddSprite(SpriteRendererComponent* sprite) = 0;

	/**
	* Unregister a sprite from the renderer.
	* @param	sprite	The sprite to unregister.
	*/
	virtual void RemoveSprite(SpriteRendererComponent* sprite) = 0;
};