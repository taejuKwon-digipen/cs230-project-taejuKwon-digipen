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
#include "TransformMatrix.h"

CS230::Sprite::Sprite() {};

void CS230::Sprite::Load(const std::filesystem::path& texturePath)
{
	texture.Load(texturePath);
	hotSpot = texture.GetSize() / 2;
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition)
{
	texture.Load(texturePath);
	hotSpot = hotSpotPosition;
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	texture.Draw(displayMatrix * math::TranslateMatrix(-hotSpot));
	/*position = position - hotSpot;
	texture.Draw(position);*/
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}




