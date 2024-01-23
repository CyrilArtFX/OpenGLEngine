#pragma once

class Renderer;

class DefaultAssets
{
public:
	/**
	* Load every default assets (textures, meshes, materials)
	*/
	static void LoadDefaultAssets(Renderer& renderer);

	/**
	* Load assets that are needed for debug mode
	*/
	static void LoadDebugAssets();
};

