#pragma once
#include <stdint.h>

class AssetsIDs 
{
public:
	static void InitializeAssetIDs();

	static uint32_t GenerateMaterialUniqueID();


private:
	static uint32_t materialUniqueID;
};