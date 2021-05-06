/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/

#include "Timer.h"
#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

Timer::Timer(int time) : timer(time)
{
	std::string timerString = "Time: " + std::to_string(static_cast <int>(timer));
	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
}

void Timer::Update(double dt)
{
	int curren_time = static_cast<int>(timer);
	timer -= dt;
	if (curren_time != static_cast<int>(timer))
	{
		std::string timnerString = "Time: " + std::to_string(static_cast <int>(timer + 1));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timnerString, 0xFFFFFFFF, true);
	}
	
}


void Timer::Draw(math::ivec2 location)
{
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	timeTexture.Draw(math::TranslateMatrix(math::ivec2{ location.x - timeTexture.GetSize().x, location.y-timeTexture.GetSize().y }));
}


bool Timer::hasEnded()
{
	if (timer <= 0.) 
	{
		return true;
	}
	return false;
}

