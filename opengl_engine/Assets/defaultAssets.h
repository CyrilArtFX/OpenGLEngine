#pragma once

class DefaultAssets
{
public:
	/**
	* Load every default assets (textures, meshes, materials)
	*/
	static void LoadDefaultAssets();

	/**
	* Load assets that are needed for debug mode
	*/
	static void LoadDebugAssets();
};

