/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Taeju Kwon
Creation date:  2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level1.h"

Level1::Level1() : levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R),
hero(math::vec2{ Engine::GetWindow().GetSize().x / 2.0 ,floor }), ball(math::vec2( 600.0, floor )) {};

void Level1::Load()
{
	background.Load("assets/Background.png");
	hero.Load();
	ball.Load();
}
void Level1::Update(double dt) {
	
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif

	hero.Update(dt);
	ball.Update(dt);
}
void Level1::Unload(){
}

void Level1::Draw()
{
	background.Draw(math::vec2(0,0));
	hero.Draw();
	ball.Draw();
}
