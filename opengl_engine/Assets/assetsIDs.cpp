#include "assetsIDs.h"

uint32_t AssetsIDs::materialUniqueID;


void AssetsIDs::InitializeAssetIDs()
{
	materialUniqueID = 0;
}

uint32_t AssetsIDs::GenerateMaterialUniqueID()
{
	//  this will never return an unique ID of 0, it will be reserved to unitinialized materials
	materialUniqueID++;
	return materialUniqueID;
}
