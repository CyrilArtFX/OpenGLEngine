#pragma once
#include <memory>

class CameraComponent;
struct Color;
class Material;
class LightComponent;
class ModelRendererComponent;
class TextRendererComponent;
class SpriteRendererComponent;
struct Vector3;
class Box;


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
	virtual void SetCamera(std::weak_ptr<CameraComponent> camera) = 0;

	/**
	* Retrieve the currently used camera.
	* @return			The currently used camera.
	*/
	virtual const std::shared_ptr<CameraComponent> GetCamera() const = 0;


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


	/**
	* Draw a debug point for a desired duration.
	* @param	pointPosition	The position in world-space of the point to draw.
	* @param	color			The color of the point to draw.
	* @param	duration		The duration of the debug draw (in seconds).
	*/
	virtual void DrawDebugPoint(const Vector3& pointPosition, const Color& color, float duration) = 0;

	/**
	* Draw a debug line between two points for a desired duration.
	* @param	pointA		The position in world-space of the first extremity of the line.
	* @param	pointB		The position in world-space of the second extremity of the line.
	* @param	color		The color of the line to draw.
	* @param	duration	The duration of the debug draw (in seconds).
	*/
	virtual void DrawDebugLine(const Vector3& pointA, const Vector3& pointB, const Color& color, float duration) = 0;

	/**
	* Draw a debug cube for a desired duration.
	* @param	boxInfos	The box values of the cube to draw.
	* @param	color		The color of the cube to draw.
	* @param	duration	The duration of the debug draw (in seconds).
	*/
	virtual void DrawDebugCube(const Box& boxInfos, const Color& color, float duration) = 0;
};