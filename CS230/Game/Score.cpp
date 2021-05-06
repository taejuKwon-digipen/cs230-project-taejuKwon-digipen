/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: taeju Kwon
Creation date: 2/17/2021
-----------------------------------------------------------------*/

#include "Score.h"
#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

Score::Score(int startingScore, Fonts fontToUse) : fontToUse(fontToUse)
{
	startingScore = 0;
	fontToUse = Fonts::Font2;
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}

void Score::Draw(math::ivec2 location)
{
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, location.y - scoreTexture.GetSize().y - 5 }));
}

void Score::RenderText()
{
	
}


