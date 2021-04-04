/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 31/3/2021
-----------------------------------------------------------------*/
#include "Background.h"
#include "../Engine/Engine.h"
#include "Level1.h"
#include "../Engine/Camera.h"

void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back(ParallaxInfo{ texturePath ,level });
}

void Background::Unload()
{
	backgrounds.clear();
}

math::ivec2 Background::Size()
{

	for (unsigned int i = 0; i < backgrounds.size(); i++)
	{
		if(backgrounds[i].level == 1)
		{
			return backgrounds[i].texture.GetSize();
		}
	}
	return math::ivec2{ 0,0 };
}

void Background::Draw(const CS230::Camera& camera)
{
	for (unsigned int i = 0; i < backgrounds.size(); i ++)
	{
		backgrounds[i].texture.Draw(math::TranslateMatrix(math::vec2{ -camera.GetPosition().x / backgrounds[i].level,0 }));
	}
}


