/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

Splash::Splash(){};

void Splash::Load() {
	texture.Load("assets/DigiPen_BLACK_1024px.png");
}

void Splash::Update(double dt)
{
	Timer += dt;
	if(Timer >= MaxTime)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
	}
}

void Splash::Unload() {
	
}

void Splash::Draw()
{
	Engine::GetWindow().Clear({ 0xffffffff });
	texture.Draw(Engine::GetWindow().GetSize()/2 - texture.GetSize()/2);
}