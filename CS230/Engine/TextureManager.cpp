/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS230
Author: Kevin Wright
Creation date: 2/19/2021
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	if( pathToTexture.count(filePath) == false)
	{
		pathToTexture.insert(std::pair<std::filesystem::path, Texture*>(filePath, new Texture(filePath)));
	}
	return pathToTexture[filePath];
}

void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("Clear Textures");

	for(const std::pair<std::filesystem::path, Texture*>& _Map : pathToTexture)
	{
		delete _Map.second;
	}
	pathToTexture.clear();
}

