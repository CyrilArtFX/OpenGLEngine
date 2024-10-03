#pragma once
#include "assetMesh.h"
#include "assetTexture.h"
#include "assetMaterial.h"
#include <Rendering/Model/model.h>
#include <Audio/audioSound.h>

#include <unordered_map>
#include <string>


class AssetManager
{
public:
	/**
	* Delete all necessary objects.
	*/
	static void DeleteObjects();

	/**
	* Load the "null" assest (the assets that will be returned if user ask for a non-existing asset.
	*/
	static void LoadNullAssets();


	/**
	* Load a texture from file using stbi.
	* Name = the name you want to give to this texture in the asset storage.
	*/
	static void LoadTexture(std::string name, const std::string texturePath, bool flipVertical = false);

	/**
	* Retrieve a texture from the asset storage.
	*/
	static Texture& GetTexture(std::string name);

	/**
	* Delete a texture from the asset storage.
	*/
	static void DeleteTexture(std::string name);


	/**
	* Load a single mesh from handcoded vertices.
	* Name = the name you want to give to this mesh in the asset storage.
	*/
	static void LoadSingleMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});

	/**
	* Load a single mesh from a 3D file using assimp.
	* WARNING : It will load only the root mesh.
	* Name = the name you want to give to this mesh in the asset storage.
	*/
	static void LoadSingleMesh(std::string name, std::string filepath);

	/**
	* Load an entire model from a 3D file using assimp.
	* Will put the meshes in a vector.
	* Name = the name you want to give to this mesh collection in the asset storage.
	*/
	static void LoadMeshCollection(std::string name, std::string filepath);

	/**
	* Retrieve a single mesh from the asset storage.
	*/
	static Mesh& GetSingleMesh(std::string name);

	/**
	* Retrieve a collection of mesh from the asset storage.
	*/
	static MeshCollection& GetMeshCollection(std::string name);

	/**
	* Delete a single mesh from the asset storage.
	*/
	static void DeleteSingleMesh(std::string name);

	/**
	* Delete a collection of mesh from the asset storage.
	*/
	static void DeleteMeshCollection(std::string name);


	/**
	* Create a model and stores it.
	* Name = the name you want to give to this model in the asset storage.
	*/
	static Model& CreateModel(std::string name);

	/**
	* Retrieve a model from the asset storage.
	*/
	static Model& GetModel(std::string name);

	/**
	* Delete a model from the asset storage.
	*/
	static void DeleteModel(std::string name);


	/**
	* Create a shader and stores it.
	* Name = the name you want to give to this shader in the asset storage.
	*/
	static void CreateShaderProgram(std::string name, const std::string vertexName, const std::string fragmentName, ShaderType shaderType);

	/**
	* Retrieve a shader from the asset storage.
	*/
	static Shader& GetShader(std::string name);

	/**
	* Delete a shader from the asset storage.
	*/
	static void DeleteShader(std::string name);


	/**
	* Create a material and stores it.
	* Name = the name you want to give to this material in the asset storage.
	*/
	static Material& CreateMaterial(std::string name, Shader* shaderUsed);

	/**
	* Stores a material collection.
	* Name = the name you want to give to this material collection in the asset storage.
	*/
	static MaterialCollection& CreateMaterialCollection(std::string name, MaterialCollection materialCollection);

	/**
	* Retrieve a material from the asset storage.
	*/
	static Material& GetMaterial(std::string name);

	/**
	* Retrieve a material collection from the asset storage.
	*/
	static MaterialCollection& GetMaterialCollection(std::string name);

	/**
	* Delete a material from the asset storage.
	*/
	static void DeleteMaterial(std::string name);


	/**
	* Create a sound from file and stores it.
	* @param	name		The name you want to this sound in the asset storage.
	* @param	filePath	The path to the sound file to read.
	* @param	settings	(optionnal) Additionnal load settings for the sound.
	* @return				The newly created sound.
	*/
	static AudioSound& CreateSound(std::string name, std::string filePath, SoundSettings settings);

	/**
	* Retrieve a sound from the asset storage.
	* @param	name	The name of the sound you want to retrieve.
	* @return			The sound with corresponding name (if it exists).
	*/
	static AudioSound& GetSound(std::string name);

	/**
	* Delete a sound from the asset storage.
	* @param	name	The name of the sound you want to delete.
	*/
	static void DeleteSound(std::string name);



	/**
	* Register an audio collision type in the asset storage.
	* @param	name					The name you want to this audio collision type in the asset storage.
	* @param	audioCollisionType		The value of the audio collision type you want to register.
	* @return							The registered audio collision type.
	*/
	static AudioCollisionOcclusion& RegisterAudioCollisionType(std::string name, AudioCollisionOcclusion audioCollisionType);

	/**
	* Retrieve an audio collision type from the asset storage.
	* @param	name	The name of the audio collision type you want to retrieve.
	* @return			The audio collision type with corresponding name (if it exists).
	*/
	static AudioCollisionOcclusion& GetAudioCollisionType(std::string name);

	/**
	* Delete an audio collision type from the asset storage.
	* @param	name	The name of the audio collision type you want to delete.
	*/
	static void DeleteAudioCollisionType(std::string name);


private:
	static std::unordered_map<std::string, Texture> textures;
	static std::unordered_map<std::string, Mesh> meshesSingle;
	static std::unordered_map<std::string, MeshCollection> meshesCollection;
	static std::unordered_map<std::string, Model> models;
	static std::unordered_map<std::string, Shader> shaders;
	static std::unordered_map<std::string, Material> materials;
	static std::unordered_map<std::string, MaterialCollection> materialsCollection;
	static std::unordered_map<std::string, AudioSound> sounds;
	static std::unordered_map<std::string, AudioCollisionOcclusion> audioCollisionTypes;
};

