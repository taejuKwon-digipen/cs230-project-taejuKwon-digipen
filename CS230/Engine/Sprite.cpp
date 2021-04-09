/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/18/2021
-----------------------------------------------------------------*/
#include "Sprite.h"

CS230::Sprite::Sprite() {};

void CS230::Sprite::Load(const std::filesystem::path& texturePath)
{
	texture.Load(texturePath);
	hotSpot = texture.GetSize() / 2;
	hotSpotList.push_back(hotSpot);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition)
{
	texture.Load(texturePath);
	hotSpot = hotSpotPosition;
	hotSpotList.push_back(hotSpot);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots)
{
	texture.Load(texturePath);

	for (math::ivec2 hotspot : hotspots)
	{
		hotSpotList.push_back(hotSpot);
	}
}


void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	//texture.Draw(displayMatrix * math::TranslateMatrix(-hotSpot));

	for (int i = 0; i < hotSpotList.size(); i++)
	{
		texture.Draw(displayMatrix * math::TranslateMatrix(GetHotSpot(0)));
	}
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
	if (empty(hotSpotList) == true)
	{
		Engine::GetLogger().LogError("Not valid hotspot index");
	} 

	return math::ivec2{} = hotSpotList[index];
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}




