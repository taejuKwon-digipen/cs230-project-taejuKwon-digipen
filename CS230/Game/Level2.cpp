/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Level2.h"

Level2::Level2() : levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R),
ship(math::vec2{ Engine::GetWindow().GetSize().x / 2.0,Engine::GetWindow().GetSize().y / 2.0 }) {};

void Level2::Load()
{
	ship.Load();
}

void Level2::Update(double)
{
	ship.Update();
	
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().Shutdown();
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level2::Unload() {
}

void Level2::Draw()
{
	Engine::GetWindow().Clear({ 0x000000ff });
	ship.Draw();
}
